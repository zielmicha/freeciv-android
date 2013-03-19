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

SDL_INIT_VIDEO = 0x20

class const: pass
const = const()

class Font(object):
    def __init__(self, pg):
        self._pg = pg

    def render(self, text, antialias, fg, bg=None):
        return Surface(self._pg.render(text, antialias, fg, *[bg] if bg else []))

    def size(self, text):
        return self._pg.size(text)

cdef SDL_Texture* _sdl_get_texture(item):
    return <SDL_Texture*> 0

cdef class Surface(object):
    cdef SDL_Renderer* _sdl
    cdef object _size

    def __init__(self):
        pass

    def get_size(self):
        return self._size

    def get_width(self):
        return self.get_size()[0]

    def get_height(self):
        return self.get_size()[1]

    def get_at(self, pos):
        pass

    def blit(self, image, position=(0, 0), rectangle=None):
        assert not rectangle
        assert position == (0, 0)
        SDL_RenderCopy(self._sdl, _sdl_get_texture(image),
                       <SDL_Rect*> 0, <SDL_Rect*> 0)

    def draw_rect(self, color, rect, width=0):
        r, g, b, a = _get_rgba(color)
        SDL_SetRenderDrawColor(self._sdl, r, g, b, a)
        cdef SDL_Rect* srect = _make_rect(rect)
        SDL_RenderDrawRect(self._sdl, srect)
        free(srect)

    def fill(self, color=(128, 0, 128)):
        r, g, b, a = _get_rgba(color)
        SDL_SetRenderDrawColor(self._sdl, r, g, b, a)
        SDL_RenderClear(self._sdl)

    def draw_line(self, color, start, end):
        pass

    def scale(self, size):
        return Surface(None)

    def get_clip(self):
        return self._pg.get_clip()

    def set_clip(self, clip):
        self._pg.set_clip(None)

    def gfx_ellipse(self, color, rect, width):
        f = None
        f(self._pg, rect[0] + rect[2]/2, rect[1] + rect[2]/2, rect[2]/2, rect[3]/2, color)

    def gfx_rect(self, color, rect, width):
        self.draw_rect(color, rect, width)

cdef Surface _window

class SDLError(Exception):
    pass

def load_image(fn):
    return Surface(None)

def load_font(name, size):
    return Font(None)

def create_surface(w, h, alpha=True):
    return Surface(None)

def get_screen_size():
    return None

def init():
    if SDL_Init(SDL_INIT_VIDEO) < 0:
        raise SDLError('SDL_Init')

def create_window(size, bits):
    global _window
    w, h = size
    wnd = SDL_CreateWindow("touchciv", 0, 0, w, h, 0)
    renderer = SDL_CreateRenderer(wnd, -1, 0)
    _window = _make_surface(renderer)
    _window._size = size
    return get_window()

def get_window():
    return _window

def get_events():
    pass

cdef Surface _make_surface(SDL_Renderer* renderer):
    cdef Surface s = Surface()
    s._sdl = renderer
    return s

cdef SDL_Rect* _make_rect(t):
    cdef SDL_Rect* r = <SDL_Rect*> malloc(sizeof(SDL_Rect))
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
