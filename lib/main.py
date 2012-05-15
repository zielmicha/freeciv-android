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
import shutil
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
import time
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
import menus

from sync import lzma

features.add_feature('app.debug', default=True, type=bool)
features.add_feature('app.autoupdate', default=True, type=bool)
features.add_feature('app.forcesize')
features.add_feature('app.resume', default=False, type=bool)
features.add_feature('app.profile', default=False, type=bool)
features.add_feature('app.shutdown', default=10, type=int)
features.add_feature('app.multiplayer', default=False, type=bool)
features.add_feature('app.version')

features.add_feature('debug.remote', default=False, type=bool)
features.add_feature('debug.remote.passphase', default='freeciv1234', type=str)
features.add_feature('debug.remote.port', default=15589, type=int)

def apply_hardexit(t):
    client.freeciv.hard_exit = t

features.set_applier('app.hardexit', apply_hardexit, type=bool, default=True)

main_menu = None
main_menu_update_shown = False

pause_file = os.path.join(save.get_save_dir(), 'pause_options')

def client_main():
    if try_resume():
        ui.main()
        return
    
    ui.set(ui.Label('loading...'))
    ui.execute_later.append(app_main)
    
    if features.get('app.profile'):
        profile_main()
    else:
        ui.main()

def app_main():
    action = sys.argv[1] if sys.argv[1:] else None
    
    if action == 'load':
        savename = sys.argv[2]
        save.load_game(savename)
    elif action == 'connect':
        host, port, username = sys.argv[2:]
        save.connect(host, int(port), username)
    elif action == 'eval':
        exec sys.argv[2] in globals()
    elif action == 'loadmeet':
        savename = sys.argv[2]
        ident = int(sys.argv[3])
        def callback():
            client.freeciv.func.py_init_meeting(ident)
        save.load_game(savename, callback)
    elif action == 'help':
        import help
        help.show()
    else:
        if action:    
            print 'unknown action %r, see lib/main.py for actions' % action
        menus.main_menu()

def profile_main():
    import cProfile
    cProfile.run('import ui; ui.main()', 'profileout')
    import pstats
    p = pstats.Stats('profileout')
    p.strip_dirs().sort_stats('time').print_stats()

def start_autoupdate():
    thread.start_new_thread(run_autoupdate, ())

def run_autoupdate():
    install_time = sync.get_install_time()
    try:
        sync.client().updates(install_time)
    except sync.civsync.UpdateRequiredError as err:
        notify_update(err.url)
    except Exception as err:
        print 'Failed to autoupdate:', err

def notify_update(url):
    print 'update found at', url
    
    time.sleep(1)
    
    with ui.execute_later_lock:
        ui.execute_later.append(lambda: menus.notify_update(url))

client.main = client_main

def unpack_data():
    last_flipped = time.time()
    all_files_count = 455
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
        time.sleep(features.get('app.shutdown'))
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
            menus.main_menu()
            ui.set(ui.Label('dummy'))
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

def setup_freeciv_config():
    path = os.environ['FREECIV_OPT'] = save.get_save_dir() + '/civrc-2.3-1'
    try:
        if not os.path.exists(path):
            shutil.copy('data/civrc-2.3-default', path)
    except (IOError, OSError):
        pass

def maybe_start_remote_debug():
    if features.get('debug.remote'):
        import remote_shell
        remote_shell.start()
        
def setup_android_version():
    vernum = osutil.get_android_version()
    if vernum >= 14: # icecream sandwich causes bug
        features.add_feature("app.disable_android_pause", type=bool, default=True)
    name, version = osutil.get_android_version_info()
    if osutil.is_desktop:
        info_string = 'Desktop'
    else:
        info_string = 'Android %s %s' % (name.capitalize(), version)
    print 'running', info_string, '(code=%s)' % vernum

def setup_game_version():
    code = features.get('civsync.ua').split('/')[1]
    a, b, c, d = map(int, code)
    version = '%d.%d.%d' % (a, b, c*10 + d)
    print 'Freeciv for Android', version
    features.set('app.version', version)

def setup_errors():
    ui.except_callback = except_hook

def except_hook():
    type, value, tb = sys.exc_info()
    tb_str = traceback.format_exception(type, value, tb, limit=20)
    panel = ui.LinearLayoutWidget()
    panel.add(ui.Label('error!', font=ui.consolefont))
    panel.add(ui.Label(str(type) + ':\n' + str(value), font=ui.consolefont))
    panel.add(ui.Label(''.join(tb_str), font=ui.consolefont))
    ui.screen = ui.ScrollWrapper(panel)

def main(size=None, init=True):
    features.FEATURE_FILE_PATH = os.path.join(save.get_save_dir(), 'features')
    features.parse_options()
    setup_game_version()
    setup_android_version()
    setup_errors()    
    size = size or check_force_size()
    
    maybe_start_remote_debug()
    
    monitor.start()
    
    client.window.init_screen(size)
    osutil.init()
    
    ui.init()
    ui.set_fill_image(None)
    unpack_data()
    ui.set_fill_image(pygame.image.load('data/user/background.jpg'))
    
    setup_freeciv_config()
    client.window.init()
    gamescreen.init()
    
    start_autoupdate()
    
    if init:
        client.freeciv.run()
    else:
        client_main()

if __name__ == '__main__':
    main()