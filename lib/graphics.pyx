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

class Font(object):
    def __init__(self, pg):
        self._pg = pg

    def render(self, text, antialias, fg, bg=None):
        surf = create_surface(10, 10)
        return surf

    def size(self, text):
        return (10, 10)

cdef SDL_Texture* _sdl_get_texture(SDL_Renderer* renderer, item):
    cdef SDL_Surface* surf
    if isinstance(item, SoftwareSurface):
        raise SDLError('would need convert')
        #surf = (<SoftwareSurface> item)._surf
        #return SDL_CreateTextureFromSurface(renderer, surf)
    else:
        return (<Surface> item)._tex

cdef class Surface(object):
    cdef SDL_Renderer* _sdl
    cdef SDL_Texture* _tex
    cdef object _size

    def _set_target(self):
        res = SDL_SetRenderTarget(self._sdl, self._tex)
        if res < 0:
            raise SDLError()

    def get_size(self):
        return self._size

    def get_width(self):
        return self.get_size()[0]

    def get_height(self):
        return self.get_size()[1]

    def get_at(self, pos):
        pass

    def blit(self, image, position=(0, 0), rectangle=(0, 0, 8000, 8000)):
        blit_src = _sdl_get_texture(self._sdl, image)
        srect = _make_rect((position[0], position[1], rectangle[2], rectangle[3]))
        drect = _make_rect(rectangle)
        err = SDL_RenderCopy(self._sdl, blit_src,
                       &srect, &drect)
        if isinstance(image, SoftwareSurface):
            SDL_DestroyTexture(blit_src)
        if err < 0:
            raise SDLError()

    def draw_rect(self, color, rect, width=0):
        self._set_target()
        r, g, b, a = _get_rgba(color)
        SDL_SetRenderDrawColor(self._sdl, r, g, b, a)
        cdef SDL_Rect srect = _make_rect(rect)
        SDL_RenderDrawRect(self._sdl, &srect)

    def fill(self, color=(128, 0, 128)):
        r, g, b, a = _get_rgba(color)
        SDL_SetRenderDrawColor(self._sdl, r, g, b, a)
        SDL_RenderClear(self._sdl)

    def draw_line(self, color, start, end):
        pass

    def scale(self, size):
        return self # fixme

    def get_clip(self):
        return Rect((0, 0, 8000, 8000))

    def set_clip(self, clip):
        pass

    def gfx_ellipse(self, color, rect, width):
        pass
        #f(self._pg, rect[0] + rect[2]/2, rect[1] + rect[2]/2, rect[2]/2, rect[3]/2, color)

    def gfx_rect(self, color, rect, width):
        self.draw_rect(color, rect, width)

cdef Surface _window
cdef SDL_Window* _window_handle

cdef class SoftwareSurface(Surface):
    cdef SDL_Surface* _surf

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

def load_image(fn):
    cdef SDL_Surface* s = IMG_Load(fn)
    if not s:
        raise SDLError()
    cdef SDL_Texture* tex = SDL_CreateTextureFromSurface(_window._sdl, s)
    if not tex:
        raise SDLError()
    # todo: free s?
    return _make_surface(NULL, tex, (s.w, s.h))

def load_font(name, size):
    return Font(None)

def create_surface(w, h, alpha=True):
    # todo: use texture
    tex = SDL_CreateTexture(_window._sdl, SDL_PIXELFORMAT_ARGB8888,
                            SDL_TEXTUREACCESS_TARGET, max(1, w), max(1, h))
    if not tex:
        raise SDLError()
    return _make_surface(_window._sdl, tex)

def get_screen_size():
    return None

def init():
    if SDL_Init(SDL_INIT_VIDEO) < 0:
        raise SDLError()
    if TTF_Init() < 0:
        raise SDLError()

def create_window(size, bits):
    global _window, _window_handle
    w, h = size
    wnd = SDL_CreateWindow("touchciv", 0, 0, w, h, 0)
    _window_handle = wnd
    renderer = SDL_CreateRenderer(wnd, -1, 0)
    if not renderer:
        raise SDLError()
    _window = _make_surface(renderer, NULL)
    _window._size = size
    return get_window()

def get_window():
    return _window

def get_events():
    return []

# CONSTRUCTORS

cdef SoftwareSurface _make_software_surface(SDL_Surface* surf):
    if not surf:
        raise ValueError('passing NULL to _make_software_surface')
    s = SoftwareSurface()
    s._surf = surf
    s._sdl = SDL_CreateSoftwareRenderer(s._surf)
    if not s._sdl:
        raise SDLError()
    return s

cdef Surface _make_surface(SDL_Renderer* renderer, SDL_Texture* tex, _size=(0, 0)):
    cdef Surface s = Surface()
    s._sdl = renderer
    s._tex = tex
    s._size = _size
    return s

cdef SDL_Rect _make_rect(t):
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
    K_UP = SDLK_UP
    K_DOWN = SDLK_DOWN
    K_LEFT = SDLK_LEFT
    K_RIGHT = SDLK_RIGHT
    K_SPACE = SDLK_SPACE
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
