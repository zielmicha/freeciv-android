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
import graphics

import actions

dirkeymap = {
    graphics.const.K_UP: freeciv.const.DIR8_NORTH,
    graphics.const.K_RIGHT: freeciv.const.DIR8_EAST,
    graphics.const.K_LEFT: freeciv.const.DIR8_WEST,
    graphics.const.K_DOWN: freeciv.const.DIR8_SOUTH,
}

keymap = {
    graphics.const.K_g: [actions.ACTIVITY_GOTO],
    graphics.const.K_b: [actions.ACTIVITY_BUILD_CITY, actions.ACTIVITY_ADD_TO_CITY],
    graphics.const.K_r: [actions.ACTIVITY_ROAD, actions.ACTIVITY_RAILROAD, actions.ACTIVITY_MAGLEV],
    graphics.const.K_m: [actions.ACTIVITY_MINE],
    graphics.const.K_i: [actions.ACTIVITY_IRRIGATE, ], # FARMLAND?
    graphics.const.K_o: [actions.ACTIVITY_TRANSFORM],
    graphics.const.K_f: [actions.ACTIVITY_FORTIFYING, actions.ACTIVITY_FORTRESS, actions.ACTIVITY_FORTIFYING],
    graphics.const.K_SPACE: [actions.ACTIVITY_DONE],
}

def key(type, key):
    unit = actions.get_unit_in_focus()

    if type == graphics.const.KEYDOWN:
        if key in dirkeymap:
            direction = dirkeymap[key]
            freeciv.func.key_unit_move_direction(direction)
        if key == graphics.const.K_ESCAPE:
            freeciv.func.key_cancel_action()
        if unit:
            available = set(unit.iter_actions())
            if key in keymap:
                activities = keymap[key]
                for activity in activities:
                    if activity in available:
                        unit.perform_activity(activity)
