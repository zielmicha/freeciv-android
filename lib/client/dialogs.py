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

@freeciv.register
def popup_unit_select_dialog(tile):
    units = freeciv.func.get_units_at_tile(tile)
    client.client.popup_unit_select_dialog(map(actions.Unit, units))