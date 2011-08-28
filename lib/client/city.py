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

@freeciv.register
def popup_city_dialog(city):
    pass #client.client.popup_city_dialog(City(city))

@freeciv.register
def city_dialog_is_open(city):
    return False

@freeciv.register
def diplomat_handled_in_diplomat_dialog():
    return -1

class City(object):
    def __init__(self, handle):
        self.handle = handle