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
        
        self.citypanel.add(ui.Label(self.city.get_name()))
        self.citypanel.add(self.get_citizen_icons())
        self.citypanel.add(self.canvas)
        self.citypanel.add(self.info_label)
        
        self.ui = ui.ScrollWrapper(self)
        
        self.add(self.citypanel)
        self.add(self.prodpanel)
        
        self.unit_img = ui.Image(self.city.get_production_image())
        self.prodpanel.add(ui.Label(self.city.get_production_name(), font=ui.smallfont))
        
        stock = self.city.get_shield_stock()
        cost = self.city.get_production_cost()
        turns = self.city.get_production_turns_to_build()
        if cost != 999:
            self.prodpanel.add(ui.Label('%d/%d (%d turns)' % (stock, cost, turns), font=ui.smallfont))
        self.prodpanel.add(self.unit_img)
        prodbuttons = ui.HorizontalLayoutWidget(spacing=10)
        prodbuttons.add(ui.Label('Prod: '))
        prodbuttons.add(ui.Button('Change', lambda: self.change_prod(add=False)))
        prodbuttons.add(ui.Button('Buy', lambda: self.buy_prod()))
        #prodbuttons.add(ui.Button('Add', lambda: self.change_prod(add=False)))
        self.prodpanel.add(prodbuttons)
        self.prodpanel.add(ui.Button('Units in city', self.show_units))
        
        #print self.city.get_buildable_improvements()
        #print self.city.get_buildable_units()
        
        self.update_layout()
        #print self.city.get_production_cost()
    
    def show_units(self):
        def focus(unit):
            unit.focus()
            ui.back()
            ui.back()
        
        panel = ui.LinearLayoutWidget()
        for unit in self.city.get_units():
            name = unit.get_name()
            callback = functools.partial(focus, unit)
            panel.add(ui.Button(name, callback))
        ui.set_dialog(panel, scroll=True)
    
    def change_prod(self, add=True):
        panel = ui.LinearLayoutWidget()
        
        things = self.city.get_buildable_improvements() + \
                    self.city.get_buildable_units()
        
        def change(type, handle):
            self.city.set_production(type, handle)
            ui.back()
        
        def add(handle, type, name, turns, stock, cost, ops):
            panel.add(ui.Label('%s %s/%s %s' % (name, stock, cost, ops), functools.partial(change, type, handle)))
        
        for handle, type, name, turns, stock, cost, ops in things:
            add(handle, type, name, turns, stock, cost, ops or '')
        
        ui.set_dialog(panel, scroll=True)
    
    def buy_prod(self):
        def buy():
            self.city.buy()
            self.make_ui()
        
        price = self.city.get_buy_price()
        if not price:
            ui.message('Cannot buy')
        elif price > self.client.get_gold():
            ui.message('Too expensive - %d' % price)
        else:
            ui.ask('Buy %s for %d?' % (self.city.get_production_name(), price), buy)
    
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