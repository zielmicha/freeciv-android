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
import pygame

import actions

dirkeymap = {
    pygame.K_UP: freeciv.const.DIR8_NORTH,
    pygame.K_RIGHT: freeciv.const.DIR8_EAST,
    pygame.K_LEFT: freeciv.const.DIR8_WEST,
    pygame.K_DOWN: freeciv.const.DIR8_SOUTH,
}

keymap = {
    pygame.K_g: [actions.ACTIVITY_GOTO],
    pygame.K_b: [actions.ACTIVITY_BUILD_CITY, actions.ACTIVITY_ADD_TO_CITY],
    pygame.K_r: [actions.ACTIVITY_ROAD, actions.ACTIVITY_RAILROAD],
    pygame.K_m: [actions.ACTIVITY_MINE],
    pygame.K_i: [actions.ACTIVITY_IRRIGATE, ], # FARMLAND?
    pygame.K_o: [actions.ACTIVITY_TRANSFORM],
    pygame.K_f: [actions.ACTIVITY_FORTIFYING, actions.ACTIVITY_FORTRESS, actions.ACTIVITY_FORTIFYING],
    pygame.K_SPACE: [actions.ACTIVITY_DONE],
}

def key(type, key):
    unit = actions.get_unit_in_focus()
    
    if type == pygame.KEYDOWN:
        if key in dirkeymap:
            direction = dirkeymap[key]
            freeciv.func.key_unit_move_direction(direction)
        if key == pygame.K_ESCAPE:
            freeciv.func.key_cancel_action()
        if unit:
            available = set(unit.iter_actions())
            if key in keymap:
                activities = keymap[key]
                for activity in activities:
                    if activity in available:
                        unit.perform_activity(activity)

