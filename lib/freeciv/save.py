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
import atexit
import sys

import dropbox

from freeciv.client import _freeciv as freeciv

from monitor import get_save_dir

features.add_feature('app.ruleset', default='default')

localhost = '127.0.0.1'

def new_game():
    port = random.randint(2000, 15000)
    args = ('-r', './data/%s.serv' % features.get('app.ruleset'))
    gui = ServerGUI()
    start_server(port, args=args, line_callback=gui.server_line_callback)
    gui.connect(port)
    ui.set(gui.ui)

class ServerGUI(ui.LinearLayoutWidget):
    def __init__(self, no_quit=False):
        super(ServerGUI, self).__init__()
        gamescreen.ScreenClient(no_quit=no_quit)
        self.ui = ui.ScrollWrapper(self)
        self.has_ui = False
        self.setup_loading_ui()

        self.server_lines = []
        self.server_console = None

    def connect(self, port, host=localhost, login='player'):
        client.client.connect_to_server(login, host, port)

    def setup_loading_ui(self):
        self.add(ui.Label('Loading...'))

    def setup_ui(self):
        self.has_ui = True
        self.items = []

        client.client.chat('/set nettimeout 0')
        client.client.chat('/set pingtimeout 1800')

        self.pick_nation_button = ui.Button('...', self.pick_nation)
        self.set_leader_name_button = ui.Button('...',
                                                lambda:
                                                uidialog.inputbox('What will be your name?',
                                                                  finish=self.set_leader_name))
        self.difficulty_button = ui.Button('...', self.set_difficulty)

        self.add(ui.Button('Start game!', start_client))
        self.add(self.pick_nation_button)
        self.add(self.set_leader_name_button)
        self.add(self.difficulty_button)
        self.add(ui.Button('Server command', server_command_dialog))

        self.aicount_button = ui.Button('...',
                                        lambda:
                                        uidialog.inputbox('How many computer enemies will you fight?',
                                                          finish=self.set_aicount))
        self.set_aicount(4)
        self.add(self.aicount_button)

        self.mapsize_button = ui.Button('...',
                                        lambda:
                                        uidialog.inputbox('How large your map will be? (1-20)',
                                                          finish=self.set_mapsize))
        self.set_mapsize(5)
        self.add(self.mapsize_button)

        self.barbarians_button = ui.Button('...', self.set_barbarians)
        self.barbarians = False
        self.set_barbarians()
        self.add(self.barbarians_button)

        self.nation_id = 1 #random.choice(client.get_nations())[2]
        self.leader_name = 'Player'
        self.city_style = 1
        self.leader_sex = 2
        self.difficulty = 'easy'

        self.set_nation_settings()
        self.set_difficulty_settings()

        self.server_console = ui.Label('loading...', font=ui.consolefont)
        self.add(self.server_console)
        self.update_server_console()

    def server_line_callback(self, line):
        self.server_lines.append(line.rstrip())
        self.server_lines = [ line for line in self.server_lines if line != '>' ]
        self.server_lines = self.server_lines[-10:]
        ui.execute_later(self.update_server_console)
        if client.client:
            client.client.server_line_callback(line)

    def update_server_console(self):
        if self.server_console:
            caption = 'Server console:\n'
            self.server_console.set_text(caption + '\n'.join(self.server_lines))

    def back(self):
        client.client.disconnect()
        ui.back(allow_override=False)

    def set_leader_name(self, name):
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
        cmd = val
        try:
            count = int(cmd)
            client.client.chat('/set aifill %d' % (count + 1))
            self.aicount_button.set_text('AI player count: %d' % count)
        except (ValueError, TypeError):
            pass

    def set_mapsize(self, val=None):
        cmd = val
        try:
            count = int(cmd)
            if count < 1 or count > 20:
                return
            client.client.chat('/set size %d' % count)
            self.mapsize_button.set_text('Map size: %dk' % count)
        except (ValueError, TypeError):
            pass

    def set_barbarians(self):
        self.barbarians = not self.barbarians
        word = ('normal' if self.barbarians else 'disabled')
        self.barbarians_button.set_text('Barbarians: %s' % word)
        client.client.chat('/set barbarians %s' % word)

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
    uidialog.inputbox('Command', finish=client.client.chat)

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
    menu = ui.LinearLayoutWidget(marginleft=10)
    was_any = False
    menu.add(dropbox.DBButton('Show saves in Dropbox', dropbox.load_from_dropbox))
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
            start_button = ui.Dialog(ui.screen, ui.Button('Touch to start game', callback))
            start_button.back = callback
            ui.set(start_button, anim=False)

    sc_client = gamescreen.ScreenClient()

    port = random.randint(1500, 12000)
    start_server(port, ('-f', path), line_callback=sc_client.server_line_callback)

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
    time.sleep(0.4)

def server_loop(port, args=(), line_callback=None, quit_on_disconnect=True):
    assert quit_on_disconnect
    args = ('--Ppm', '-p', str(port), '-s', get_save_dir(), ) + args

    piddir = get_save_dir()
    print 'server args', args

    stream = zygote_start_server(args)

    while True:
        line = stream.readline()
        if not line:
            break
        if line_callback:
            line_callback(line)
        print 'server:', line.rstrip()

def start_zygote():
    global zygote_cmd_pipe, zygote_console_pipe
    cmd_pipe_fd, zygote_cmd_pipe_fd = os.pipe()
    zygote_console_pipe_fd, console_pipe_fd = os.pipe()
    pid = os.fork()
    if pid == 0:
        zygote_main(os.fdopen(cmd_pipe_fd, 'r', 0),
                    os.fdopen(console_pipe_fd, 'w', 0))
    else:
        print 'zygote spawned as', pid
        atexit.register(os.kill, pid, 9) # no mercy!
        zygote_cmd_pipe = os.fdopen(zygote_cmd_pipe_fd, 'w', 0)
        zygote_console_pipe = os.fdopen(zygote_console_pipe_fd, 'r', 0)

def zygote_start_server(cmd):
    zygote_cmd_pipe.write('\0'.join(cmd) + '\n')
    return zygote_console_pipe

def zygote_main(cmd_pipe, console_pipe):
    os.environ['FREECIV_QUIT_ON_DISCONNECT'] = 'true'
    os.dup2(console_pipe.fileno(), 0)
    os.dup2(console_pipe.fileno(), 1)
    while True:
        cmd = cmd_pipe.readline()
        if not cmd:
            print >>sys.stderr, 'zygote: exiting'
            return
        cmd = cmd.rstrip('\n')
        print >>sys.stderr, 'zygote: starting server', ' '.join(cmd.split('\0'))
        freeciv.func.py_server_main(cmd.split('\0'))
        print >>sys.stderr, 'zygote: server forked'
