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

import sys
import os

features = {}
appliers = {}
feature_types = {}
pernaments = {}
feature_safety = {}

monitor = None

def log(str):
    global monitor
    if not monitor:
        try:
            from freeciv import monitor
        except ImportError:
            print str
            return
    monitor.log('features', str)

def get(name):
    return features[name]

def set_applier(name, func, type=str, default=None):
    appliers[name] = func
    feature_types[name] = type
    features[name] = default

def add_feature(name, default=None, type=str, safe=False):
    appliers[name] = None
    features[name] = default
    feature_types[name] = type
    feature_safety[name] = safe

def get_feature_file_path():
    import osutil
    return osutil.get_internal_storage() + '/features'

def load_config():
    FEATURE_FILE_PATH = get_feature_file_path()
    print 'features', FEATURE_FILE_PATH

    try:
        for line in open(FEATURE_FILE_PATH):
            try:
                k, v = _parse_arg(line.rstrip())
                pernaments[k] = v
            except Exception as err:
                print 'failed to parse config line %r' % line
    except IOError:
        print 'feature config not read'

def parse_options():
    load_config()
    args = sys.argv[1:]
    unused = [sys.argv[0]]
    for arg in args:
        if arg == '-f:_list':
            show_feature_list()
            sys.exit(1)
        if arg.startswith('-f:'):
            arg = arg[len('-f:'):]
            _parse_arg(arg)
        else:
            unused.append(arg)
    sys.argv = unused

def show_feature_list():
    for key in sorted(feature_types):
        print '%s = [%s] %s' % (key.rjust(35), feature_types[key].__name__, str(features[key]).ljust(35))

def _parse_arg(arg):
    if '=' in arg:
        key, val = arg.split('=', 1)
    else:
        key = arg
        val = 'true'
    set_feature(key, val)
    return key, val

def parse_type(t, v):
    if t == bool:
        if isinstance(v, bool):
            return v
        else:
            return v.lower() in ('true', 't', 'y', 'yes')
    elif t == str:
        return v
    elif t == int:
        return int(v)
    else:
        raise TypeError(t)

def set(name, value, require_safe=False):
    if name not in appliers:
        raise ValueError('Unknown feature %r.' % name)

    if require_safe and not feature_safety[name]:
        raise ValueError('Tried to set unsafe feature %r.' % name)

    log('set_feature %s %r' % (name, value))

    features[name] = parse_type(feature_types[name], value)
    if appliers[name]:
        appliers[name](features[name])

def set_perm(name, value):
    assert '=' not in name and '\n' not in name and '\r' not in name

    set(name, value)
    if pernaments.get(name, Ellipsis) != value:
        pernaments[name] = value
        _store_pernaments()

        print 'changed pernament feature %s to %r' % (name, value)

def _store_pernaments():
    path = get_feature_file_path()
    dir = os.path.dirname(path)
    if not os.path.exists(dir):
        os.makedirs(dir)
    with open(path, 'w') as features_conf:
        features_conf.write('\n'.join([ '%s=%s' % (k, v) for k, v in pernaments.items() ]) + '\n')

set_feature = set
