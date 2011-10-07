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
import os
import time
import hashlib
import gzip
import pprint
import platform
import glob
import bz2
try:
    import lzma
except ImportError:
    # windows
    import pylzma as lzma

import civsync

civ_not_found = False
is_windows = False
if platform.system().lower() == 'linux':
    name, ver, code = platform.linux_distribution()
    if name:
        source = 'desktop-%s-%s' % (name.lower(), ver.lower())
    else:
        source = 'desktop-linux-%s' % platform.release()
elif platform.system().lower() == 'windows':
    is_windows = True
    win_release = platform.win32_ver()[0]
    source = 'desktop-windows-%s' % win_release.lower()
else:
    source = 'desktop-%s-%s' % (platform.system().lower(), platform.release().lower())

civsync.USER_AGENT = 'CivSyncDesktop/1 (%s)' % source

session = civsync.Session()

if is_windows:
    civpath = os.path.join(os.path.expanduser('~'), r'AppData\Roaming\.freeciv')
else:
    civpath = os.path.join(os.path.expanduser('~'), '.freeciv')
print 'civpath', civpath

savepath = os.path.join(civpath, 'saves')
sessfile = os.path.join(civpath, 'civsync.sessid.txt')
cachefile = os.path.join(civpath, 'civsync.cache.txt')
request_login = None
request_check = False

try:
    cache = dict( line.split(':',1) for line in open(cachefile).read().splitlines() )
except IOError:
    cache = {}
entries_to_work = []
current_entry = None
current_state = 'none'

to_download = []
to_upload = []

print 'uploading saves as', source

def work():
    pre_work()
    do_work()

def pre_work():
    global to_upload, to_download, current_state
    
    print 'listing local files...'
    local_sync_hash = {}
    for name in os.listdir(savepath):
        sufix = '-sync.sav.gz'
        if not name.endswith(sufix):
            continue
        
        rest, hash = name[:-len(sufix)].rsplit('-', 1)
        local_sync_hash[hash] = name
    #print 'local synced files:'
    #pprint.pprint(local_sync_hash)
    
    print 'listing remote files...'
    
    current_state = 'contacting server...'
    remote_files = session.list()
    current_state = 'preparing...'
    
    to_download = []
    
    for entry in remote_files:
        if entry.sha1 in cache:
            # do not downloadad file we uploaded
            continue
        if short_hash(entry.sha1) not in local_sync_hash:
            to_download.append(entry)
    
    if to_download:
        print 'to download:'
        pprint.pprint(to_download)
    else:
        print 'nothing to download'
    
    print 'listing local files...'
    uploadable = []
    for name in os.listdir(savepath):
        if '-auto.sav' in name:
            continue
        if '-sync.sav' not in name:
            uploadable.append(name)
    uploadable.sort(key=lambda r: -os.path.getmtime(os.path.join(savepath, r)))
    uploadable = uploadable[:5]
    
    to_upload = []
    for name in uploadable:
        found = False
        for entry in remote_files:
            if entry.source == source and trim_save_name(entry.name) == trim_save_name(name):
                found = True
                break
        if not found:
            to_upload.append(name)
    
    if to_upload:
        print 'to upload:'
        pprint.pprint(to_upload)
    else:
        print 'nothing to upload'
    
    current_state = 'idle'

def trim_save_name(name):
    if name.endswith('.gz'):
        name = name[:-3]
    if name.endswith('.bz2'):
        name = name[:-4]
    if name.endswith('.sav'):
        name = name[:-4]
    return name

def read_compressed(path):
    if path.endswith('.bz2'):
        return bz2.decompress(open(path, 'rb').read())
    elif path.endswith('.gz'):
        return gzip.open(path, 'rb').read()
    else:
        return open(path, 'rb').read()

def do_work():
    global current_entry, current_state
    
    while to_download:
        entry = to_download.pop()
        current_state = 'downloading'
        current_entry = '%s' % trim_save_name(entry.name)
        
        name = '%s-%s-sync.sav.gz' % (trim_save_name(entry.name), short_hash(entry.sha1))
        path = os.path.join(savepath, name)
        print 'download to %s %dkB' % (name, entry.size/1024)
        
        compressed_data = session.download(entry.sha1).read()
        data = lzma.decompress(compressed_data)
        
        with gzip.open(path, 'wb') as f:
            f.write(data)
        
        # why not change mtime of file?
        # - we dont know if local clock is same as remote clock
        
        print 'saved to', path
    
    while to_upload:
        name = to_upload.pop()
        current_state = 'uploading'
        current_entry = '%s' % trim_save_name(name)
        
        upload_name = trim_save_name(name)
        path = os.path.join(savepath, name)
        
        print 'uploading', path
        content = read_compressed(path)
        compressed = lzma.compress(content)
        print '\tuncompressed save size %d kB' % (len(content) / 1024)
        print '\tcompressed blob size %d kB' % (len(compressed) / 1024)
        session.upload(source, upload_name, compressed).send_all_console()
        
        sha1 = hashlib.sha1(compressed).hexdigest()
        add_to_cache(sha1, 'true')
        
        print 'uploaded as %s:%s' % (source, upload_name)

def short_hash(h):
    return h[:6]

def add_to_cache(key, val):
    cache[key] = val
    with open(cachefile, 'w') as f:
        for k, v in cache.items():
            f.write('%s:%s\n' % (k, v))

def prepare():
    try:
        sess = open(sessfile).read().strip()
    except IOError:
        sess = None
    
    if sess:
        session._sessid = sess

def wait_until_logged():
    if not session.is_logged():    
        print 'wait_until_logged'
        request_login()
        while not session.is_logged():
            time.sleep(0.4)
        f = open(sessfile, 'w')
        f.write(session.sessid)
        f.close()

def find_civ_client():
    if is_windows:
        files = glob.glob(os.path.expandvars(r'%PROGRAMFILES%\Freeciv*\freeciv-gtk2.exe'))
        if files:
            return files[0]
        else:
            return None
    else:
        for entry in os.environ['PATH'].split(os.pathsep):
            bin = os.path.join(entry, 'freeciv-gtk2')
            if os.path.exists(bin):
                return bin
        return None

def run():
    global current_state, civ_not_found, request_check
    
    time.sleep(0.2)
    
    civbinary = find_civ_client()
    civ_not_found = not civbinary
    #while not os.path.exists(civpath):
    #    else:
    #        current_state = 'civnotfound'
    #    time.sleep(1)
    
    if not os.path.exists(savepath):
        os.mkdir(savepath)
    
    current_state = 'preparing...'
    
    while True:
        wait_until_logged()
        
        try:
            work()
        except civsync.LoginError:
            session._sessid = None
            wait_until_logged()
        
        wait = min(10, civsync.minimal_wait)
        for i in xrange(wait):
            if request_check:
                request_check = False
                break
            time.sleep(i)

def start():
    thread.start_new_thread(run, ())