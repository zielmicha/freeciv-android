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

@freeciv.register
def get_gui_specific_themes_directories():
    return ['data']

@freeciv.register
def get_useable_themes_in_directory(path):
    return []

@freeciv.register
def isometric_view_supported():
    return 1

@freeciv.register
def overhead_view_supported():
    return 1

@freeciv.register
def ui_exit():
    pass