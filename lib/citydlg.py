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

import client
import icons

import pygame
import functools

class Dialog(ui.HorizontalLayoutWidget):
    def __init__(self, client, city):
        super(Dialog, self).__init__()
        self.client = client
        self.city = city
        
        self.make_ui()
    
    def make_ui(self):
        self.items = []
        self.canvas = CityCanvas(self, self.city)
        self.info_label = self.get_labels()
        self.citypanel = ui.LinearLayoutWidget()
        self.prodpanel = ui.LinearLayoutWidget()
        
        self.citypanel.add(self.get_citizen_icons())
        self.citypanel.add(self.canvas)
        self.citypanel.add(self.info_label)
        
        self.ui = ui.ScrollWrapper(self)
        
        self.add(self.citypanel)
        self.add(self.prodpanel)
        
        self.unit_img = ui.Image(self.city.get_production_image())
        self.prodpanel.add(ui.Label(self.city.get_production_name()))
        
        stock = self.city.get_shield_stock()
        cost = self.city.get_production_cost()
        turns = self.city.get_production_turns_to_build()
        if cost != 999:
            self.prodpanel.add(ui.Label('%d/%d (%d turns)' % (stock, cost, turns)))
        self.prodpanel.add(self.unit_img)
        
        self.update_layout()
        #print self.city.get_production_cost()
    
    def get_citizen_icons(self):
        def rotate_specialist(i):
            self.city.rotate_specialist(i)
            # self.refresh()
        
        panel = ui.HorizontalLayoutWidget(spacing=0)
        index = 0
        for name, count in self.city.get_citizens():
            for i in xrange(count):
                try:
                    icon = icons.get_small_image('%s-%d' % (name, i % 2)) # man and woman
                except KeyError:
                    icon = icons.get_small_image(name) # elvis, taxman, scientist
                panel.add(ui.Image(icon, functools.partial(rotate_specialist, index)))
                index += 1
        return panel
    
    def refresh(self):
        self.make_ui()
    
    def tick(self):
        super(Dialog, self).tick()
        self.client.tick()
    
    def get_labels(self):
        panel = ui.HorizontalLayoutWidget(spacing=10)
        panel_a = ui.LinearLayoutWidget(spacing=0)
        panel_b = ui.LinearLayoutWidget(spacing=0)
        panel.add(panel_a)
        panel.add(panel_b)
        
        def add(a, b):
            font = ui.consolefont
            panel_a.add(ui.Label(a, font=font))
            panel_b.add(ui.Label(str(b), font=font))
        
        def plus(n):
            return '+%d' % n if n > 0 else '%s' % n
        
        def add_basic(title, name):
            surplus = plus(self.city.get_prod('surplus', name))
            add(title, '%s (%s)' % (self.city.get_prod('prod', name), surplus))
        
        add_basic('Food', 'food')
        add_basic('Production', 'shield')
        add_basic('Trade', 'trade')
        
        add('', '')
        
        add_basic('Gold', 'gold')
        add('Science', self.city.get_prod('prod', 'science'))
        add('Luxury', self.city.get_prod('prod', 'luxury'))
        
        add('', '')
        
        add('Corruption', self.city.get_prod('waste', 'trade'))
        
        return panel

class CityCanvas(object):
    def __init__(self, dialog, city):
        self.city = city
        self.image = self.city.make_citymap()
        self.size = self.image.get_size()
        self.dialog = dialog
    
    def draw(self, surf, pos):
        surf.blit(self.image, pos)
    
    def event(self, ev):
        if ev.type == pygame.MOUSEBUTTONDOWN:
            self.city.map_click(*ev.pos)
            # self.dialog.refresh()
    
    def tick(self):
        pass

def init():
    icons.init()