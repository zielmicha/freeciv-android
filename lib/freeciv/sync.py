# Copyright (C) 2013 Michal Zielinski (michal@zielinscy.org.pl)
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

import os
import microjson as json
import osutil

if osutil.is_desktop:
    import urllib
else:
    import java_https as urllib
import time

import features
import save

HOST = 'www.civsync.com'
PROTO = 'https'
USER_AGENT = 'CivGeneric/1'

def apply_host_change(host):
    global HOST
    HOST = host

def apply_proto_change(proto):
    global PROTO
    PROTO = proto

features.set_applier('civsync.host', apply_host_change, default=HOST)
features.set_applier('civsync.proto', apply_proto_change, default=PROTO)

def apply_user_agent_change(ua):
    global USER_AGENT
    USER_AGENT = ua
    # hack, hack, hack
    print 'changing user agent to', ua
    urllib.URLopener.version = ua

features.set_applier('civsync.ua', apply_user_agent_change)

version = 2603
if osutil.is_desktop:
    features.set('civsync.ua', 'CivSyncDesktop/%d' % version)
else:
    features.set('civsync.ua', 'CivSyncAndroid/%d' % version)
features.add_feature('civsync.enable', False, type=bool)
features.add_feature('civsync.sid', None, safe=True)

def get_sid():
    sid = features.get('civsync.sid')
    if not sid:
        sid = ''.join( hex(ord(ch))[2:] for ch in os.urandom(8) )
        features.set_perm('civsync.sid', sid)
    return sid

def updates(install_time):
    request('/sync/updates', install_time=install_time)

def get_install_time():
    path = os.path.join(save.get_save_dir(), 'install_time')
    try:
        return int(open(path).read())
    except (IOError, ValueError):
        install_time = int(time.time() * 1000)
        with open(path, 'w') as f:
            f.write('%d' % install_time)
    return install_time

def request(path, **get):
    # don't need HTTPS when not transmitting sid
    if 'post_data' in get:
        post_data = get['post_data']
        del get['post_data']
    else:
        post_data = None
    proto = PROTO if 'sid' in get else 'http'
    url = proto + '://' + HOST + path + '?' + urllib.urlencode(get)
    print 'request', url
    resp = urllib.urlopen(url, post_data)
    return resp.read()

def request_with_sid(path, **get):
    get['sid'] = get_sid()
    return request(path, **get)

def json_request_with_sid(path, **get):
    get['sid'] = get_sid()
    return json.loads(request(path, **get))

class UpdateRequiredError(Exception):
    pass
