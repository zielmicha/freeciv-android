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

import actions

client_page = 0

@freeciv.register
def set_city_names_font_sizes(a, b):
    pass

@freeciv.register
def popdown_help_dialog():
    pass

@freeciv.register
def update_players_dialog():
    pass

@freeciv.register
def update_report_dialogs():
    pass

@freeciv.register
def close_connection_dialog():
    pass

@freeciv.register
def get_client_page():
    return client_page

@freeciv.register
def set_client_page(page):
    global client_page
    client_page = page
    print 'set_client_page', page
    
    if page == freeciv.const.PAGE_START:
        print 'page_start'
        page_start()
    elif page == freeciv.const.PAGE_GAME:
        print 'page_game'
        page_game()

def page_start():
    freeciv.func.send_chat('/start')

def page_game():
    pass

@freeciv.register
def races_toggles_set_sensitive():
    pass

@freeciv.register
def popdown_all_city_dialogs():
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
def is_meswin_open():
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

@freeciv.register
def popup_unit_select_dialog(tile):
    units = freeciv.func.get_units_at_tile(tile)
    client.client.popup_unit_select_dialog(map(actions.Unit, units))