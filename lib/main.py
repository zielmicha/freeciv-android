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

import time
import select
import pygame
import sys
import osutil
import thread
import os
import random
import tarfile
import copy
import functools
import progress

import save
import uidialog
import gamescreen
import ui
import client

def new_game():
    save.new_game()

def client_main():
    menu = ui.Menu()
    
    menu.add('New game', new_game)
    menu.add('Load game', save.load_dialog)
    menu.add('Debug', debug_menu)
    
    ui.set(menu)
    
    ui.main()

def debug_menu():
    def fake_screen_size(size):
        main(size, init=False)
    
    def fake_screen_size_menu():
        menu = ui.Menu(center=False)
        for size in [(320, 240), (480, 320), (640, 480)]:
            menu.add(str(size), functools.partial(fake_screen_size, size))
        ui.set_dialog(menu, scroll=True)
    
    menu = ui.Menu()
    
    menu.add('Fake screen size', fake_screen_size_menu)
    menu.add('Get screen size', lambda: ui.set_dialog(ui.Label(str(ui.screen_size))))
    
    ui.set(menu)

client.main = client_main

def unpack_data():
    last_flipped = time.time()
    all_files_count = 955
    i = 0
    if os.path.exists('data.tgz'):
        tar = tarfile.open('data.tgz')
        for info in tar:
            i += 1
            if (time.time() - last_flipped) > 0.1:
                progress.draw_frame('installing...', info.name, float(i) / all_files_count)
                last_flipped = time.time()
            if '..' in info.name or info.name.startswith('/'):
                raise IOError('unsafe file name')
            
            if info.isdir():
                info = copy.copy(info)
                info.mode = 0700
            if osutil.is_android:
                tar.extract(info, "")
        os.remove('data.tgz')
    progress.draw_frame('', 'starting...', 1)

def main(size=None, init=True):
    client.window.init_screen(size)
    osutil.init()
    
    ui.init()
    unpack_data()
    ui.set_fill_image(pygame.image.load('data/user/background.jpg'))
    client.window.init()
    gamescreen.init()
    if init:
        client.freeciv.run()
    else:
        client_main()

if __name__ == '__main__':
    main()