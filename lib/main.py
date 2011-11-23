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
import osutil
import uidialog
import gamescreen
import ui
import client
import sync
import features
import monitor
import options

from sync import lzma

def new_game():
    save.new_game()

features.add_feature('app.debug', default=True, type=bool)
features.add_feature('app.autoupdate', default=True, type=bool)
features.add_feature('app.forcesize')
features.add_feature('app.resume', default=True, type=bool)
features.add_feature('app.profile', default=False, type=bool)
features.add_feature('app.shutdown', default=10, type=int)

def apply_hardexit(t):
    client.freeciv.hard_exit = t

features.set_applier('app.hardexit', apply_hardexit, type=bool, default=True)

main_menu = None
main_menu_update_shown = False

pause_file = os.path.join(save.get_save_dir(), 'pause_options')

def client_main():
    action = sys.argv[1] if sys.argv[1:] else None
    if try_resume():
        ui.main()
        return
    
    if action == 'load':
        savename = sys.argv[2]
        save.load_game(savename)
    else:
        show_main_menu()
    
    if features.get('app.profile'):
        profile_main()
    else:
        ui.main()

def profile_main():
    import cProfile
    cProfile.run('import ui; ui.main()', 'profileout')
    import pstats
    p = pstats.Stats('profileout')
    p.strip_dirs().sort_stats('time').print_stats()

def show_main_menu():
    global main_menu
    main_menu = menu = ui.Menu()
    
    menu.add('New game', new_game)
    menu.add('Load game', save.load_dialog)
    menu.add('Feedback', feedback)
    menu.add('Options', options.show_options)
    
    ui.set(menu)

def feedback():
    panel = ui.LinearLayoutWidget()
    panel.add(ui.Label('Leaving comments with logs will help me diagnose\npotential problems with game speed and\nunexpected behaviour.'))
    panel.add(ui.Button('Leave a comment with a log (preferred)', lambda: sync.comment(get_install_time(), True)))
    panel.add(ui.Button('Leave a comment without a log', lambda: sync.comment(get_install_time(), False)))
    ui.set(panel)

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
    
    if not main_menu:
        # game was started by "load" command
        return
    
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

def pause():
    if client.client:
        print 'pause occured'
        print 'saving game'
        client.client.chat('/save %s/pause_save.sav.gz' % save.get_save_dir())
        with open(pause_file, 'w') as f:
            f.write('version=1\n')
        time.sleep(featues.get('app.shutdown'))
        if not osutil.is_paused():
            remove_pause_file()
            return
        print 'turning off server'
        client.client.disconnect()
        ui.back(allow_override=False)
        osutil.wait_for_resume()
        resume()
    else:
        osutil.wait_for_resume()

ui.pause_callback = pause

def try_resume():
    if features.get('app.resume'):
        return resume()

def resume():
    name = get_resume_data()
    if name:
        remove_pause_file()
        try:
            show_main_menu()
            save.load_game(name)
        except IOError:
            # loading save failed
            return False
        return True
    else:
        return False

def get_resume_data():
    try:
        content = open(pause_file).read()
    except IOError:
        return None
    else:
        return os.path.join(save.get_save_dir(), 'pause_save.sav.gz')

def remove_pause_file():
    try:
        os.remove(pause_file)
    except OSError:
        print 'Failed to remove pause file'

def main(size=None, init=True):
    features.FEATURE_FILE_PATH = os.path.join(save.get_save_dir(), 'features')
    features.parse_options()
    size = size or check_force_size()
    
    start_autoupdate()
    monitor.start()
    
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