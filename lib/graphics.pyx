# Copyright (C) 2011 Michal Zielinski (michal@zielinscy.org.pl)
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

from libc.stdlib cimport malloc, free
from SDL cimport *
import io
import os

cdef class Font(object):
    cdef TTF_Font* font
    cdef object name, font_size

    def __init__(self, name, size):
        self.name = name
        self.font_size = size
        cdef SDL_RWops* res = open_file(name)
        self.font = TTF_OpenFontRW(res, True, size)
        if not self.font:
            raise TTFError()

    def render(self, text, antialias=1, fg=(0, 0, 0), bg=None):
        if len(text) == 0:
            text = ' '
        if isinstance(text, unicode):
            text = text.encode('utf8')
        # todo: antialias and bg
        cdef SDL_Surface* s
        cdef SDL_Color fgcolor
        fgcolor.r, fgcolor.g, fgcolor.b, _ = _get_rgba(fg)
        surf = TTF_RenderUTF8_Blended(self.font, text, fgcolor)
        if not surf:
            raise TTFError()
        _debug_createtexture(surf.w, surf.h)
        cdef SDL_Texture* tex = SDL_CreateTextureFromSurface(_window._sdl, surf)
        if not tex:
            raise SDLError()
        size = (surf.w, surf.h)
        SDL_FreeSurface(surf)
        return _make_surface(NULL, tex, size, "render of %s" % text)

    def size(self, text):
        cdef int w, h
        if TTF_SizeUTF8(self.font, text, &w, &h):
            raise TTFError()
        return (w, h)

cdef SDL_Texture* _sdl_get_texture(SDL_Renderer* renderer, item):
    cdef SDL_Surface* surf
    return (<Surface> item)._tex

_debug_texturecount = 0
_debug_texturepixels = 0

cdef _debug_createtexture(int w, int h):
    global _debug_texturecount, _debug_texturepixels
    _debug_texturecount += 1
    _debug_texturepixels += w * h

def _debug_destroytexture(size):
    global _debug_texturecount, _debug_texturepixels
    _debug_texturecount -= 1
    _debug_texturepixels -= size[0] * size[1]

MODE_BLEND = SDL_BLENDMODE_BLEND
MODE_MOD = SDL_BLENDMODE_MOD
MODE_NONE = SDL_BLENDMODE_NONE
MODE_ADD = SDL_BLENDMODE_ADD

same_blit_buffer = None

cdef class Surface(object):
    cdef SDL_Renderer* _sdl
    cdef SDL_Texture* _tex
    cdef object _size
    cdef object _filename
    cdef int _alpha
    # version number - changes after each draw
    cdef int _version

    def __cinit__(self):
        self._version = 0

    def _set_target(self):
        # increment version number when texture is set as target
        self._version += 1

        # set as target
        res = SDL_SetRenderTarget(self._sdl, self._tex)
        if res < 0:
            raise SDLError()

    cdef void _finish(self):
        if self._tex != NULL:
            pass # SDL_RenderPresent(self._sdl)

    def get_size(self):
        return self._size

    def get_width(self):
        return self.get_size()[0]

    def get_height(self):
        return self.get_size()[1]

    def get_at(self, pos):
        pass

    def blit(self, image, dest=(0, 0), src=None, blend=MODE_BLEND, alpha_mask=255):
        global same_blit_buffer
        if isinstance(image, CroppedSurface):
            (<CroppedSurface>image).blit_into(self, dest, src, blend, alpha_mask)
            return
        cdef SDL_Rect srect, drect
        cdef SDL_Texture* blit_src
        if not src:
            src = (0, 0, image.get_width(), image.get_height())

        if self == image:
            if not same_blit_buffer:
                same_blit_buffer = create_surface(512, 512)
            if src[2] > same_blit_buffer.get_width() or src[3] > same_blit_buffer.get_height():
                raise RuntimeError('src==dest blit too big to fit into same_blit_buffer')
            newsrc = (0, 0, src[2], src[3])
            same_blit_buffer.draw_rect((0, 0, 0, 0), newsrc, blend=MODE_NONE)
            same_blit_buffer.blit(image, src=src)
            src = newsrc
            image = same_blit_buffer
        self._set_target()

        if len(dest) == 2:
            dest = (dest[0], dest[1], src[2], src[3])
        blit_src = _sdl_get_texture(self._sdl, image)
        SDL_SetTextureAlphaMod(blit_src, alpha_mask)
        srect = _make_rect(src)
        drect = _make_rect(dest)
        SDL_SetTextureBlendMode(blit_src, blend)
        err = SDL_RenderCopy(self._sdl, blit_src, &srect, &drect)
        if err < 0:
            raise SDLError()
        #self._filename = 'last blit was from %s' % (<Surface>image)._filename
        self._finish()

    def draw_rect(self, color, rect, width=0, blend=MODE_BLEND):
        self._set_target()
        r, g, b, a = _get_rgba(color)
        SDL_SetRenderDrawColor(self._sdl, r, g, b, a)
        SDL_SetRenderDrawBlendMode(self._sdl, blend)
        cdef SDL_Rect srect = _make_rect(rect)
        if width == 0:
            SDL_RenderFillRect(self._sdl, &srect)
        else:
            SDL_RenderDrawRect(self._sdl, &srect)
        self._finish()

    def fill(self, color=(128, 0, 128), blend=MODE_BLEND):
        self._set_target()
        r, g, b, a = _get_rgba(color)
        SDL_SetRenderDrawColor(self._sdl, r, g, b, a)
        SDL_SetRenderDrawBlendMode(self._sdl, blend)
        SDL_RenderClear(self._sdl)
        self._finish()

    def draw_line(self, color, start, end, blend=MODE_BLEND):
        self._set_target()
        r, g, b, a = _get_rgba(color)
        SDL_SetRenderDrawColor(self._sdl, r, g, b, a)
        SDL_SetRenderDrawBlendMode(self._sdl, blend)
        x1, y1 = start
        x2, y2 = end
        SDL_RenderDrawLine(self._sdl, x1, y1, x2, y2)
        self._finish()

    def scale(self, size, src=None):
        cdef Surface dest = create_surface_small(size[0], size[1])
        dest._filename = 'scaled %s' % self._filename
        dest.blit(self, dest=(0, 0, size[0], size[1]), src=src)
        return dest

    def cropped(self, rect):
        return CroppedSurface(self, rect)

    def checked_cropped(self, rect):
        if Rect((0, 0,) + self.get_size()).clip(rect) != rect:
            raise ValueError('cropping %s of %s image' % (rect, self.get_size()))
        return self.cropped(rect)

    def gfx_ellipse(self, color, rect, width):
        raise NotImplementedError
        #f(self._pg, rect[0] + rect[2]/2, rect[1] + rect[2]/2, rect[2]/2, rect[3]/2, color)

    def gfx_rect(self, color, rect, width, **kwargs):
        self.draw_rect(color, rect, width, **kwargs)

    def get_clip(self):
        return Rect((0, 0, 8000, 8000))

    def read_data(self):
        yfix = self.get_size()[1] - _window.get_size()[1]
        self._set_target()
        #tex = create_surface(*self.get_size())
        #tex.blit(self)
        #tex._set_target()
        size = self.get_size()
        if size[0] != 0 and size[1] != 0:
            return read_renderer_data((0, -yfix) + size, self._sdl)
        else:
            return ''

    property filename:
        def __set__(self, val): self._filename = val
        def __get__(self): return self._filename

    property version:
        def __get__(self): return self._version

    def __repr__(self):
        return '<Surface 0x%X filename=%r>' % (id(self), self._filename)

    def destroy(self):
        if self._tex != NULL:
            SDL_DestroyTexture(self._tex)
            self._tex = NULL
            _debug_destroytexture(self.get_size())

    def __dealloc__(self):
        if self._tex != NULL:
            SDL_DestroyTexture(self._tex)
            self._tex = NULL
            _debug_destroytexture(self.get_size())

cdef class CroppedSurface(Surface):
    cdef object orig
    cdef object rect
    cdef object allocator
    cdef object alloc_free_data

    def get_orig(self):
        return self.orig

    def get_crop(self):
        return self.rect

    def __init__(self, orig, rect):
        assert rect
        self.orig = orig
        self.rect = Rect(rect)

    def get_size(self):
        return self.rect[2], self.rect[3]

    cdef object blit_into(self, surf, dest, src, blend, alpha_mask):
        if not src:
            src = self.rect
        else:
            src = (src[0] + self.rect[0], src[1] + self.rect[1], src[2], src[3])
            src = self.rect.clip(src)
        if len(dest) == 2:
            dest = dest + (src[2], src[3])
        surf.blit(self.orig, dest, src, blend, alpha_mask)

    def blit(self, surf, dest=(0, 0), src=None, *args, **kwargs):
        if not src:
            src = (0, 0) + surf.get_size()
        if len(dest) == 2:
            dest = dest + (src[2], src[3])
        dest = (dest[0] + self.rect[0], dest[1] + self.rect[1], dest[2], dest[3])
        if self.rect.clip(dest) != dest: print 'risky blit'

        self.orig.blit(surf, dest, src, *args, **kwargs)

    def scale(self, size):
        return self.orig.scale(size, src=self.rect)

    def set_alloc_data(self, allocator, alloc_free_data):
        self.allocator = allocator
        self.alloc_free_data = alloc_free_data

    def __del__(self):
        if self.allocator:
            self.allocator.free_area(*self.alloc_free_data)

def create_surface_small(w, h):
    _init_alloc()
    for alloc in allocators:
        if alloc.sw >= w and alloc.sh >= h:
            return alloc.alloc(w, h)
    return create_surface(w, h)

def read_window_data():
    if _window._tex:
        return _window.read_data()
    else:
        return read_renderer_data((0, 0) + _window.get_size(), _window._sdl)

cdef object read_renderer_data(object _rect, SDL_Renderer* renderer):
    cdef object size = (_rect[2], _rect[3])
    cdef SDL_Rect rect = _make_rect(_rect)
    cdef int pixelsize = 4
    cdef int bufsize = pixelsize * size[0] * size[1]
    cdef char* pixels = <char*>malloc(bufsize)
    if SDL_RenderReadPixels(renderer, &rect,
                            SDL_PIXELFORMAT_ABGR8888,
                            pixels, size[0] * pixelsize) != 0:
        free(pixels)
        raise SDLError()
    cdef bytes py_data = pixels[:bufsize]
    free(pixels)
    return py_data

S = 1024

class Allocator:
    def __init__(self, sw, sh=None):
        sh = sh or sw
        self.sw = sw
        self.sh = sh
        self.buffs = []
        self.nw = S / self.sw
        self.nh = S / self.sh
        self.free = []
        self._usage = []

    def add_buff(self):
        i = len(self.buffs)
        self.buffs.append(create_surface(S, S))
        self.free += [ (i, x, y) for x in xrange(self.nw) for y in xrange(self.nh) ]

    def alloc(self, w, h):
        if not self.free:
            self.add_buff()
        i, x, y = self.free.pop()
        self._usage.append(w * h / float(self.sw) / float(self.sh))
        img = self.buffs[i].checked_cropped((x * self.sw, y * self.sh, w, h))
        img.set_alloc_data(self, (i, x, y))
        return img

    def free_area(self, i, x, y):
        self.buffs[i].draw_rect((0, 0, 0, 0), (x, y, self.sw, self.sh), mode=MODE_NONE)
        self.free.append((i, x, y))

def _init_alloc():
    global allocators
    if not allocators:
        allocators = []

allocators = []

cdef Surface _window
cdef SDL_Window* _window_handle

class Rect(tuple):
    def colliderect(self, point):
        x, y, w, h = self
        x1, y1 = point
        return x1 >= x and x1 < x + w and y1 >= y and y1 < y + h

    def inflate(self, W, H):
        x, y, w, h = self
        return x - W, y - H, w + W * 2, h + H * 2

    def clip(self, other):
        x, y, w, h = self
        x1, y1, w1, h1 = other
        return Rect((max(x, x1), max(y, y1), min(x + w, x1 + w1) - max(x, x1), \
            min(y + h, y1 + h1) - max(y, y1)))

    def empty(self):
        x, y, w, h = self
        return w <= 0 or h <= 0

    @property
    def left(self):
        return self[0]

    @property
    def right(self):
        return self[0] + self[2]

    @property
    def top(self):
        return self[1]

    @property
    def bottom(self):
        return self[1] + self[3]

class SDLError(Exception):
    def __init__(self, msg=None):
        if not msg:
            msg = SDL_GetError()
        Exception.__init__(self, msg)

class TTFError(Exception):
    def __init__(self, msg=None):
        if not msg:
            msg = TTF_GetError()
        Exception.__init__(self, msg)

def load_image(fn):
    cdef SDL_RWops* res = open_file(fn)
    if not res:
        raise SDLError()
    cdef SDL_Surface* s = IMG_Load_RW(res, True)
    if not s:
        raise SDLError()
    _debug_createtexture(s.w, s.h)
    cdef SDL_Texture* tex = SDL_CreateTextureFromSurface(_window._sdl, s)
    if not tex:
        raise SDLError()
    size = (s.w, s.h)
    SDL_FreeSurface(s)
    return _make_surface(NULL, tex, size, fn)

def load_font(name, size):
    return Font(name, size)

max_texture_size = 2048

def create_surface(w, h, alpha=True):
    cdef SDL_Texture* tex
    MAX = max_texture_size
    if w > MAX or h > MAX:
        print 'WARNING! trimming texture to fit max size'
    _debug_createtexture(w, h)
    tex = SDL_CreateTexture(_window._sdl, 0,
                            SDL_TEXTUREACCESS_TARGET, min(max(1, w), MAX), min(max(1, h), MAX))
    if not tex:
        raise SDLError('create texture %dx%d' % (w, h))
    surf = _make_surface(_window._sdl, tex, (w, h), "created", alpha)
    if alpha:
        surf.fill((0, 0, 0, 0), blend=MODE_NONE)
    else:
        surf.fill((255, 0, 0, 255), blend=MODE_NONE)
    return surf

def get_screen_size():
    cdef SDL_DisplayMode mode
    if SDL_GetDesktopDisplayMode(0, &mode) < 0:
        raise SDLError()
    return (mode.w, mode.h)

def init():
    if SDL_Init(SDL_INIT_VIDEO) < 0:
        raise SDLError()
    if TTF_Init() < 0:
        raise SDLError()
    SDL_SetHint("SDL_RENDER_SCALE_QUALITY", "linear")

def start_text_input():
    SDL_StartTextInput()

def stop_text_input():
    SDL_StopTextInput()

def create_window(size, hidden=False, fullscreen=False):
    global _window, _window_handle
    w, h = size
    flags = SDL_WINDOW_OPENGL # we need OpenGL, software renderer is shit
    if hidden:
        flags |= SDL_WINDOW_HIDDEN
    if fullscreen:
        flags |= SDL_WINDOW_FULLSCREEN
    wnd = SDL_CreateWindow("touchciv", 0, 0, w, h, flags)
    _window_handle = wnd
    renderer = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED)
    if not renderer:
        raise SDLError()
    _window = _make_surface(renderer, NULL, size, "window")
    _window._size = size
    print 'graphics: window created', size
    return get_window()

def set_offscreen_window(size):
    global _window
    _window = create_surface(*size)

def set_logical_size(w, h):
    assert _window
    SDL_RenderSetLogicalSize(_window._sdl, w, h)
    _window._size = (w, h)

def get_window():
    return _window

def get_events():
    events = []
    cdef SDL_Event ev
    while SDL_PollEvent(&ev):
        events.append(_translate_event(&ev))
    return events

cdef object _translate_event(SDL_Event* ev):
    if ev.type == SDL_MOUSEMOTION:
        return Event(ev.type, pos=(ev.motion.x, ev.motion.y))
    elif ev.type in (SDL_MOUSEBUTTONUP, SDL_MOUSEBUTTONDOWN):
        return Event(ev.type, pos=(ev.button.x, ev.button.y),
                     button=ev.button.button)
    elif ev.type in (SDL_KEYUP, SDL_KEYDOWN):
        return Event(ev.type, key=_translate_sym(ev.key.keysym.sym))
    elif ev.type == SDL_TEXTINPUT:
        return Event(ev.type, text=str(ev.text.text))
    elif ev.type == SDL_TEXTEDITING:
        return Event(ev.type, text=str(ev.edit.text), start=ev.edit.start,
                     length=ev.edit.length)
    else:
        return Event(ev.type)

def _translate_sym(n):
    return key_map.get(n, n)

key_map = {}

def map_key(src, dst):
    key_map[src] = dst

class Event:
    def __init__(self, type, **dict):
        self.type = type
        for k, v in dict.items():
            setattr(self, k, v)

    @property
    def dict(self):
        return self.__dict__

    def __repr__(self):
        return 'Event(%s, %s)' % (self.type, self.__dict__)

def sdl_open(path):
    cdef char buf[8096]
    cdef SDL_RWops* ops = open_file(path)
    if not ops:
        raise SDLError()
    data = []
    while True:
        read = SDL_RWread(ops, buf, 1, sizeof(buf))
        if read <= 0:
            break
        data.append(buf[:read])
    SDL_RWclose(ops)
    return io.BytesIO(''.join(data))

cdef SDL_RWops* open_file(path):
    if path.startswith('data') and os.environ.get('FC_DATA_PATH'):
        path = os.environ['FC_DATA_PATH'] + '/' + path
    return SDL_RWFromFile(path, "rb")

# CONSTRUCTORS

cdef Surface _make_surface(SDL_Renderer* renderer, SDL_Texture* tex,
                           _size=(0, 0), _filename=None, _alpha=True):
    cdef Surface s = Surface()
    s._sdl = renderer
    s._tex = tex
    s._size = (int(_size[0]), int(_size[1]))
    s._filename = _filename
    s._alpha = _alpha
    return s

cdef SDL_Rect _make_rect(t) except *:
    assert isinstance(t, (tuple, list)), 'invalid rect %r' % t
    cdef SDL_Rect r
    x, y, w, h = t
    r.x = x
    r.y = y
    r.w = w
    r.h = h
    return r

cdef _get_rgba(t):
    if len(t) == 3:
        return t + (255, )
    else:
        return t

def flip():
    SDL_RenderPresent(_window._sdl)

class const:
    MOUSEBUTTONUP = SDL_MOUSEBUTTONUP
    MOUSEBUTTONDOWN = SDL_MOUSEBUTTONDOWN
    MOUSEMOTION = SDL_MOUSEMOTION
    TEXTEDITING = SDL_TEXTEDITING
    TEXTINPUT = SDL_TEXTINPUT
    QUIT = SDL_QUIT
    KEYDOWN = SDL_KEYDOWN
    KEYUP = SDL_KEYUP
    K_UP = SDLK_UP
    K_DOWN = SDLK_DOWN
    K_LEFT = SDLK_LEFT
    K_RIGHT = SDLK_RIGHT
    K_SPACE = SDLK_SPACE
    K_ESCAPE = SDLK_ESCAPE
    K_BACKSPACE = SDLK_BACKSPACE
    K_AC_BACK = SDLK_AC_BACK
    K_F1 = SDLK_F1
    K_a = SDLK_a
    K_b = SDLK_b
    K_c = SDLK_c
    K_d = SDLK_d
    K_e = SDLK_e
    K_f = SDLK_f
    K_g = SDLK_g
    K_h = SDLK_h
    K_i = SDLK_i
    K_j = SDLK_j
    K_k = SDLK_k
    K_l = SDLK_l
    K_m = SDLK_m
    K_o = SDLK_o
    K_p = SDLK_p
    K_q = SDLK_q
    K_r = SDLK_r
    K_s = SDLK_s
    K_t = SDLK_t
    K_u = SDLK_u
    K_v = SDLK_v
    K_w = SDLK_w
    K_x = SDLK_x
    K_y = SDLK_y
    K_z = SDLK_z

const = const()
