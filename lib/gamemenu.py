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

import ui
import pygame
import client

from client import freeciv

order_sprites_names = ('auto attack,auto connect,auto explore,'
    'auto settlers,build city,cutdown forest,plant forest,'
    'mine,irrigate,no orders,disband,fortify,goto,goto city,home city,nuke,'
    'paradrop,partol,pillage,railroad,road,sentry,unload,wait,'
    'forterss,fallout,pollutions,airbases,add to city,help build wonder,'
    'none,spy,none,return to,airlift,load'.split(','))

def get_order_sprite(name):
    if name not in order_sprites_names:
        name = 'none'
    i = order_sprites_names.index(name)
    return order_sprites[i][0]

class Menu(ui.LinearLayoutWidget):
    def __init__(self, client):
        ui.LinearLayoutWidget.__init__(self)
        self.client = client
        self.panel = ui.HorizontalLayoutWidget(spacing=4)
        self.add(self.panel)
        self.panel.add(ui.Label('loading...', color=(0, 255, 0)))
    
    def update(self, actions):
        self.panel.items = []
        self.items = [self.panel]
        if actions:
            joystick_layout = ui.LinearLayoutWidget()
            joystick = Joystick(client)
            joystick_layout.marginleft = self.client.ui.map.size[0] - joystick.size[0] - 10
            joystick_layout.add(joystick)
            self.items.insert(0, joystick_layout)
            for action_ident, action_name, action_length in actions:
                self.panel.add(Button(self.client, action_ident, action_name))
        
        self.update_layout()

class Button(object):
    def __init__(self, client, action_ident, action_name):
        self.client = client
        self.action_ident = action_ident
        self.action_name = action_name
        
        self.image = get_order_sprite(action_name)
        self.size = self.image.get_size()
        self.tooltip = None
    
    def draw(self, surf, pos):
        if self.image:
            surf.blit(self.image, pos)
    
    def event(self, ev):
        if ev.type == pygame.MOUSEBUTTONDOWN:
            x, y = ev.abs_pos
            y -= self.image.get_height()
            x -= self.image.get_width() / 2
            self.tooltip = ui.Tooltip(self.action_name, (x, y), color=(0, 255, 255))
            return ui.LOCK_MOUSE_EVENT
        if ev.type == pygame.MOUSEBUTTONUP:
            if self.tooltip:
                self.tooltip.remove()
            x, y = ev.pos
            if x < 0 or y < 0 or x > self.size[0] or y > self.size[1]:
                return
            self.click()
    
    def tick(self):
        pass
    
    def click(self):
        self.client.get_unit_in_focus().perform_activity(self.action_ident)

class Joystick(object):
    colors = {
        (0xff, 0xff, 0): 'n',
        (0, 0, 0x80): 'ne',
        (0, 0xff, 0xff): 'e',
        (0, 0xff, 0): 'se',
        (0xff, 0, 0): 's',
        (0, 0, 0): 'sw',
        (0xff, 0, 0xff): 'w',
        (0, 0, 0xff): 'nw',
        (255, 255, 255): '',
    }
    
    consts = {
        'n': freeciv.const.DIR8_NORTH,
        'ne': freeciv.const.DIR8_NORTHEAST,
        'nw': freeciv.const.DIR8_NORTHWEST,
        's': freeciv.const.DIR8_SOUTH,
        'se': freeciv.const.DIR8_SOUTHEAST,
        'sw': freeciv.const.DIR8_SOUTHWEST,
        'w': freeciv.const.DIR8_WEST,
        'e': freeciv.const.DIR8_EAST,
    }
    
    @staticmethod
    def init():
        Joystick.gfx = client.common.load_gfxfile('data/user/joystick.png').convert_alpha()
        Joystick.map = client.common.load_gfxfile('data/user/joystick-map.png').convert()
        Joystick.masks = dict(
            (name, client.common.load_gfxfile('data/user/joystick-mask-%s.png' % name).convert_alpha())
            for name in Joystick.colors.values() if name )
        
    
    def __init__(self, client):
        self.size = Joystick.gfx.get_size()
        self.client = client
        self.current = None
    
    def draw(self, surf, pos):
        surf.blit(Joystick.gfx, pos)
        if self.current:
            surf.blit(Joystick.masks[self.current], pos)
    
    def event(self, ev):
        if ev.type in (pygame.MOUSEBUTTONDOWN, pygame.MOUSEMOTION):
            dir = self.get_direction(ev.pos)
            self.current = dir
            if not dir:
                return False
        elif ev.type == pygame.MOUSEBUTTONUP:
            dir = self.get_direction(ev.pos)
            self.current = None
            if dir:
                self.do_action(dir)
            else:
                return False
    
    def unfocus(self):
        self.current = None
    
    def do_action(self, dir):
        freeciv.func.key_unit_move_direction(self.consts[dir])
    
    def get_direction(self, pos):
        try:
            color = Joystick.map.get_at(pos)[:3]
            return Joystick.colors.get(color, '')
        except IndexError:
            return ''
    
    def tick(self):
        pass

def init():
    Joystick.init()
    init_orders()

def init_orders():
    global order_sprites
    img_orders = client.common.load_gfxfile('data/user/theme_orders_buttons.png').convert_alpha()
    order_sprites = client.common.split_sprites(img_orders, start=(0, 1), each=(29, 31), size=(31, 29), num=(1, 38))
    
    for line in order_sprites:
        line[0] = pygame.transform.smoothscale(line[0], (56, 56))

