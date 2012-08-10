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

import gamescreen
import ui
import uidialog
import osutil
import client
import sync
import monitor

import functools
import time
import thread
import random
import os
import gzip
import features
import subprocess

from monitor import get_save_dir

features.add_feature('app.ruleset', default='default')

localhost = '127.0.0.1'

def new_game():
    port = random.randint(2000, 15000)
    args = ('-r', './data/%s.serv' % features.get('app.ruleset'))
    start_server(port, args=args)
    ui.set(ServerGUI(port))

def connect_dialog():
    host = uidialog.inputbox('Server host')
    port = int(uidialog.inputbox('Server port'))
    username = uidialog.inputbox('User name')
    connect(host, port, username)

def connect(host, port, login='player'):
    ui.set(ServerGUI(host=host, port=port, login=login, no_quit=True))

class ServerGUI(ui.LinearLayoutWidget):
    def __init__(self, port, host=localhost, login='player', no_quit=False):
        super(ServerGUI, self).__init__()
        sc_client = gamescreen.ScreenClient(no_quit=no_quit)
        sc_client.connect_to_server(login, host, port)
        self.has_ui = False
        self.setup_loading_ui()

    def setup_loading_ui(self):
        self.add(ui.Label('Loading...'))

    def setup_ui(self):
        self.has_ui = True
        self.items = []

        client.client.chat('/set nettimeout 0')
        client.client.chat('/set pingtimeout 1800')

        self.pick_nation_button = ui.Button('...', self.pick_nation)
        self.set_leader_name_button = ui.Button('...', self.set_leader_name)
        self.difficulty_button = ui.Button('...', self.set_difficulty)

        self.add(ui.Button('Start game!', start_client))
        self.add(self.pick_nation_button)
        self.add(self.set_leader_name_button)
        self.add(self.difficulty_button)
        self.add(ui.Button('Server command', server_command_dialog))

        self.aicount_button = ui.Button('...', self.set_aicount)
        self.set_aicount(4)
        self.add(self.aicount_button)

        self.mapsize_button = ui.Button('...', self.set_mapsize)
        self.set_mapsize(5)
        self.add(self.mapsize_button)

        self.nation_id = 1 #random.choice(client.get_nations())[2]
        self.leader_name = 'Player'
        self.city_style = 1
        self.leader_sex = 2
        self.difficulty = 'easy'

        self.set_nation_settings()
        self.set_difficulty_settings()

    def back(self):
        client.client.disconnect()
        ui.back(allow_override=False)

    def set_leader_name(self):
        name = uidialog.inputbox('What will be your name?')
        if name:
            self.leader_name = name
            self.set_nation_settings()

    def set_difficulty(self):
        def set_do(name):
            self.difficulty = name
            self.set_difficulty_settings()

        ui.show_list_dialog(['novice', 'easy', 'normal', 'hard'], callback=set_do)

    def set_difficulty_settings(self):
        client.client.chat('/%s' % self.difficulty)
        self.difficulty_button.set_text('Difficulty: %s' % self.difficulty)

    def set_aicount(self, val=None):
        cmd = val or uidialog.inputbox('How many computer enemies will you fight?')
        try:
            count = int(cmd)
            client.client.chat('/set aifill %d' % (count + 1))
            self.aicount_button.set_text('AI player count: %d' % count)
        except (ValueError, TypeError):
            pass

    def set_mapsize(self, val=None):
        cmd = val or uidialog.inputbox('How large your map will be? (1-20)')
        try:
            count = int(cmd)
            if count < 1 or count > 20:
                return
            client.client.chat('/set size %d' % count)
            self.mapsize_button.set_text('Map size: %dk' % count)
        except (ValueError, TypeError):
            pass

    def tick(self):
        super(ServerGUI, self).tick()
        client.client.tick()

        if not self.has_ui and client.dialogs.is_page_open('START'):
            self.setup_ui()

    def set_nation_settings(self):
        client.freeciv.func.set_nation_settings(self.nation_id, self.leader_name, self.city_style, self.leader_sex)

        self.pick_nation_button.set_text('Pick nation: %s' % client.get_nation_name(self.nation_id))
        self.set_leader_name_button.set_text('Set leader name: %s' % self.leader_name)

    def pick_nation(self):
        def set_nation(style, id):
            self.city_style = style
            self.nation_id = id
            self.set_nation_settings()
            ui.back()
        nations = ui.LinearLayoutWidget()
        for name, style, id in client.get_nations():
            nations.add(ui.Button(name, functools.partial(set_nation, style, id)))

        ui.set_dialog(nations, scroll=True)

def server_command_dialog():
    cmd = uidialog.inputbox('Command')
    if cmd:
        print cmd
        client.client.chat(cmd)

def load_scenario():
    menu = ui.LinearLayoutWidget()

    for name, path in get_scenarios():
        callback = functools.partial(load_game, path)
        menu.add(ui.Button(name, callback))

    ui.set(ui.ScrollWrapper(menu))

def get_scenarios():
    #f = [ line.split(':') for line in open('data/scenario/list.txt').read().splitlines() ]
    #return [ (name, 'scenarion/' + fn) for name, fn in f ]
    return [ (name.split('.')[0], 'data/scenario/' + name)
        for name in os.listdir('data/scenario')
        if '.sav' in name ]

def load_dialog():
    menu = ui.LinearLayoutWidget()
    was_any = False
    if features.get('civsync.enable'):
        menu.add(ui.Button('Show CivSync saves', sync.show_load))
    for name, path in get_saves():
        callback = functools.partial(load_game, path)
        menu.add(ui.Button(name, callback))
        was_any = True
    if not was_any:
        menu.add(ui.Label('No saved games yet...'))
    ui.set(ui.ScrollWrapper(menu))

def get_saves():
    def sort_key(name):
        return os.path.getmtime(os.path.join(path, name))

    path = get_save_dir()
    names = os.listdir(path)
    names.sort(key=sort_key, reverse=True)
    for name in names:
        if '.sav' in name:
            yield (name, os.path.join(path, name))

def open_save(path):
    if path.endswith('.gz'):
        return gzip.open(path)
    elif path.endswith('.bz2'):
        import bz2
        return bz2.BZ2File(path)
    else:
        return open(path)

def get_save_username(path):
    for name in open_save(path):
        if name.startswith('name='):
            name = name[len('name='):].strip().strip('"')
            print 'detected player name', name
            return name
    print 'falling back to default player name'
    return 'player'

def load_game(path, user_callback=None, before_callback=None):
    def out_callback(line):
        if 'Established control over the server. You have command access level' in line:
            ui.back(anim=False)
            start_button = ui.Dialog(ui.screen, ui.Button('Touch to start game', callback))
            start_button.back = callback
            ui.set(start_button, anim=False)
            sc_client.out_window_callback = None

    port = random.randint(1500, 12000)
    start_server(port, ('-f', path))

    sc_client = gamescreen.ScreenClient()
    sc_client.out_window_callback = out_callback
    try:
        sc_client.connect_to_server('player', localhost, port)
    except client.ConnectionError:
        ui.message('Failed to connect to game server, try again', type='error')
        return

    def callback():
        if before_callback() if before_callback else True:
            load_game_now(port, get_save_username(path))

        if user_callback:
            user_callback()

    ui.replace(client.client.ui)
    ui.message('Loading...')

def load_game_now(port, username):
    client.client.chat('/take "%s"' % username)
    client.client.chat('/start')
    client.client.tick()
    ui.back(allow_override=False)

def start_client():
    client.client.chat('/start')
    ui.replace_anim(client.client.ui)

def start_server(port, args=(), line_callback=None, quit_on_disconnect=True):
    thread.start_new_thread(server_loop, (port, args, line_callback, quit_on_disconnect))
    time.sleep(0.3)

def server_loop(port, args=(), line_callback=None, quit_on_disconnect=True):
    if osutil.is_android:
        serverpath = os.path.join(os.path.dirname(client.freeciv.freecivclient.__file__), 'freecivserver')
    else:
        serverpath = 'server/freeciv-server'
    args = ('--Ppm', '-p', str(port), '-s', get_save_dir(), ) + args
    print 'starting server - executable at', serverpath
    stat = os.stat(serverpath)
    try:
        os.chmod(serverpath, 0o744) # octal!!!!
    except OSError as err:
        print 'chmodding server failed', err
    piddir = get_save_dir()
    cmd = (serverpath, ) + args
    if osutil.is_desktop:
        os.environ['LD_PRELOAD'] = ''
    if quit_on_disconnect:
        os.environ['FREECIV_QUIT_ON_DISCONNECT'] = 'true'
    else:
        del os.environ['FREECIV_QUIT_ON_DISCONNECT']
    print cmd
    serv_in, stream = os.popen4(cmd, bufsize=1) # line buffering

    p = subprocess.Popen(cmd, bufsize=1,
          stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, close_fds=True)
    stream = p.stdout

    while True:
        line = stream.readline()
        if not line:
            break
        if line_callback:
            line_callback(line)
        monitor.log('server', line.rstrip())
