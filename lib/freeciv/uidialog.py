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

import osutil
import time
import ui
import graphics

if osutil.is_desktop:
    import webbrowser

    def open_url(url):
        webbrowser.open_new_tab(url)
elif osutil.is_android:
    def open_url(url):
        raise NotImplementedError
        #pyjni.open_intent("android.intent.action.VIEW", url)

def inputbox(text, default='', finish=None, cancel=None):
    def _finish():
        if text.label:
            graphics.stop_text_input()
            finish(text.label)
            ui.back(allow_override=False)
        else:
            _cancel()

    def reset():
        text.set_text('')

    def _cancel():
        graphics.stop_text_input()
        if cancel: cancel()
        ui.back(allow_override=False)

    graphics.start_text_input()
    container = ui.LinearLayoutWidget()
    container.back = _cancel
    container.add(ui.Label('%s' % text))
    text = InputBox(default)
    container.add(text)
    container.focus = text
    panel = ui.HorizontalLayoutWidget(spacing=10)
    panel.add(ui.Button('OK', _finish))
    panel.add(ui.Button('Reset', reset))
    container.add(panel)
    ui.set(container)

class InputBox(ui.Label):
    def event(self, ev):
        if ev.type == graphics.const.TEXTINPUT:
            self.set_text(self.label + ev.text)
        elif ev.type == graphics.const.KEYDOWN:
            if ev.key == graphics.const.K_BACKSPACE:
                self.set_text(self.label[:-1])
