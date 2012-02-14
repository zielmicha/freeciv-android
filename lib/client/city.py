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
import actions

SP_ELVIS, SP_SCIENTIST, SP_TAXMAN = range(3)

VUT_NONE, VUT_ADVANCE, VUT_GOVERNMENT, VUT_IMPROVEMENT, VUT_SPECIAL, \
VUT_TERRAIN, VUT_NATION, VUT_UTYPE, VUT_UTFLAG, VUT_UCLASS, VUT_UCFLAG, \
VUT_OTYPE, VUT_SPECIALIST, VUT_MINSIZE, VUT_AI_LEVEL, VUT_TERRAINCLASS, \
VUT_BASE, VUT_MINYEAR, VUT_TERRAINALTER, VUT_CITYTILE, VUT_LAST = range(21)

@freeciv.register
def real_city_dialog_popup(city):
    client.client.popup_city_dialog(City(city))

@freeciv.register
def city_dialog_is_open(city):
    return client.client.city_dialog_is_open(City(city))

@freeciv.register
def real_city_dialog_refresh(city):
    return client.client.refresh_city_dialog(City(city))

@freeciv.register
def real_city_report_update_city(city):
    return client.client.refresh_city_dialog(City(city))

@freeciv.register
def city_report_dialog_update_city(city):
    return client.client.refresh_city_dialog(City(city))

@freeciv.register
def diplomat_handled_in_diplomat_dialog():
    return -1

class City(object):
    def __init__(self, handle):
        self.handle = handle
    
    def __hash__(self):
        return self.handle
    
    def __eq__(self, other):
        return isinstance(other, City) and self.handle == other.handle
    
    def make_citymap(self):
        size = freeciv.func.get_citydlg_canvas_width(), freeciv.func.get_citydlg_canvas_height()
        canvas = common.canvas_create(size[0], size[1])
        freeciv.func.city_dialog_redraw_map(self.handle, canvas)
        return canvas
    
    def get_citizens(self):
        yield 'happy', freeciv.func.city_get_citizen_count(self.handle, False, freeciv.const.CITIZEN_HAPPY)
        yield 'content', freeciv.func.city_get_citizen_count(self.handle, False, freeciv.const.CITIZEN_CONTENT)
        yield 'unhappy', freeciv.func.city_get_citizen_count(self.handle, False, freeciv.const.CITIZEN_UNHAPPY)
        yield 'angry', freeciv.func.city_get_citizen_count(self.handle, False, freeciv.const.CITIZEN_ANGRY)
        yield 'elvis', freeciv.func.city_get_citizen_count(self.handle, True, SP_ELVIS)
        yield 'scientist', freeciv.func.city_get_citizen_count(self.handle, True, SP_SCIENTIST)
        yield 'taxman', freeciv.func.city_get_citizen_count(self.handle, True, SP_TAXMAN)
    
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
    
    def get_name(self):
        return freeciv.func.city_name(self.handle)
    
    def rotate_specialist(self, index):
        freeciv.func.city_rotate_specialist(self.handle, index)
    
    def map_click(self, x, y):
        freeciv.func.city_map_click(self.handle, x, y)
    
    def get_buildable_improvements(self):
        return freeciv.func.get_buildable_improvements_in_city(self.handle)
    
    def get_buildable_units(self):
        return freeciv.func.get_buildable_units_in_city(self.handle)
    
    def set_production(self, type, handle):
        freeciv.func.city_change_production_type(self.handle, type, handle)
    
    def get_built_improvements(self):
        return freeciv.func.get_built_improvements_in_city(self.handle)
    
    def get_units(self):
        return [ actions.Unit(unit) for unit in freeciv.func.get_units_present_in_city(self.handle) ]
    
    def get_buy_price(self):
        if freeciv.func.city_can_buy(self.handle):
            return freeciv.func.city_production_buy_gold_cost(self.handle)
        else:
            return None
    
    def buy(self):
        freeciv.func.city_buy_production(self.handle)

    def get_sell_price(self, handle):
        return freeciv.func.impr_sell_gold(handle)
    
    def can_sell(self, handle):
        return freeciv.func.can_city_sell_building(self.handle, handle)
    
    def sell(self, handle):
        freeciv.func.city_sell_improvement_type(self.handle, handle)
    