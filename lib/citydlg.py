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
        self.units_in_city = ui.HorizontalLayoutWidget()
        self.setup_units_in_city()
        
        self.citypanel.add(ui.Label(self.city.get_name()))
        self.citypanel.add(self.get_citizen_icons())
        self.citypanel.add(self.canvas)
        self.citypanel.update_layout()
        self.citypanel.add(ui.ScrollWrapper(self.info_label,
                                            height=ui.screen_height - self.citypanel.size[1] - self.citypanel.spacing,
                                            width=self.canvas.size[0]))
        
        self.ui = self # ui.ScrollWrapper(self)
        
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
        self.prodpanel.add(ui.ScrollWrapper(self.units_in_city, width=340, height=120, ways=ui.SCROLL_WIDTH))
        self.prodpanel.add(ui.Button('Buildings in city', self.show_buildings))
        
        #print self.city.get_buildable_improvements()
        #print self.city.get_buildable_units()
        
        self.citypanel.update_layout()
        self.update_layout()
        #print self.city.get_production_cost()
    
    def setup_units_in_city(self):
        def focus(unit):
            unit.focus()
            ui.back()
        
        for unit in self.city.get_units():
            callback = functools.partial(focus, unit)
            panel = ui.LinearLayoutWidget(center=True)
            panel.add(ui.Image(unit.get_image(), callback=callback))
            panel.add(ui.Label(unit.get_name(), font=ui.consolefont, callback=callback))
            self.units_in_city.add(panel)
            self.units_in_city.add(ui.Spacing(10, 0))
    
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
    
    def show_buildings(self):
        buildings = self.city.get_built_improvements()
        
        panel = ui.LinearLayoutWidget()
        for handle, name in buildings:
            callback = functools.partial(lambda info: self.sell_dialog(*info), (name, handle))
            p = ui.HorizontalLayoutWidget()
            p.add(ui.Label(name))
            p.add(ui.Button('Sell', callback))
            panel.add(p)
        ui.set_dialog(panel, scroll=True)
        
        #ui.not_implemented()
    
    def sell_dialog(self, name, handle):
        if not self.city.can_sell(handle):
            ui.message('Cannot sell %s' % name)
        else:
            def do_sell():
                self.city.sell(handle)
                ui.back()
            cost = self.city.get_sell_price(handle)
            ui.ask('Sell %s for %d?' % (name, cost), do_sell)
    
    def change_prod(self, add=True):
        panel = ui.LinearLayoutWidget()
        
        things = self.city.get_buildable_improvements() + \
                    self.city.get_buildable_units()
        
        def change(type, handle):
            self.city.set_production(type, handle)
            ui.back()
        
        def add(handle, type, name, turns, stock, cost, ops, image):
            c = ui.HorizontalLayoutWidget()
            c.add(ui.Label('    ', image=image))
            c.add(ui.Label('%s %s/%s %s' % (name, stock, cost, ops), functools.partial(change, type, handle)))
            panel.add(c)
        
        for handle, type, name, turns, stock, cost, ops, img in things:
            add(handle, type, name, turns, stock, cost, ops or '', img)
        
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
    def __init__(self, dialog, city, scale_to=400):
        self.scale_to = scale_to
        self.city = city
        image = self.city.make_citymap()
        self.orig_size = size = image.get_size()
        self.size = (scale_to, size[1] * scale_to / size[0])
        self.image = pygame.transform.smoothscale(image, self.size)
        self.dialog = dialog
    
    def draw(self, surf, pos):
        surf.blit(self.image, pos)
    
    def event(self, ev):
        if ev.type == pygame.MOUSEBUTTONDOWN:
            self.city.map_click(*map(self._dev_to_map, ev.pos))
            # self.dialog.refresh()
    
    def _dev_to_map(self, pos):
        return pos * self.orig_size[0] / self.scale_to
    
    def tick(self):
        pass

def init():
    icons.init()