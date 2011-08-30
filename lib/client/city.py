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

import client
import common

@freeciv.register
def popup_city_dialog(city):
    client.client.popup_city_dialog(City(city))

@freeciv.register
def city_dialog_is_open(city):
    return False

@freeciv.register
def diplomat_handled_in_diplomat_dialog():
    return -1

class City(object):
    def __init__(self, handle):
        self.handle = handle
    
    def make_citymap(self):
        size = freeciv.func.get_citydlg_canvas_width(), freeciv.func.get_citydlg_canvas_height()
        canvas = common.canvas_create(size[0], size[1])
        freeciv.func.city_dialog_redraw_map(self.handle, canvas)
        return canvas
    
    def is_unhappy(self):
        return freeciv.func.city_unhappy(self.handle)
    
    def is_happy(self):
        return freeciv.func.city_happy(self.handle)
    
    def is_celebrating(self):
        return freeciv.func.city_celebrating(self.handle)
    
    def get_prod_int(self, mode, type):
        return freeciv.func.city_get_prod(self.handle, mode, type)
    
    def get_prod(self, mode, type):
        return self.get_prod_int(getattr(freeciv.const, 'MODE_' + mode.upper()), getattr(freeciv.const, 'O_' + type.upper()))
    
    def get_prods(self):
        s = []
        for mode in 'surplus,prod,waste'.split(','):
            s.append( '%s' % mode )
            for type in 'food,shield,trade,gold,science,luxury'.split(','):
                s.append( '    %s: %s' % (type, self.get_prod(mode, type)) )
            
        return '\n'.join(s)
    
    def get_size(self):
        return freeciv.func.city_get_size(self.handle)
    
    def get_turns_to_grow(self):
        return freeciv.func.city_get_turns_to_grow(self.handle)
    
    def get_granary_size(self):
        return freeciv.func.city_granary_size(self.get_size())
    
    def get_production_turns_to_build(self): # 999 == blocked
        return freeciv.func.city_production_turns_to_build(self.handle, 1)
    
    def get_production_image(self):
        return freeciv.func.city_get_production_image(self.handle)
    
    def get_production_cost(self):
        return freeciv.func.city_get_production_cost(self.handle)
    
    def get_production_name(self):
        return freeciv.func.city_get_production_name(self.handle)
    
    def get_shield_stock(self):
        return freeciv.func.city_get_shield_stock(self.handle)