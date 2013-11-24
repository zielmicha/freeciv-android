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

import traceback
import functools

import ui
from freeciv import uidialog
import osutil
import features

from freeciv import dropbox

class OptionsButton(ui.Button):
    def __init__(self, label, key):
        self.feature_label = label
        self.feature_key = key

        ui.Button.__init__(self, '', self._callback)

        self.make_button()

    def make_button(self):
        text = self.feature_label % features.get(self.feature_key)
        self.set_text(text)

    def _callback(self):
        def finish(val):
            try:
                features.set_perm(self.feature_key, val)
            except ValueError as e:
                ui.message(str(e), type='error')
            self.make_button()

        uidialog.inputbox('Value for %s' % self.feature_key, finish=finish)

class BoolOptionsButton(ui.Button):
    def __init__(self, label_t, label_f, key):
        self.label_t = label_t
        self.label_f = label_f
        self.feature_key = key

        ui.Button.__init__(self, '', self._callback)

        self.make_button()

    def make_button(self):
        text = self.label_t if features.get(self.feature_key) else self.label_f
        self.set_text(text)

    def _callback(self):
        try:
            val = features.get(self.feature_key)
            features.set_perm(self.feature_key, not val)
        except ValueError as e:
            ui.message(str(e), type='error')
        self.make_button()

class OptionsPanel(ui.LinearLayoutWidget):
    def add_feature(self, label, key):
        self.add(OptionsButton(label, key))

    def add_feature_bool(self, label_t, label_f, key):
        self.add(BoolOptionsButton(label_t, label_f, key))

def show_options():
    options = OptionsPanel(marginleft=10)
    options.add(ui.Label('Touch an option to change'))
    options.add_feature('Shutdown game after %d seconds of pause', 'app.shutdown')
    #options.add_feature_bool('New joystick', 'Old joystick', 'app.new_joystick')
    options.add(ui.Button('Change joystick', change_joystick))
    options.add(ui.Button('Change ruleset for new games', change_ruleset))
    st = 'Full city label toggle button:'
    options.add_feature_bool(st + ' show', st + ' hide', 'app.full_label_toggle_button')

    options.add(dropbox.DBButton('Login to Dropbox', lambda: dropbox.login()))

    if features.get('app.debug'):
        options.add(ui.Button('Debug', debug_menu))


    options.add(ui.Label('Freeciv for Android is licensed under GNU/GPL. \n' \
                         'Dropbox and Dropbox logo are trademarks of Dropbox, Inc.\n', ))
    ui.set(options)

def debug_menu():
    def fake_screen_size(size):
        import main
        main.main(size, init=False)

    def fake_screen_size_menu():
        menu = ui.Menu(center=False)
        for size in [(320, 240), (480, 320), (640, 480), (1024, 800), (1280, 800)]:
            menu.add(str(size), functools.partial(fake_screen_size, size))
        ui.set_dialog(menu, scroll=True)

    def change_feature():
        def finish(arg):
            try:
                features._parse_arg(arg)
            except Exception as e:
                traceback.print_exc()
                ui.message(str(e))

        uidialog.inputbox('name=key', finish=finish)

    def pernament_feature():
        def finish(arg):
            try:
                k, v = arg.split('=', 1)
                features.set_perm(k, v)
            except Exception as e:
                traceback.print_exc()
                ui.message(str(e))

        uidialog.inputbox('name=key', finish=finish)

    def show_features():
        s = '\n'.join( '%s=%s' % (k,v) for k, v in sorted(features.features.items()) )
        ui.set_dialog(ui.Label(s), scroll=True)

    def test_inputbox():
        import uidialog
        def finish(text):
            print 'got', text

        def cancel():
            print 'cancel'

        uidialog.inputbox('Query?', 'defaultval', finish=finish, cancel=cancel)

    def test_eval():
        import uidialog
        def finish(text):
            exec text

        uidialog.inputbox('Expr to exec?', '', finish=finish)


    menu = ui.Menu()

    menu.add('Fake screen size', fake_screen_size_menu)
    menu.add('Get screen size', lambda: ui.set_dialog(ui.Label(str(ui.screen_size))))
    menu.add('Change feature', change_feature)
    menu.add('Pernament feature', pernament_feature)
    menu.add('Show features', show_features)
    menu.add('Cause exception', lambda: 1/0)
    menu.add('Test Market URL', osutil.open_market)
    menu.add('Test inputbox', test_inputbox)
    menu.add('Eval', test_eval)

    ui.set(ui.ScrollWrapper(menu))

def change_ruleset():
    def set_ruleset(name):
        features.set_perm('app.ruleset', name)
        ui.back()

    rulesets = ['default', 'civ1', 'civ2']
    panel = ui.LinearLayoutWidget()

    for ruleset in rulesets:
        panel.add(ui.Button(ruleset, functools.partial(set_ruleset, ruleset)))

    ui.set_dialog(panel)

def change_joystick():
    def set_type(name):
        features.set_perm('app.joystick', name)
        ui.back()

    types = ['new', 'tile']
    panel = ui.LinearLayoutWidget()

    for type in types:
        panel.add(ui.Button(type.capitalize(), functools.partial(set_type, type)))

    ui.set_dialog(panel)
