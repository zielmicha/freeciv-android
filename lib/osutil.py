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
import pygame
import time

try:
    import android
except ImportError:
    android = None

is_android = bool(android)
is_desktop = not is_android

def init():
    if android:
        android.init()
        android.map_key(android.KEYCODE_BACK, pygame.K_ESCAPE)

def get_android_data(append=''):
    chdir = os.getcwd()
    if chdir.startswith('/sdcard/'):
        chdir = chdir[len('/sdcard/'):]
    if chdir.startswith('/mnt/sdcard/'):
        chdir = chdir[len('/mnt/sdcard/'):]
    if chdir.endswith('/'):
        chdir = chdir[:-1]
    id = chdir
    return '/data/data/%s/%s' % (id, append)

def is_paused():
    if is_android:
        return android.check_pause()
    else:
        return sig_state == PAUSED

def wait_for_resume():
    if is_android:
        android.wait_for_resume()
    else:
        while sig_state == PAUSED:
            time.sleep(0.3)

if is_desktop:
    import signal
    
    print 'PID for pausing is', os.getpid()
    
    PAUSED = 1
    NOT_PAUSED = 0
    
    sig_state = NOT_PAUSED
    
    def _sig_pause(a, b):
        global sig_state
        sig_state = PAUSED
    
    def _sig_unpause(a, b):
        global sig_state
        sig_state = NOT_PAUSED
    
    signal.signal(signal.SIGUSR1, _sig_pause)
    signal.signal(signal.SIGUSR2, _sig_unpause)