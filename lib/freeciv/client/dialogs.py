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

import freeciv.client, sys
freeciv.client = sys.modules['freeciv.client'] # hack?
from freeciv import client
from freeciv import uidialog

import city
import actions

from freeciv.client import _freeciv as freeciv

client_page = 0


@freeciv.register
def get_current_client_page():
    return client_page

@freeciv.register
def real_set_client_page(page):
    global client_page
    client_page = page
    print 'set_client_page', page

    if page == freeciv.const.PAGE_START:
        page_start()
    elif page == freeciv.const.PAGE_GAME:
        page_game()

def is_page_open(name):
    return client_page == getattr(freeciv.const, 'PAGE_' + name)

def page_start():
    pass

def page_game():
    pass

@freeciv.register
def races_toggles_set_sensitive():
    pass

@freeciv.register
def meswin_dialog_is_open():
    return True

@freeciv.register
def popup_newcity_dialog(unit, default_name):
    uidialog.inputbox('What should we call our new city?', default_name,
                      finish=lambda text: freeciv.func.finish_city_at_unit(unit, text),
                      cancel=lambda: freeciv.func.cancel_city_at_unit(unit))

@freeciv.register
def unit_select_dialog_popup(tile):
    units = freeciv.func.get_units_at_tile(tile)
    client.client.unit_select_dialog_popup(map(actions.Unit, units))

@freeciv.register
def popup_caravan_dialog(unit, home_city, target_city, target_unit, target_tile, act_list):
    client.client.popup_caravan_dialog(actions.Unit(unit), city.City(home_city), city.City(target_city), actions.Unit(target_unit), target_tile, act_list)

@freeciv.register
def popup_diplomat_dialog(unit, tile):
    diplomat_action = DiplomatAction(unit, tile)
    client.client.popup_diplomat_dialog(diplomat_action)

@freeciv.register
def popup_incite_dialog(city, cost):
    action = client.client._last_diplomat_action
    client.client.popup_incite_dialog(action, cost,
                                      cost != freeciv.const.INCITE_IMPOSSIBLE_COST)

class DiplomatAction(object):
    def __init__(self, diplomat, tile):
        client.client._last_diplomat_action = self
        self.diplomat = diplomat
        self.tile = tile
        self.city = freeciv.func.tile_city(tile)
        self.spy = freeciv.func.unit_has_type_flag(diplomat, freeciv.const.F_SPY)
        units = freeciv.func.get_units_at_tile(tile)
        self.unit = units[0] if units else None
        print 'DiplomatAction diplomat=%s tile=%s city=%s unit=%s spy=%s' \
            % (self.diplomat, self.tile, self.city, None, self.spy)

    def can_do(self, const):
        return freeciv.func.diplomat_can_do_action(self.diplomat, const, self.tile)

    def get_actions(self):
        actions = [ freeciv.const.ACTION_ESTABLISH_EMBASSY,
                    freeciv.const.ACTION_SPY_BRIBE_UNIT,
                    freeciv.const.ACTION_SPY_INCITE_CITY,
                    freeciv.const.ACTION_SPY_INVESTIGATE_CITY,
                    freeciv.const.ACTION_SPY_SABOTAGE_CITY,
                    freeciv.const.ACTION_SPY_STEAL_TECH,
                    freeciv.const.ACTION_SPY_POISON,
                    freeciv.const.ACTION_SPY_SABOTAGE_UNIT]
        for action in actions:
            if self.can_do(action):
                yield action

    def perform_simple_action(self, action, value=0):
        freeciv.func.request_diplomat_action(action,
                                             freeciv.func.py_get_unit_id(self.diplomat),
                                             self._get_target_id(),
                                             value)

    def request_answer(self, action, value=0):
        freeciv.func.request_diplomat_answer(action,
                                             freeciv.func.py_get_unit_id(self.diplomat),
                                             self._get_target_id(),
                                             value)

    def _get_target_id(self):
        if self.city:
            return freeciv.func.py_get_city_id(self.city)
        elif self.unit:
            return freeciv.func.py_get_unit_id(self.unit)
        else:
            raise RuntimeError('DiplomatAction without a target')
