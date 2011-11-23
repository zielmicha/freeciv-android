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

import select
import pygame
import time

import progress

import freeciv

import dialogs
import common
import window
import actions
import city
import key
import misc

net_socket = -1
client = None
main = None

class ConnectionError(Exception):
    pass

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

@freeciv.register
def economy_report_dialog_update():
    client.update_taxes()

@freeciv.register
def update_info_label():
    pass

@freeciv.register
def update_intel_dialog(id):
    pass

@freeciv.register
def activeunits_report_dialog_update():
    pass

@freeciv.register
def city_report_dialog_update():
    pass

@freeciv.register
def update_turn_done_button(restore):
    client._set_turn_button_state(restore)

class Client(object):
    def __init__(self):
        global client
        client = self
        self.next_time = time.time()
        self.cursor_pos = (0, 0)
        self.draw_patrol_lines = False
        self.out_window_callback = None
        self.turn_button_flip = False
        self.meetings = {}
    
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
        if self.out_window_callback:
            self.out_window_callback(text)
        print '[OutWindow]', text
    
    def end_turn(self):
        freeciv.func.key_end_turn()
    
    def chat(self, text):
        freeciv.func.send_chat(text)
    
    def draw_map(self, surf, pos):
        mapview = freeciv.func.get_mapview_store()
        surf.blit(mapview, pos)
    
    def draw_overview(self, surf, pos, scale):
        dest_surf = pygame.transform.smoothscale(window.overview_surface, scale)
        surf.blit(dest_surf, pos)
        pygame.draw.rect(surf, (255, 255, 255), pos + scale, 1)
    
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
            raise ConnectionError(buff)
    
    def escape(self):
        if self.draw_patrol_lines:
            self.key_event(pygame.KEYDOWN, pygame.K_ESCAPE)
            self.draw_patrol_lines = False
        else:
            self.quit()
    
    def disable_menus(self):
        print 'disable_menus'
    
    def get_unit_in_focus(self):
        units = freeciv.func.get_units_in_focus()
        if units:
            return actions.Unit(units[0])
        else:
            return None
    
    def disconnect(self):
        self.chat('/quit')
        freeciv.func.disconnect_from_server()
        
        global client
        client = None
    
    def get_tax_values(self):
        lux = freeciv.func.get_tax_value(True)
        science = freeciv.func.get_tax_value(False)
        tax = 100 - lux - science
        return tax, lux, science
    
    def set_tax_values(self, tax, lux, science):
        freeciv.func.set_tax_values(tax, lux, science)
    
    def get_gold(self):
        return freeciv.func.get_gold_amount()
    
    def get_gold_income(self):
        return freeciv.func.get_gold_income()
    
    def get_current_tech(self):
        return freeciv.func.get_current_tech()
    
    def get_techs(self):
        return map(Tech, freeciv.func.get_techs())
    
    def get_current_year_name(self):
        return freeciv.func.get_current_year_name()
    
    def get_governments(self):
        return map(Gov, freeciv.func.get_governments())
    
    def get_clients(self):
        return map(city.City, freeciv.func.get_cities())
        
    def _set_turn_button_state(self, restore):
        if not freeciv.func.get_turn_done_button_state():
            return
        
        if (restore and self.turn_button_flip) or not restore:
            self.turn_button_flip = not self.turn_button_flip
        
        self.set_turn_button_state(not self.turn_button_flip)
    
    def set_turn_button_state(self, enabled):
        print 'set_turn_button_state default', enabled

class Gov(object):
    def __init__(self, (index, name, changable)):
        self.name = name
        self.index = index
        self.changable = changable
    
    def change_to(self):
        freeciv.func.change_government(self.index)

class Tech(object):
    def __init__(self, (index, name, steps)):
        self.index = index
        self.name = name
        self.steps = steps
    
    def set_as_goal(self):
        freeciv.func.set_tech_goal(self.index)

def get_nations():
    return [
        (freeciv.func.get_name_of_nation_id(i),
         freeciv.func.city_style_of_nation_id(i), i)
        for i in xrange(freeciv.func.get_playable_nation_count()) ]

def get_nation_name(i):
    return freeciv.func.get_name_of_nation_id(i)
