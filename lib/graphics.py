# Copyright (C) 2013 Michal Zielinski (michal@zielinscy.org.pl)
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

import io
import os

class Font(object):
    def __init__(self, name, size):
        pass

    def render(self, text, antialias=1, fg=(0, 0, 0), bg=None):
        return create_surface(10, 10)

    def size(self, text):
        return (10, 10)

MODE_BLEND, MODE_MOD, MODE_NONE, MODE_ADD = range(4)

class Surface(object):
    def get_size(self):
        return self._size

    def get_width(self):
        return self.get_size()[0]

    def get_height(self):
        return self.get_size()[1]

    def get_at(self, pos):
        pass

    def blit(self, image, dest=(0, 0), src=None, blend=MODE_BLEND):
        pass

    def draw_rect(self, color, rect, width=0, blend=MODE_BLEND):
        pass

    def fill(self, color=(128, 0, 128), blend=MODE_BLEND):
        pass

    def draw_line(self, color, start, end, blend=MODE_BLEND):
        pass

    def scale(self, size, src=None):
        pass

    def checked_cropped(self, rect):
        pass

    def gfx_rect(self, color, rect, width, **kwargs):
        self.draw_rect(color, rect, width, **kwargs)

    def get_clip(self):
        return Rect((0, 0, 8000, 8000))

    def __repr__(self):
        return '<Surface 0x%X filename=%r>' % (id(self), self._filename)

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

def load_image(fn):
    return create_surface(10, 10)

def load_font(name, size):
    return Font(name, size)

def create_surface(w, h, alpha=True):
    return Surface()

def get_screen_size():
    return (1000, 1000)

def init():
    pass

def start_text_input():
    pass

def stop_text_input():
    pass

def create_window(size):
    pass

def get_window():
    pass

def get_events():
    pass
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
    pass

def flip():
    pass

class const: pass

const = const()

_consts = ['MOUSEBUTTONUP', 'MOUSEBUTTONDOWN', 'MOUSEMOTION', 'TEXTEDITING', 'TEXTINPUT', 'QUIT', 'KEYDOWN', 'KEYUP', 'K_UP', 'K_DOWN', 'K_LEFT', 'K_RIGHT', 'K_SPACE', 'K_ESCAPE', 'K_BACKSPACE', 'K_AC_BACK', 'K_F1', 'K_a', 'K_b', 'K_c', 'K_d', 'K_e', 'K_f', 'K_g', 'K_h', 'K_i', 'K_j', 'K_k', 'K_l', 'K_m', 'K_o', 'K_p', 'K_q', 'K_r', 'K_s', 'K_t', 'K_u', 'K_v', 'K_w', 'K_x', 'K_y', 'K_z']

for item in _consts:
    setattr(const, item, item)
