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

from freeciv.client import _freeciv as freeciv
from freeciv import client
import city

# Activity list: see freeciv-src/common/fc_types.h
# We're still using old values as ACTIVITY_ROAD and ACTIVITY_RAILROAD instead of ACTIVITY_GEN_ROAD
# but this is not a problem because these values are not sent to the server.
ACTIVITY_IDLE = 0
ACTIVITY_POLLUTION = 1
ACTIVITY_ROAD = 2
ACTIVITY_MINE = 3
ACTIVITY_IRRIGATE = 4
ACTIVITY_FORTIFIED = 5
ACTIVITY_FORTRESS = 6
ACTIVITY_SENTRY = 7
ACTIVITY_RAILROAD = 8
ACTIVITY_PILLAGE = 9
ACTIVITY_GOTO = 10
ACTIVITY_EXPLORE = 11
ACTIVITY_TRANSFORM = 12
# ACTIVITY_UNKNOWN = 13
ACTIVITY_AIRBASE = 14
ACTIVITY_FORTIFYING = 15
ACTIVITY_FALLOUT = 16
# ACTIVITY_PATROL_UNUSED = 17
ACTIVITY_MAGLEV = 17
ACTIVITY_BASE = 18
ACTIVITY_GEN_ROAD = 19
ACTIVITY_CONVERT = 20 # TODO: to implement

ACTIVITY_DISBAND = 1001
ACTIVITY_WAIT = 1002
ACTIVITY_DONE = 1003
ACTIVITY_ADD_TO_CITY = 1004
ACTIVITY_BUILD_CITY = 1005
ACTIVITY_PARADROP = 1007
ACTIVITY_CHANGE_HOMECITY = 1008
ACTIVITY_LOAD = 1009
ACTIVITY_UNLOAD = 1010

ACTIVITY_CENTER_ON_UNIT = 2003
ACTIVITY_UPGRADE = 2004

# freeciv-src/common/actions.h (+ 3000 to avoid collision with activities)
ACTION_MIN_VALUE=3000
ACTION_ESTABLISH_EMBASSY=3000
ACTION_SPY_INVESTIGATE_CITY=3001
ACTION_SPY_POISON=3002
ACTION_SPY_STEAL_GOLD=3003
ACTION_SPY_SABOTAGE_CITY=3004
ACTION_SPY_TARGETED_SABOTAGE_CITY=3005
ACTION_SPY_STEAL_TECH=3006
ACTION_SPY_TARGETED_STEAL_TECH=3007
ACTION_SPY_INCITE_CITY=3008
ACTIVITY_ESTABLISH_TRADE_ROUTE=3009
ACTION_MARKETPLACE=3010
ACTIVITY_HELP_BUILD_WONDER=3011
ACTION_SPY_BRIBE_UNIT=3012
ACTION_SPY_SABOTAGE_UNIT=3013
ACTION_MAX_VALUE=3013

def py_action_to_freeciv_action(py_action):
    if py_action < ACTION_MIN_VALUE or py_action > ACTION_MAX_VALUE:
        return -1
    return py_action - ACTION_MIN_VALUE

def freeciv_action_target_city_to_py_action(act_id):
    return act_id + ACTION_MIN_VALUE

BASE_GUI_FORTRESS = 0
BASE_GUI_AIRBASE = 1

ROCO_ROAD = 0
ROCO_RAILROAD = 1

activities = dict( (k,v) for k,v in globals().items() if k.startswith('ACTIVITY_' ) )
activity_names = dict( (v, k) for k,v in activities.items() )

action_names = {
    'done': 'no orders',
    'fortyfing': 'fortify',
    'explore': 'auto explore',
}

class Unit(object):
    def __init__(self, handle):
        self.handle = handle

    def get_properties(self):
        return freeciv.func.get_unit_properties(self.handle)

    def iter_actions(self):
        id, tileid, city, terrain_name = self.get_properties()

        yield ACTIVITY_CENTER_ON_UNIT
        yield ACTIVITY_GOTO
        yield ACTIVITY_DISBAND
        yield ACTIVITY_WAIT
        yield ACTIVITY_DONE

        if freeciv.func.unit_can_add_or_build_city(id):
            if city:
                yield ACTIVITY_ADD_TO_CITY
            else:
                yield ACTIVITY_BUILD_CITY

        if freeciv.func.unit_can_help_build_wonder_here(id):
            yield ACTIVITY_HELP_BUILD_WONDER

        if freeciv.func.can_unit_paradrop(id):
            yield ACTIVITY_PARADROP

        if freeciv.func.can_unit_change_homecity(id):
            yield ACTIVITY_CHANGE_HOMECITY

        if freeciv.func.can_unit_upgrade(self.handle):
            yield ACTIVITY_UPGRADE

        if freeciv.func.get_possible_unit_base_name(id, BASE_GUI_AIRBASE):
            yield ACTIVITY_AIRBASE

        if freeciv.func.get_possible_unit_base_name(id, BASE_GUI_FORTRESS):
            yield ACTIVITY_FORTRESS

        if freeciv.func.can_unit_do_activity_road(id, ROCO_ROAD):
            yield ACTIVITY_ROAD
        elif freeciv.func.can_unit_do_activity_road(id, ROCO_RAILROAD):
            yield ACTIVITY_RAILROAD
        elif freeciv.func.can_unit_do_activity_any_road(id):
            yield ACTIVITY_MAGLEV

        standard_activities = [
            ACTIVITY_IRRIGATE,
            ACTIVITY_MINE,
            ACTIVITY_TRANSFORM,
            ACTIVITY_FORTIFYING,
            ACTIVITY_POLLUTION,
            ACTIVITY_FALLOUT,
            ACTIVITY_SENTRY,
            ACTIVITY_PILLAGE,
            ACTIVITY_EXPLORE
        ]

        for a_ident in standard_activities:
            if freeciv.func.can_unit_do_activity(id, a_ident):
                yield a_ident

    def get_actions(self):
        return [ (ident, self.get_action_name(ident), self.get_action_time(ident)) for ident in self.iter_actions() ]

    def get_action_time(self, type):
        if type > 1000:
            return 0
        else:
            return freeciv.func.py_tile_activity_time(type, self.get_tile())

    def get_action_name(self, type):
        if type in [ACTIVITY_FORTRESS, ACTIVITY_AIRBASE]:
            base_gui_type = BASE_GUI_FORTRESS
            if type == ACTIVITY_AIRBASE:
                base_gui_type = BASE_GUI_AIRBASE
            return freeciv.func.get_possible_unit_base_name(self.handle, base_gui_type)
        def_name = activity_names[type][len('ACTIVITY_'):].lower().replace('_', ' ')
        if def_name in action_names:
            return action_names[def_name]
        return def_name

    def get_tile(self):
        id, tileid, city, terrain_name = self.get_properties()
        return tileid

    def get_terrain_name(self):
        id, tileid, city, terrain_name = self.get_properties()
        return terrain_name

    def get_name(self):
        return freeciv.func.get_unit_name(self.handle)

    def get_image(self):
        return freeciv.func.get_unit_image(self.handle)

    def focus(self):
        freeciv.func.request_new_unit_activity(self.handle, ACTIVITY_IDLE)
        freeciv.func.unit_focus_set(self.handle)

    def perform_activity(self, ident, target=0):
        # Warning! Safe to use only when `self` is in focus.
        id, tileid, city, terrain_name = self.get_properties()
        if ident == ACTIVITY_GOTO:
            freeciv.func.key_unit_goto()
        elif ident == ACTIVITY_ROAD:
            freeciv.func.key_unit_road()
        elif ident == ACTIVITY_RAILROAD:
            freeciv.func.key_unit_road()
        elif ident == ACTIVITY_MAGLEV:
            freeciv.func.key_unit_road()
        elif ident == ACTIVITY_BUILD_CITY or ident == ACTIVITY_ADD_TO_CITY:
            freeciv.func.key_unit_build_city()
        #elif ident == ACTIVITY_:
        #    freeciv.func.key_unit_trade_route()
        elif ident == ACTIVITY_IRRIGATE:
            freeciv.func.key_unit_irrigate()
        elif ident == ACTIVITY_MINE:
            freeciv.func.key_unit_mine()
        elif ident == ACTIVITY_TRANSFORM:
            freeciv.func.key_unit_transform()
        elif ident == ACTIVITY_FORTIFYING:
            freeciv.func.key_unit_fortify()
        elif ident == ACTIVITY_POLLUTION:
            freeciv.func.key_unit_pollution()
        elif ident == ACTIVITY_PARADROP:
            freeciv.func.key_unit_paradrop()
        elif ident == ACTIVITY_FALLOUT:
            freeciv.func.key_unit_fallout()
        elif ident == ACTIVITY_SENTRY:
            freeciv.func.key_unit_sentry()
        elif ident == ACTIVITY_PILLAGE:
            freeciv.func.key_unit_pillage()
        #elif ident == ACTIVITY_:
        #    freeciv.func.key_unit_homecity()
        #elif ident == ACTIVITY_:
        #    freeciv.func.key_unit_unload_all()
        elif ident == ACTIVITY_WAIT:
            freeciv.func.key_unit_wait()
        elif ident == ACTIVITY_DONE:
            freeciv.func.key_unit_done()
        elif ident == ACTIVITY_DISBAND:
            freeciv.func.key_unit_disband()
        elif ident == ACTIVITY_CHANGE_HOMECITY:
            freeciv.func.key_unit_homecity()
        elif ident == ACTIVITY_FORTRESS:
            freeciv.func.key_unit_fortress()
        elif ident == ACTIVITY_AIRBASE:
            freeciv.func.key_unit_airbase()
        elif ident == ACTIVITY_EXPLORE:
            freeciv.func.key_unit_auto_explore()
        elif ident == ACTIVITY_HELP_BUILD_WONDER:
            freeciv.func.py_caravan_help_build_wonder(self.handle, target)
        elif ident == ACTIVITY_ESTABLISH_TRADE_ROUTE:
            freeciv.func.py_caravan_establish_trade(self.handle, target)
        elif ident == ACTIVITY_CENTER_ON_UNIT:
            freeciv.func.request_center_focus_unit()
        elif ident == ACTIVITY_UPGRADE:
            freeciv.func.request_unit_upgrade(self.handle)
        else:
            freeciv_action = py_action_to_freeciv_action(ident)
            if freeciv_action >= 0:
                if ident == ACTION_SPY_BRIBE_UNIT or ident == ACTION_SPY_SABOTAGE_UNIT:
                    freeciv.func.py_request_do_action_target_unit(freeciv_action, self.handle, target)
                else:
                    freeciv.func.py_request_do_action(freeciv_action, self.handle, target)
            else:
                print 'Unsupported action', ident

    def get_activity_string(self):
        return freeciv.func.get_activity_str(self.handle)

    def get_home_citiy(self):
        home_city = freeciv.func.get_home_citiy(self.handle)
        if home_city:
            return city.City(home_city)
        else:
            return None

def get_unit_in_focus():
    units = freeciv.func.get_units_in_focus()
    if units:
        return Unit(units[0])
    else:
        return None

@freeciv.register
def real_menus_update():
    units = freeciv.func.get_units_in_focus()
    if not units:
        client.client.disable_menus()
    else:
        first_unit = Unit(units[0])
        client.client.update_menus(first_unit)
