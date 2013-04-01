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

if osutil.is_desktop:
    import webbrowser

    def open_url(url):
        webbrowser.open_new_tab(url)
elif osutil.is_android:
    def open_url(url):
        raise NotImplementedError
        #pyjni.open_intent("android.intent.action.VIEW", url)

def inputbox(text, default=''):
    raise NotImplementedError
