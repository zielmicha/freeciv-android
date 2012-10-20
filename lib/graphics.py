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

import pygame
import pygame.gfxdraw

from pygame import Rect

def load_image(fn):
    return Image(pygame.image.load(fn).convert_alpha())

def load_font(name, size):
    return Font(pygame.font.Font(name, size))

def create_surface(w, h, alpha=True):
    return Image(pygame.Surface((w, h), pygame.SRCALPHA if alpha else 0))

def get_screen_size():
    return pygame.display.Info().current_w, pygame.display.Info().current_h

def init():
    pygame.display.init()
    pygame.font.init()

def create_window(size, bits):
    global _window
    _window = Image(pygame.display.set_mode(size, 0, bits))
    pygame.display.set_caption("touchciv")
    return _window

def get_window():
    return _window

def get_events():
    return pygame.event.get()

def flip():
    pygame.display.flip()

class Font(object):
    def __init__(self, pg):
        self._pg = pg

    def render(self, text, antialias, fg, bg=None):
        return Image(self._pg.render(text, antialias, fg, *[bg] if bg else []))

    def size(self, text):
        return self._pg.size(text)

class Image(object):
    def __init__(self, pg):
        self._pg = pg

    def get_size(self):
        return self._pg.get_size()

    def get_width(self):
        return self.get_size()[0]

    def get_height(self):
        return self.get_size()[1]

    def blit(self, image, position=(0, 0), rectangle=None):
        self._pg.blit(image._pg, position, rectangle)

    def draw_rect(self, color, rect, width=0):
        pygame.draw.rect(self._pg, color, rect, width)

    def draw_line(self, color, start, end):
        pygame.draw.line(self._pg, color, start, end)

    def scale(self, size):
        return Image(pygame.transform.smoothscale(self._pg, size))

    def get_clip(self):
        return self._pg.get_clip()

    def set_clip(self, clip):
        self._pg.set_clip(pygame.Rect(clip))

    def gfx_ellipse(self, color, rect, width):
        if width == 0:
            f = pygame.gfxdraw.filled_ellipse
        else:
            f = pygame.gfxdraw.aaellipse
        f(self._pg, rect[0] + rect[2]/2, rect[1] + rect[2]/2, rect[2]/2, rect[3]/2, color)

    def gfx_rect(self, color, rect, width):
        if width == 0:
            pygame.gfxdraw.box(self._pg, rect, color)
        else:
            pygame.gfxdraw.rectangle(self._pg, rect, color)
