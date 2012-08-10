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
import freeciv
import features

features.add_feature('ui.fake_max_size')

import osutil
import common
import client

@freeciv.register
def get_overview_window():
    return overview_surface

@freeciv.register
def dirty_all():
    pass

@freeciv.register
def dirty_rect(x, y, w, h):
    pass

@freeciv.register
def get_overview_area_dimensions():
    return overview_surface.get_size()

@freeciv.register
def overview_size_changed():
    global overview_surface
    w, h = freeciv.get_overview_size()
    overview_surface = pygame.Surface((w, h))
    client.client.overview_size_changed(w, h)

@freeciv.register
def update_map_canvas_scrollbars_size():
    pass

@freeciv.register
def update_map_canvas_scrollbars():
    pass

@freeciv.register
def update_unit_info_label(n):
    pass

@freeciv.register
def flush_dirty():
    pass

@freeciv.register
def gui_flush():
    pass

@freeciv.register
def update_overview_scroll_window_pos(x, y):
    pass

@freeciv.register
def update_mouse_cursor(cursor):
    #pygame.mouse.set_cursor((8,8),(0,0),(0,0,0,0,0,0,0,0),(0,0,0,0,0,0,0,0))
    #pygame.mouse.set_visible(False)
    global current_cursor
    i = cursor_names.get(cursor, 'CURSOR_DEFAULT')
    current_cursor = cursors[cursor_mapping.get(i, 0)]

mouse_pos = (0, 0)

@freeciv.register
def create_line_at_mouse_pos():
    client.client.draw_patrol_lines = True
    freeciv.func.update_line(*mouse_pos)

def load_cursors():
    gfx = common.load_gfxfile('data/misc/cursors.png')
    cursor = []
    for i in xrange(10):
        x = i * 33 + 1
        w = 32
        y = 1
        h = 32
        cursor.append(common.crop_sprite(gfx, x, y, w, h, None, 0, 0))
    return cursor

def draw_cursor(pos):
    if not current_cursor:
        return
    #x, y = pos
    #w, h = current_cursor.get_size()
    #screen.blit(current_cursor, (x - w/2, y - h/2))

current_cursor = None
cursor_mapping = {}

def init_screen(size=None):
    def _get_max_size():
        fake = features.get('ui.fake_max_size')
        if fake:
            return map(int, fake.split(','))
        else:
            return pygame.display.Info().current_w, pygame.display.Info().current_h

    def _get_request_size(max_size):
        if osutil.is_desktop and not features.get('ui.fake_max_size'):
            return (1280, 800)
        else:
            w, h = max_size
            MAX_W = 800
            if w > MAX_W:
                scale = h / float(w)
                size = (MAX_W, int(MAX_W * scale))
            else:
                size = (w, h)
            return size

    global screen, surface, overview_surface, cursors, cursor_names
    pygame.display.init()
    if not size:
        max_size = _get_max_size()
        ask_for_size = _get_request_size(max_size)
        print 'screen size: max =', max_size, 'ask =', ask_for_size
    else:
        ask_for_size = size
        print 'explicit size:', ask_for_size
    screen = pygame.display.set_mode(ask_for_size, 0, 32) #((800, 480), 0, 32)
    pygame.display.set_caption("touchciv")
    surface = screen

def init():
    global screen, surface, overview_surface, cursors, cursor_names
    overview_surface = pygame.Surface((200, 200))
    cursors = load_cursors()
    cursor_names = dict([ (getattr(freeciv.const, name), name) for name in dir(freeciv.const) if name.startswith('CURSOR_') ])
