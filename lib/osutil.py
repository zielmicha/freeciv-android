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
freeciv.osutil handles system-specific activity - mainly Android interaction.
'''

try:
    import android
except ImportError:
    android = None

    def get_internal_storage():
        return os.path.expanduser('~/.freeciv/android-internal')

else:
    from android import get_internal_storage


import os
import sys
import graphics
import time
from freeciv import features
from graphics import sdl_open as open_res

features.add_feature('app.emulatedpi', 60, type=int)

if android:
    import jnius
    import reflect as jnius_reflect

is_android = bool(android)
is_desktop = not is_android

def init():
    if android:
        android.map_key(android.KEYCODE_BACK, graphics.const.K_ESCAPE)
        android.map_key(android.KEYCODE_MENU, graphics.const.K_F1)

_jni_initted = False

def init_jni():
    global SDLActivity, Intent, Uri, _jni_initted
    if _jni_initted: return
    SDLActivity = jnius_reflect.autoclass('org.libsdl.app.SDLActivity')
    Intent = jnius_reflect.autoclass('android.content.Intent')
    Uri = jnius_reflect.autoclass('android.net.Uri')
    _jni_initted = True

def get_android_data(append=''):
    return get_internal_storage() + '/' + append

def get_external_storage():
    return '/mnt/sdcard/' + get_ident()

def get_ident():
    return get_internal_storage().strip('/').split('/')[-2]

def is_paused():
    return False

def wait_for_resume():
    pass

def get_android_version():
    if is_android:
        return 999 # TODO
    else:
        return None

def get_android_version_info():
    return version_map.get(get_android_version(), ('unknown', ''))

def open_market():
    print 'opening market'
    if is_android:
        # Which is better?
        open_url('https://play.google.com/store/apps/details?id=pl.org.zielinscy.freeciv')
        #open_url('market://details?id=' + get_ident())

def open_url(url, action='android.intent.action.VIEW'):
    print 'open url', url
    if is_android:
        init_jni()
        intent = Intent(action, Uri.parse(url))
        _get_activity().startActivity(intent)

def get_dpi():
    if is_android:
        init_jni()
        return _get_activity().getResources().getDisplayMetrics().density * 160
    else:
        return features.get('app.emulatedpi')

def _get_activity():
    return SDLActivity.mSingleton

version_map = {
    None: ('desktop', None),
    10000: ('devel', 'dev'),
    1: ('base', '1.0'),
    2: ('base', '1.1'),
    3: ('cupcake', '1.5'),
    4: ('donut', '1.6'),
    5: ('eclair', '2.0'),
    6: ('eclair', '2.0.1'),
    7: ('eclair', '2.1'),
    8: ('froyo', '2.2'),
    9: ('gingerbread', '2.3'),
    10: ('gingerbread', '2.3.3'),
    11: ('honeycomb', '3.0'),
    12: ('honeycomb', '3.1'),
    13: ('honeycomb', '3.2'),
    14: ('icecream sandwich', '4.0'),
    15: ('icecream sandwich', '4.0.3'),
}
