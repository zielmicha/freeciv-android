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
    try:
        import easygui
    except ImportError:
        print '---------------------'
        print 'import easygui FAILED'
        print 'WILL USE raw_input!!'
        print '----------------------'
        def inputbox(text, default=''):
            return raw_input('%s [%s]' % text_default) or default
    else:
        def inputbox(text, default=''):
            return easygui.enterbox(text, default=default)

    import webbrowser

    def open_url(url):
        webbrowser.open_new_tab(url)

elif osutil.is_android:

    def inputbox(text, default='', title=''):
        raise NotImplementedError

    def open_url(url):
        raise NotImplementedError
        #pyjni.open_intent("android.intent.action.VIEW", url)
