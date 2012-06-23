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
import math
import time
import features
import functools

from client import freeciv

features.add_feature('app.new_joystick', default=None, type=bool)
features.add_feature('app.joystick', default=None)

def get_joystick_type():
    sel = features.get('app.joystick')
    if sel:
        return sel
    else:
        new = features.get('app.new_joystick')
        if new == None:
            return 'tile'
        elif new:
            return 'new'
        else:
            return 'old'

order_sprites_names = ('auto attack,auto connect,auto explore,'
    'auto settlers,build city,cutdown forest,plant forest,'
    'mine,irrigate,no orders,disband,fortify,goto,goto city,home city,nuke,'
    'paradrop,partol,pillage,railroad,road,sentry,unload,wait,'
    'forterss,fallout,pollutions,airbases,transforms,add to city,help build wonder,'
    'none,spy,none,return to,airlift,load'.split(','))

confirm_actions = [client.actions.ACTIVITY_DISBAND]

def get_order_sprite(name):
    if name == 'center on unit':
        name = 'none'
    if name not in order_sprites_names:
        name = 'help build wonder'
    i = order_sprites_names.index(name)
    return order_sprites[i][0]

ZOOM_LEVELS = [0.3, 0.5, 0.7, 1, 1.3, 1.6, 2, 2.5]

class Menu(ui.LinearLayoutWidget):
    def __init__(self, client):
        ui.LinearLayoutWidget.__init__(self)
        self.client = client
        self.zoom_panel = ui.HorizontalLayoutWidget(spacing=4)
        self.zoom_panel.add(ui.Button('+', self.incr_zoom, force_width=20))
        self.zoom_panel.add(ui.Button(' - ', self.decr_zoom, force_width=20))
        self.zoom_level = ZOOM_LEVELS.index(1)
        self.panel = ui.HorizontalLayoutWidget(spacing=4)
        self.add(self.zoom_panel)
        self.add(self.panel)
        self.panel.add(ui.Label('loading...', color=(0, 255, 0)))
    
    def incr_zoom(self, i=1):
        self.zoom_level += i
        self.zoom_level = max(0, min(len(ZOOM_LEVELS) - 1, self.zoom_level))
        self.client.ui.map.zoom = ZOOM_LEVELS[self.zoom_level]
    
    def decr_zoom(self):
        self.incr_zoom(-1)
    
    def update(self, unit):
        self.panel.items = []
        self.items = [self.zoom_panel, self.panel]
        if unit:
            self.update_joystick()
            self.update_actions(unit)
            
        self.update_layout()
    
    def update_joystick(self):
        joystick_layout = ui.LinearLayoutWidget()
        j_type = get_joystick_type()
        if j_type == 'new':
            joystick = NewJoystick(client)
            joystick_layout.marginleft = self.client.ui.map.size[0] - joystick.size[0] - 50
        elif j_type == 'tile':
            joystick = TileJoystick(client)
            joystick_layout.marginleft = self.client.ui.map.size[0] - joystick.size[0] - 20
        else:
            joystick = Joystick(client)
            joystick_layout.marginleft = self.client.ui.map.size[0] - joystick.size[0] - 10
        joystick_layout.add(joystick)
        self.items.insert(0, joystick_layout)
    
    def update_actions(self, unit):
        image = unit.get_image()
        self.panel.add(ui.Button('', callback=lambda: self.show_action_list(unit),
                                 image=image, force_width=image.get_width(), force_height=image.get_height()))
        for action_ident, action_name, action_length in unit.get_actions():
            self.panel.add(Button(self.client, action_ident, action_name))
    
    def show_action_list(self, unit):
        def fcallback(action_ident):
            self.client.get_unit_in_focus().perform_activity(action_ident)
            ui.back()
        
        panel = ui.LinearLayoutWidget()
        
        for action_ident, action_name, action_length in unit.get_actions():
            callback = functools.partial(fcallback, action_ident)
            hor = ui.HorizontalLayoutWidget()
            hor.add(ui.Image(get_order_sprite(action_name), callback))
            hor.add(ui.Label('%s' % (action_name, ), callback))
            panel.add(hor)
        
        ui.set_dialog(panel, scroll=True)
        

class Button(object):
    def __init__(self, client, action_ident, action_name):
        self.client = client
        self.action_ident = action_ident
        self.action_name = action_name
        
        self.click_at = None
        self.image = get_order_sprite(action_name)
        self.size = self.image.get_size()
        self.tooltip = None
    
    def draw(self, surf, pos):
        if self.image:
            surf.blit(self.image, pos)
    
    def event(self, ev):
        if ev.type == pygame.MOUSEBUTTONDOWN:
            self.click_at = time.time()
            x, y = ev.abs_pos
            y -= self.image.get_height()
            x -= self.image.get_width() / 2
            self.tooltip = ui.Tooltip(self.action_name, (x, y-40), color=(0, 255, 255))
            return ui.LOCK_MOUSE_EVENT
        if ev.type == pygame.MOUSEBUTTONUP:
            if self.tooltip:
                self.tooltip.remove()
            if time.time() - 0.5 > self.click_at:
                return
            x, y = ev.pos
            if x < 0 or y < 0 or x > self.size[0] or y > self.size[1]:
                return
            self.click()
    
    def tick(self):
        pass
    
    def click(self):
        def do():
            self.client.get_unit_in_focus().perform_activity(self.action_ident)

        if self.action_ident in confirm_actions:
            ui.ask('Really %s?' % self.action_name, do)
        else:
            do()

class NewJoystick(object):
    small_radius = 35
    
    consts = {
        0: freeciv.const.DIR8_EAST,
        45: freeciv.const.DIR8_SOUTHEAST,
        90: freeciv.const.DIR8_SOUTH,
        135: freeciv.const.DIR8_SOUTHWEST,
        180: freeciv.const.DIR8_WEST,
        225: freeciv.const.DIR8_NORTHWEST,
        270: freeciv.const.DIR8_NORTH,
        315: freeciv.const.DIR8_NORTHEAST,
    }
    
    @staticmethod
    def init():
        pass
    
    def __init__(self, client):
        self.client = client
        self.size = (180, 180)
        self.current = None
        self.clicked = False
    
    def draw(self, surf, pos):
        px, py = pos
        cx, cy = px + self.size[0]/2, py + self.size[1]/2
        self._ellipse(surf, (230, 230, 255, 120), (cx-self.small_radius, cy-self.small_radius, 2*self.small_radius, 2*self.small_radius))
        if self.current is not None:
            self._ellipse(surf, (255, 255, 255, 70), pos + self.size)
            size = self.size[0]/2
            angle = math.radians(self.current)
            x, y = size*math.cos(angle), size*math.sin(angle)
            pygame.draw.line(surf, (255, 0, 0), (px+size, py+size), (px+size+x, py+size+y))
    
    def _ellipse(self, surf, color, rect):
        pygame.gfxdraw.filled_ellipse(surf, rect[0]+rect[3]/2, rect[1]+rect[3]/2, rect[2]/2, rect[3]/2, color)
    
    def event(self, ev):
        if hasattr(ev, 'pos'):
            relpos = (ev.pos[0] - self.size[0]/2, ev.pos[1] - self.size[1]/2)
        if ev.type == pygame.MOUSEBUTTONDOWN:
            if abs(relpos[0]) <= self.small_radius and abs(relpos[1]) <= self.small_radius:
                self.clicked = True
            else:
                return False
        if ev.type in (pygame.MOUSEBUTTONDOWN, pygame.MOUSEMOTION):
            if self.clicked:
                if abs(relpos[0]) > self.small_radius or abs(relpos[1]) > self.small_radius:
                    dir = self.get_direction(relpos)
                    self.current = dir
                else:
                    self.current = None
                return ui.LOCK_MOUSE_EVENT
            else:
                return False
        elif ev.type == pygame.MOUSEBUTTONUP:
            if self.current is not None:
                self.do_action(self.current)
            self.clicked = False
            self.current = None
    
    def unfocus(self):
        self.current = None
    
    def do_action(self, dir):
        freeciv.func.key_unit_move_direction(self.consts[dir])
    
    def get_direction(self, pos):
        angle = math.atan2(pos[0], pos[1])
        return (90 - int((math.degrees(angle)%360+22.5)/45) * 45) % 360
    
    def tick(self):
        pass

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


class TileJoystick(ui.LinearLayoutWidget):
    @staticmethod
    def init():
        pass
    
    def __init__(self, client):
        self.hidden = False
        spacing = 10
        
        super(TileJoystick, self).__init__(spacing=spacing)
        self.client = client
        
        b = functools.partial(TileButton, self)
        
        top = ui.HorizontalLayoutWidget(spacing=spacing)
        top.add(b(freeciv.const.DIR8_NORTHWEST))
        top.add(b(freeciv.const.DIR8_NORTH))
        top.add(b(freeciv.const.DIR8_NORTHEAST))
        self.add(top)
        
        center = ui.HorizontalLayoutWidget(spacing=spacing)
        center.add(b(freeciv.const.DIR8_WEST))
        center.add(b(None))
        center.add(b(freeciv.const.DIR8_EAST))
        self.add(center)
        
        bottom = ui.HorizontalLayoutWidget(spacing=spacing)
        bottom.add(b(freeciv.const.DIR8_SOUTHWEST))
        bottom.add(b(freeciv.const.DIR8_SOUTH))
        bottom.add(b(freeciv.const.DIR8_SOUTHEAST))
        self.add(bottom)
        
        self.update_layout()

class TileButton(object):
    active_bg = (255, 255, 200, 150)
    bg = (130, 100, 0, 90)
    fg = (150, 150, 50)
    
    def __init__(self, joystick, dir):
        self.size = (60, 60)
        self.dir = dir
        self.active = False
        self.joystick = joystick
    
    def draw(self, surf, pos):
        if self.dir != None and self.joystick.hidden:
            return 
        if self.active:
            color = self.active_bg
        else:
            color = self.bg
        ui.round_rect(surf, color, self.fg, pos + self.size)
    
    def tick(self):
        pass
    
    def unhover(self):
        self.active = False
    
    def event(self, event):
        if self.dir != None and self.joystick.hidden:
            return False
        if event.type == pygame.MOUSEBUTTONDOWN:
            self.active = True
        elif event.type == pygame.MOUSEBUTTONUP:
            self.active = False
            self.click()
    
    def click(self):
        if self.dir == None:
            self.joystick.hidden = not self.joystick.hidden
        else:    
            freeciv.func.key_unit_move_direction(self.dir)

def init():
    NewJoystick.init()
    Joystick.init()
    TileJoystick.init()
    init_orders()

def init_orders():
    global order_sprites
    img_orders = client.common.load_gfxfile('data/user/theme_orders_buttons.png').convert_alpha()
    order_sprites = client.common.split_sprites(img_orders, start=(0, 1), each=(29, 31), size=(31, 29), num=(1, 38))
    
    for line in order_sprites:
        line[0] = pygame.transform.smoothscale(line[0], (56, 56))

