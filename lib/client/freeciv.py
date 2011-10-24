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

def set_debug(flag):
    global debug
    debug = flag
    
debug = False
features.set_applier('debug.freeciv', set_debug, type=bool, default=False)

class _obj: pass

func = _obj()
callback = _obj()
const = _obj()

hard_exit = True

def _callback(funname, *args):
    if debug:
        print 'callback', funname
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
    except:
        traceback.print_exc()
        print 'Abort.'
        if hard_exit:
            os._exit(1)
        else:
            sys.exit(1)

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
        if name not in ('call_idle_callbacks', 'get_mapview_store'):
            print name
    return freecivclient.call_f(id, args)

def call(name, *args):
    return freecivclient.call_f(functions[name], args)

functions = {}

freecivclient.set_callback(_callback)

def run(args=[]):
    freecivclient.run_main(["freeciv-python-client"] + args)
    