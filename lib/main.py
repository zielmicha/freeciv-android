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
import progress

import uidialog
import gamescreen
import ui
import client

server_at = 6000

def new_game():
    client = gamescreen.ScreenClient()
    client.connect_to_server('michal', 'localhost', server_at)
    client.chat('/start')
    ui.set(client.ui)

def start_server():
    thread.start_new_thread(server_loop, ())

def server_loop():
    global server_at
    server_at = random.randrange(2000, 8000)
    if osutil.is_android:
        serverpath = os.path.join(os.path.dirname(client.freeciv.freecivclient.__file__), 'freecivserver')
    else:
        serverpath = 'server/freeciv-server'
    args = '-p %s' % server_at
    print 'starting server - executable at', serverpath
    stat = os.stat(serverpath)
    os.chmod(serverpath, 744)
    stream = os.popen('%s %s 2>&1' % (serverpath, args), 'r', 1) # line buffering
    os.chmod(serverpath, stat.st_mode)
    for line in stream:
        print '[server]', line.rstrip()

def client_main():
    print 'client_main'
    menu = ui.Menu()
    
    menu.add('Start server', start_server)
    menu.add('New game', new_game)
    
    ui.set(menu)
    
    ui.main()

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

def main():
    client.window.init_screen()
    osutil.init()
    
    ui.init()
    unpack_data()
    client.window.init()
    gamescreen.init()
    client.freeciv.run()

if __name__ == '__main__':
    main()