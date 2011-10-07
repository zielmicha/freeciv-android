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
import traceback
import thread
import progress

import save
import uidialog
import gamescreen
import ui
import client
import sync
import features

from sync import lzma

def new_game():
    save.new_game()

features.add_feature('app.debug', default=True, type=bool)
features.add_feature('app.autoupdate', default=True, type=bool)
features.add_feature('app.forcesize')

main_menu = None
main_menu_update_shown = False

def client_main():
    global main_menu
    main_menu = menu = ui.Menu()
    
    menu.add('New game', new_game)
    menu.add('Load game', save.load_dialog)
    if features.get('app.debug'):
        menu.add('Debug', debug_menu)
    
    ui.set(menu)
    
    ui.main()

def start_autoupdate():
    thread.start_new_thread(run_autoupdate, ())

def run_autoupdate():
    install_time = get_install_time()
    try:
        sync.client().updates(install_time)
    except sync.civsync.UpdateRequiredError as err:
        with ui.execute_later_lock:
            ui.execute_later.append(lambda: notify_update(err.url))

def notify_update(url):
    print 'update found at', url
    
    def callback():
        button.set_text('Loading...')
        button.callback = None
        with ui.execute_later_lock:
            ui.execute_later.append(lambda: uidialog.open_url(url))
    
    global main_menu_update_shown
    if main_menu_update_shown:
        return
    main_menu_update_shown = True
    panel = ui.LinearLayoutWidget()
    panel.add(ui.Label('There is an update available!'))
    button = ui.Button('Update', callback)
    panel.add(button)
    main_menu.items.append(panel)

def debug_menu():
    def fake_screen_size(size):
        main(size, init=False)
    
    def fake_screen_size_menu():
        menu = ui.Menu(center=False)
        for size in [(320, 240), (480, 320), (640, 480)]:
            menu.add(str(size), functools.partial(fake_screen_size, size))
        ui.set_dialog(menu, scroll=True)
    
    def test_lzma():
        data = '23423424\023234'
        try:
            print 'compressing...'
            cmpr = lzma.compress(data)
            print 'ok'
            print 'compressed data', repr(cmpr)
        except:
            traceback.print_exc()
            string = 'Nothing works!'
        else:
            try:
                print 'decompressing...'
                got = lzma.decompress(cmpr)
                print 'ok'
            except:
                traceback.print_exc()
                string = 'Decompressing doesn\'t work!'
            else:
                if got == data:    
                    string = 'Everything works!'
                else:
                    string = 'Invalid result...'
        ui.set_dialog(ui.Label(string))
    
    def test_progress():
        n = 30
        for i in xrange(n+1):
            progress.draw_frame("Test progress", "Task %d/%d" % (i,n), i/float(n))
            time.sleep(0.1)
    
    def change_feature():
        arg = uidialog.inputbox('name=key')
        try:
            features._parse_arg(arg)
        except Exception as e:
            traceback.print_exc()
            ui.message(str(e))
    
    def show_features():
        s = '\n'.join( '%s=%s' % (k,v) for k, v in sorted(features.features.items()) )
        ui.set_dialog(ui.Label(s), scroll=True)
    
    menu = ui.Menu()
    
    menu.add('Fake screen size', fake_screen_size_menu)
    menu.add('Get screen size', lambda: ui.set_dialog(ui.Label(str(ui.screen_size))))
    menu.add('Test LZMA', test_lzma)
    menu.add('Test progress', test_progress)
    menu.add('Change feature', change_feature)
    menu.add('Show features', show_features)
    menu.add('Test open_url', lambda: uidialog.open_url('http://google.com'))
    
    ui.set(ui.ScrollWrapper(menu))

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
                info.mode = 0o700
            if osutil.is_android:
                tar.extract(info, "")
        os.remove('data.tgz')
    progress.draw_frame('', 'starting...', 1)

def get_install_time():
    path = os.path.join(save.get_save_dir(), 'install_time')
    try:
        return int(open(path).read())
    except (IOError, ValueError):
        install_time = int(time.time() * 1000)
        with open(path, 'w') as f:
            f.write('%d' % install_time)
    return install_time

def check_force_size():
    if features.get('app.forcesize'):
        return map(int, features.get('app.forcesize').split(','))

def main(size=None, init=True):
    features.parse_options(sys.argv)
    size = size or check_force_size()
    
    start_autoupdate()
    
    client.window.init_screen(size)
    osutil.init()
    
    ui.init()
    ui.set_fill_image(None)
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