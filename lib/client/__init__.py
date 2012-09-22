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
import monitor
import features

import freeciv

import dialogs
import common
import window
import actions
import diplomacy
import city
import key
import misc

net_socket = -1
client = None
main = None

features.add_feature('debug.outwindow', default=False, type=bool)

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
    if client:
        client.console_line(text)
    else:
        print 'outwindow: %s\n' % text,

@freeciv.register
def real_meswin_dialog_update():
    count = freeciv.func.meswin_get_num_messages()
    client.update_meswin([ freeciv.func.meswin_get_message(i) for i in xrange(count) ])

@freeciv.register
def real_economy_report_dialog_update():
    client.update_taxes()

@freeciv.register
def update_turn_done_button(restore):
    client._set_turn_button_state(restore)

@freeciv.register
def handle_authentication_req(type, prompt):
    client.handle_authentication_req(prompt)

@freeciv.register
def popup_notify_goto_dialog(title, text, a, b):
    client.popup_notify(text)

class Client(object):
    def __init__(self, no_quit=False):
        global client
        client = self
        self.no_quit = no_quit
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
        monitor.log('outwindow', text)
        if features.get('debug.outwindow'):
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
    
    def overview_click(self, x, y):
        freeciv.func.py_overview_click(x, y)
    
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
        if not self.no_quit:
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
    
    def get_techs(self, level=11):
        return map(Tech, freeciv.func.get_techs(level))
    
    def get_current_year_name(self):
        return freeciv.func.get_current_year_name()
    
    def get_governments(self):
        return map(Gov, freeciv.func.get_governments())
    
    def get_cities(self):
        return map(city.City, freeciv.func.get_cities())
    
    def _set_turn_button_state(self, restore):
        if not freeciv.func.get_turn_done_button_state():
            return
        
        if (restore and self.turn_button_flip) or not restore:
            self.turn_button_flip = not self.turn_button_flip
        
        self.set_turn_button_state(not self.turn_button_flip)
    
    def set_turn_button_state(self, enabled):
        pass
    
    def authenticate(self, password):
        freeciv.func.authenticate(password)
    
    def get_players(self):
        return diplomacy.get_players()
    
    def get_player_with_id(self, id):
        return diplomacy.Player(freeciv.func.player_by_number(id))
    
    def get_playing(self):
        return diplomacy.Player(freeciv.func.get_playing())
    
    def toggle_full_labels(self):
        freeciv.func.request_toggle_city_full_bar()

    def get_caravan_options(self, unit, homecity, destcity):
        can_establish, can_trade, can_wonder = \
            freeciv.func.py_get_caravan_options(unit.handle, homecity.handle, destcity.handle)
        return can_establish, can_trade, can_wonder
        

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
    
    def set_as_current(self):
        freeciv.func.set_tech_research(self.index)

def get_nations():
    return [
        (freeciv.func.get_name_of_nation_id(i),
         freeciv.func.city_style_of_nation_id(i), i)
        for i in xrange(freeciv.func.get_playable_nation_count()) ]

def get_nation_name(i):
    return freeciv.func.get_name_of_nation_id(i)


