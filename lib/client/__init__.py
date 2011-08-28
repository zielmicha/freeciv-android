import select
import pygame

import progress
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

import freeciv

import dialogs
import common
import window
import actions
import city
import key
import misc
import time

net_socket = -1
client = None
main = None

@freeciv.register
def ui_main():
    progress.draw_frame('', 'loading tileset...', 1)
    freeciv.func.init_things()
    freeciv.func.init_mapcanvas_and_overview()
    main()
    
def tick():
    pass

@freeciv.register
def ui_init():
    common.init()

@freeciv.register
def add_net_input(sockid):
    global net_socket
    net_socket = sockid

@freeciv.register
def remove_net_input():
    global net_socket
    net_socket = -1

@freeciv.register
def real_output_window_append(text, tags, connid):
    client.console_line(text)

@freeciv.register
def real_update_meswin_dialog():
    count = freeciv.func.get_num_messages()
    client.update_meswin([ freeciv.func.get_message(i) for i in xrange(count) ])

class Client(object):
    def __init__(self):
        global client
        client = self
        self.next_time = time.time()
        self.cursor_pos = (0, 0)
    
    def tick(self):
        if self.next_time >= time.time():
            sleep_time = freeciv.func.real_timer_callback()
            self.next_time = time.time() + sleep_time
        
        freeciv.func.call_idle_callbacks()
        if net_socket != -1:
            r, w, x = select.select([net_socket], [], [], 0.03)
            if r:
                freeciv.func.input_from_server(net_socket)
        else:
            time.sleep(0.03)
        
        #window.draw_cursor(cursor_pos)
    
    def console_line(self, text):
        print '[OutWindow]', text
    
    def end_turn(self):
        freeciv.func.key_end_turn()
    
    def chat(self, text):
        freeciv.func.send_chat(text)
    
    def draw_map(self, surf, pos):
        mapview = freeciv.func.get_mapview_store()
        surf.blit(mapview, pos)
    
    def draw_overview(self, surf, pos):
        surf.blit(window.overview_surface, pos)
        pygame.draw.rect(surf, (255, 255, 255), pos + window.overview_surface.get_size(), 1)
    
    def set_map_size(self, size):
        freeciv.func.map_canvas_resized(*size)
    
    def update_map_canvas_visible(self):
        freeciv.func.update_map_canvas_visible()
    
    def get_overview_size(self):
        return window.overview_surface.get_size()
    
    def mouse_motion(self, pos):
        window.mouse_pos = self.cursor_pos = pos
        x, y = pos
        freeciv.func.update_line(x, y)
        freeciv.func.control_mouse_cursor_pos(x, y)
    
    def popup_unit_select_dialog(self, units):
        print 'unit_select_dialog', units
    
    def key_event(self, type, keycode):
        key.key(type, keycode)
    
    def update_meswin(self, lines):
        print 'meswin updated'
        print '\t' + '\n\t'.join(map(repr, lines))
    
    def connect_to_server(self, username, host, port):
        bufflen = 512
        buff = ' ' * bufflen
        result = freeciv.func.connect_to_server(username, host, port, buff, bufflen)
        buff = buff.rstrip(' ').rstrip('\0')
        if result == -1:
            print 'fail %r' % buff
    
    def disable_menus(self):
        print 'disable_menus'
    
    def get_unit_in_focus(self):
        units = freeciv.func.get_units_in_focus()
        if units:
            return actions.Unit(units[0])
        else:
            return None
    
    
    