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

import graphics
from freeciv.client import _freeciv as freeciv
import features
import osutil
from freeciv import client

import common

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
    overview_surface = graphics.create_surface(w, h)
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
    pass

mouse_pos = (0, 0)

@freeciv.register
def create_line_at_mouse_pos():
    client.client.draw_patrol_lines = True
    freeciv.func.update_line(*mouse_pos)

def init_screen():
    global screen, surface, overview_surface

    screen = graphics.get_window()
    surface = screen

def init():
    global screen, surface, overview_surface
    overview_surface = graphics.create_surface(200, 200)
