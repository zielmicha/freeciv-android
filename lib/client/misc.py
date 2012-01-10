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
'''
Callbacks that do nothing.
'''

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

@freeciv.register
def option_gui_add(arg):
    pass

@freeciv.register
def option_gui_update(arg):
    pass

@freeciv.register
def update_info_label():
    pass

@freeciv.register
def update_intel_dialog(id):
    pass

@freeciv.register
def activeunits_report_dialog_update():
    pass

@freeciv.register
def city_report_dialog_update():
    pass

@freeciv.register
def real_units_report_dialog_update():
    pass

@freeciv.register
def real_players_dialog_update():
    pass

@freeciv.register
def set_city_names_font_sizes(a, b):
    pass

@freeciv.register
def popdown_help_dialog():
    pass


@freeciv.register
def close_all_diplomacy_dialogs():
    pass

@freeciv.register
def popdown_all_game_dialogs():
    pass

@freeciv.register
def popdown_races_dialog():
    pass

@freeciv.register
def set_turn_done_button_state(enabled):
    pass

@freeciv.register
def update_conn_list_dialog():
    pass

@freeciv.register
def refresh_spaceship_dialog(n):
    pass

@freeciv.register
def close_connection_dialog():
    pass

@freeciv.register
def real_conn_list_dialog_update():
    pass

@freeciv.register
def real_science_report_dialog_update():
    pass

@freeciv.register
def real_focus_units_changed():
    pass

@freeciv.register
def voteinfo_gui_update():
    pass

@freeciv.register
def real_menus_init():
    pass

@freeciv.register
def real_players_dialog_update():
    pass

@freeciv.register
def popdown_all_city_dialogs():
    pass

@freeciv.register
def option_dialog_popdown(arg):
    pass

@freeciv.register
def gui_clear_theme():
    pass

@freeciv.register
def real_city_report_dialog_update():
    pass

@freeciv.register
def refresh_unit_city_dialogs(city_handle):
    pass