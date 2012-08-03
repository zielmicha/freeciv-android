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
import uidialog

import city
import actions

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
    text = uidialog.inputbox('What should we call our new city?', default_name)
    while text:
        try:
            text.encode('ascii')
        except UnicodeError:
            text = uidialog.inputbox('Please use only latin characters!', default_name)
        else:
            break
    if text:
        freeciv.func.finish_city_at_unit(unit, text)
    else:
        freeciv.func.cancel_city_at_unit(unit)

@freeciv.register
def popup_unit_select_dialog(tile):
    units = freeciv.func.get_units_at_tile(tile)
    client.client.popup_unit_select_dialog(map(actions.Unit, units))

@freeciv.register
def popup_caravan_dialog(unit, home_city, dest_city):
    client.client.popup_caravan_dialog(actions.Unit(unit), city.City(home_city), city.City(dest_city))

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
        actions = [ freeciv.const.DIPLOMAT_MOVE,
                    freeciv.const.DIPLOMAT_EMBASSY,
                    freeciv.const.DIPLOMAT_BRIBE,
                    freeciv.const.DIPLOMAT_INCITE,
                    freeciv.const.DIPLOMAT_INVESTIGATE,
                    freeciv.const.DIPLOMAT_SABOTAGE,
                    freeciv.const.DIPLOMAT_STEAL,
                    freeciv.const.SPY_POISON,
                    freeciv.const.SPY_SABOTAGE_UNIT,
                    freeciv.const.DIPLOMAT_ANY_ACTION]
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
