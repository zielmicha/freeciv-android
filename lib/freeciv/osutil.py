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

import os
import sys
import graphics
import time
import features
from graphics import sdl_open as open_res

features.add_feature("app.disable_android_pause", type=bool, default=False)

try:
    import android
except ImportError:
    android = None
else:
    from android import get_internal_storage

is_android = bool(android)
is_desktop = not is_android

def init():
    if android:
        android.map_key(android.KEYCODE_BACK, graphics.const.K_ESCAPE)
        android.map_key(android.KEYCODE_MENU, graphics.const.K_F1)

def get_android_data(append=''):
    return get_internal_storage() + '/' + append

def get_external_storage():
    ident = get_internal_storage().strip('/').split('/')[-2]
    return '/mnt/sdcard/' + ident

def is_paused():
    return False

def wait_for_resume():
    pass

def get_android_version():
    if is_android:
        return 999 # TODO
    else:
        return None

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

def get_android_version_info():
    return version_map.get(get_android_version(), ('unknown', ''))
