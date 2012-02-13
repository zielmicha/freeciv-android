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

import sys, os

sys.path.append(os.path.join(os.path.dirname(__file__), '../..', 'src'))

import freecivclient
import functools
import traceback
import glob
import os
from freecivclient import mask_sprite, get_overview_size
import features
import collections
import time

def set_debug(flag):
    global debug
    debug = flag
    
debug = False

def make_init_profiling_tuple():
    return [0, 0.0]

_profiling_callback = collections.defaultdict(make_init_profiling_tuple)
_profiling_calls = collections.defaultdict(make_init_profiling_tuple)

features.add_feature('debug.freeciv.print_callbacks', type=bool, default=False)
features.set_applier('debug.freeciv', set_debug, type=bool, default=False)

class _obj: pass

func = _obj()
callback = _obj()
const = _obj()

hard_exit = True

callback_num = 0

def _callback(funname, *args):
    if debug:
        start_time = time.time()
        if features.get('debug.freeciv.print_callbacks'):
            global callback_num
            callback_num += 1
            if not funname.startswith(('canvas_', 'update_mouse_cursor')):
                print '[callback % 7d]' % callback_num, funname
    try:
        args = tuple(args)
        name = funname
        if hasattr(callback, name):
            ret = getattr(callback, name)(*args)
            if not isinstance(ret, (list, tuple)):
                ret = (ret, )
            return ret
        else:
            print 'no function named %s %s' % (name, args)
    except Exception as ex:
        if not isinstance(ex, (KeyboardInterrupt, SystemExit)):
            traceback.print_exc(limit=200)
        else:
            print type(ex).__name__
        print 'Abort.'
        _end_callbacks()
        if hard_exit:
            os._exit(1)
        else:
            sys.exit(1)
    finally:
        if debug:
            tpl = _profiling_callback[funname]
            tpl[0] += 1
            tpl[1] += time.time() - start_time

def _end_callbacks():
    if debug:
        print 'Calls stat'
        _show_profileinfo(_profiling_calls)
        print 'Callback stat'
        _show_profileinfo(_profiling_callback)
        print 'Unused'
        _show_unused()

def _show_profileinfo(l):
    items = l.items()
    items.sort(key=lambda (k, (a, b)): b, reverse=True)
    for funname, (calln, calltime) in items:
        print '% 7.1f  % 7d %s' % (calltime, calln, funname)

def _show_unused():
    unused = set(callback.__dict__.keys()) - set(_profiling_callback.keys())
    print '\t' + '\n\t'.join(sorted(unused))

def register(name_or_func):
    if isinstance(name_or_func, str):    
        def decorator(method):
            setattr(callback, name_or_func, method)
            return method
        return decorator
    elif callable(name_or_func):
        setattr(callback, name_or_func.__name__, name_or_func)
        return name_or_func
    else:
        raise TypeError('%r should be str or callable' % name_or_func)

@register('callback_test')
def _callback_test():
    pass

@register('add_function')
def _add_function(name, id):
    functions[name] = id
    setattr(func, name, functools.partial(_call, name, id))

@register('set_const')
def _set_const(name, val):
    setattr(const, name, val)
    
def _call(name, id, *args):
    if debug:
        start_time  = time.time()
    try:
        return freecivclient.call_f(id, args)
    finally:
        if debug:
            tpl = _profiling_calls[name]
            tpl[0] += 1
            tpl[1] += time.time() - start_time

def call(name, *args):
    return freecivclient.call_f(functions[name], args)

functions = {}

freecivclient.set_callback(_callback)

def run(args=[]):
    freecivclient.run_main(["freeciv-python-client"] + args)
    