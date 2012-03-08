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

import thread
import save
import os
import osutil
import sys
import time
import features
import gc
import random

features.add_feature('debug.garbage', False, type=bool)
features.add_feature('debug.gc_count', False, type=bool)
features.add_feature('debug.monitor.stop_on_pause', True, type=bool)

def get_save_dir():
    if osutil.is_android:
        return os.path.abspath('saves')
    else:
        return os.path.expanduser('~/.freeciv/android-saves')

def get_mem_usage(process='self'):
    try:
        return int(open('/proc/%s/stat' % process).read().split()[22])
    except IOError:
        return -1

def start():
    thread.start_new_thread(run, ())

def run():
    if features.get('debug.garbage'):
         gc.set_debug(gc.DEBUG_LEAK)
    
    while True:
        if osutil.is_paused():
            if features.get('debug.monitor.stop_on_pause'):
                log('log', 'monitor stopped because of pause')
                osutil.wait_for_resume()
        
        time.sleep(6)
        log('mem_self', get_mem_usage('self'))
        try:
            servpid = get_server_pid()
            server_use = get_mem_usage(servpid)
        except IOError:
            server_use = 'not running'
            
        log('mem_server', server_use)
        log('gc_stat', 'counts=%r garbage=%d' % (gc.get_count(), len(gc.garbage)))
        
        if features.get('debug.gc_count'):
            gc.collect()
            log('gc_count', len(gc.get_objects()))
        
        #if features.get('debug.garbage'):
        #    print gc.garbage

def get_server_pid():
    return int(open(get_save_dir() + '/serverpid', 'r').read())

log_file = open(os.path.join(get_save_dir(), 'more.log'), 'a', 1)

def log(cat, s):
    log_file.write('%s:%d:%s\n' % (cat, time.time()*1000, s))

log('on', 'Client is launching...')

def change_stdout():
    if osutil.is_android:
        true_err = os.fdopen(2, 'w', 1)
    
    logout = sys.stdout
    
    class MyStdout(object):
        def __init__(self):
            self.log_buffer = ''
            
        def write(self, s):  
            if osutil.is_android:
                true_err.write(str(s))
            logout.write(str(s))
            self.log_buffer += s
            while '\n' in self.log_buffer:
                line, rest = self.log_buffer.split('\n', 1)
                log('log', line)
                self.log_buffer = rest
    
    sys.stdout = sys.stderr = MyStdout()

change_stdout()