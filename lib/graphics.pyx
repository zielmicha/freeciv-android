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

    def render(self, text, antialias, fg, bg=None):
        if len(text) == 0:
            text = ' '
        # todo: antialias and bg
        cdef SDL_Surface* s
        cdef SDL_Color fgcolor
        fgcolor.r, fgcolor.g, fgcolor.b, _ = _get_rgba(fg)
        surf = TTF_RenderUTF8_Blended(self.font, text, fgcolor)
        if not surf:
            raise TTFError()
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

cdef class Surface(object):
    cdef SDL_Renderer* _sdl
    cdef SDL_Texture* _tex
    cdef object _size
    cdef object _filename

    def _set_target(self):
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

    def blit(self, image, dest=(0, 0), src=None):
        cdef SDL_Rect srect, drect
        cdef SDL_Texture* blit_src
        self._set_target()
        if not src:
            src = (0, 0, image.get_width(), image.get_height())
        if len(dest) == 2:
            dest = (dest[0], dest[1], src[2], src[3])
        blit_src = _sdl_get_texture(self._sdl, image)
        srect = _make_rect(src)
        drect = _make_rect(dest)
        err = SDL_RenderCopy(self._sdl, blit_src, &srect, &drect)
        if err < 0:
            raise SDLError()
        self._finish()

    def draw_rect(self, color, rect, width=0):
        self._set_target()
        r, g, b, a = _get_rgba(color)
        SDL_SetRenderDrawColor(self._sdl, r, g, b, a)
        cdef SDL_Rect srect = _make_rect(rect)
        if width == 0:
            SDL_RenderFillRect(self._sdl, &srect)
        else:
            SDL_RenderDrawRect(self._sdl, &srect)
        self._finish()

    def fill(self, color=(128, 0, 128)):
        self._set_target()
        r, g, b, a = _get_rgba(color)
        SDL_SetRenderDrawColor(self._sdl, r, g, b, a)
        SDL_RenderClear(self._sdl)
        self._finish()

    def draw_line(self, color, start, end):
        self._set_target()
        self._finish()

    def scale(self, size):
        cdef Surface dest = create_surface(size[0], size[1])
        dest._filename = 'scaled %s' % self._filename
        dest.blit(self, dest=(0, 0, size[0], size[1]))
        return dest

    def gfx_ellipse(self, color, rect, width):
        pass
        #f(self._pg, rect[0] + rect[2]/2, rect[1] + rect[2]/2, rect[2]/2, rect[3]/2, color)

    def gfx_rect(self, color, rect, width):
        self.draw_rect(color, rect, width)

    def get_clip(self):
        return Rect((0, 0, 8000, 8000))

    def __repr__(self):
        return '<Surface 0x%X filename=%r>' % (id(self), self._filename)

    def __dealloc__(self):
        if self._tex != NULL:
            SDL_DestroyTexture(self._tex)
            self._tex = NULL

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
        return max(x, x1), max(y, y1), min(x + w, x1 + w1) - max(x, x1), \
            min(y + h, y1 + h1) - max(y, y1)

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
    cdef SDL_Texture* tex = SDL_CreateTextureFromSurface(_window._sdl, s)
    if not tex:
        raise SDLError()
    size = (s.w, s.h)
    SDL_FreeSurface(s)
    return _make_surface(NULL, tex, size, fn)

def load_font(name, size):
    return Font(name, size)

def create_surface(w, h, alpha=True):
    cdef SDL_Texture* tex
    MAX = 2048
    tex = SDL_CreateTexture(_window._sdl, 0,
                            SDL_TEXTUREACCESS_TARGET, min(max(1, w), MAX), min(max(1, h), MAX))
    if not tex:
        raise SDLError('create texture %dx%d' % (w, h))
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND)
    surf = _make_surface(_window._sdl, tex, (w, h))
    surf.fill((0, 0, 0, 0))
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

def create_window(size):
    global _window, _window_handle
    w, h = size
    wnd = SDL_CreateWindow("touchciv", 0, 0, w, h, 0)
    _window_handle = wnd
    renderer = SDL_CreateRenderer(wnd, -1, 0)
    _prepare_renderer(renderer)
    if not renderer:
        raise SDLError()
    _window = _make_surface(renderer, NULL)
    _window._size = size
    return get_window()

cdef _prepare_renderer(SDL_Renderer* renderer):
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND)

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
                           _size=(0, 0), _filename=None):
    cdef Surface s = Surface()
    s._sdl = renderer
    s._tex = tex
    s._size = _size
    s._filename = _filename
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
    QUIT = SDL_QUIT
    KEYDOWN = SDL_KEYDOWN
    KEYUP = SDL_KEYUP
    K_UP = SDLK_UP
    K_DOWN = SDLK_DOWN
    K_LEFT = SDLK_LEFT
    K_RIGHT = SDLK_RIGHT
    K_SPACE = SDLK_SPACE
    K_ESCAPE = SDLK_ESCAPE
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
