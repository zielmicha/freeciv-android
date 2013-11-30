import ui
import features
import osutil

from freeciv import sync
import save as _save

import functools

from freeciv.dropbox import get_download_path

if osutil.is_android:
    import reflect as jnius_reflect
    DropboxHelper = None

features.add_feature('civsync.key', None)
features.add_feature('civsync.secret', None)

# Important: all calls to Java need to be done in UI thread
# (execute_later_decorator is for that)

def init():
    print 'DropboxHelper init'
    global DropboxHelper
    if not DropboxHelper:
        DropboxHelper = jnius_reflect.autoclass('com.zielm.freeciv.DropboxHelper')
        print 'initializing DropboxHelper tokens'
        tokenKey = features.get('civsync.key')
        tokenSecret = features.get('civsync.secret')
        DropboxHelper.setTokens(tokenKey, tokenSecret)
        DropboxHelper.init()
        ui.execute_later(_message_checker)

def _message_checker():
    if DropboxHelper.needAuth:
        print 'Authentication requested by DropboxHelper'
        DropboxHelper.needAuth = False
        features.set_perm('civsync.key', None)
        features.set_perm('civsync.secret', None)
        login()

    msg = DropboxHelper.getMessage()
    if msg:
        print 'showing message from DropboxHelper', msg
        ui.message(msg)
    ui.execute_later(_message_checker)

@ui.execute_later_decorator
def login():
    init()
    DropboxHelper.doAuth()
    _check_finish()

def _check_finish():
    if DropboxHelper.authFinished:
        _auth_finished()
    else:
        ui.execute_later(_check_finish)

def _auth_finished():
    print '_auth_finished'
    key = DropboxHelper.tokenKey
    secret = DropboxHelper.tokenSecret
    features.set_perm('civsync.key', key)
    features.set_perm('civsync.secret', secret)
    tell_civsync()

def tell_civsync():
    ui.async(lambda: sync.request_with_sid('/sync/register',
                                           key=features.get('civsync.key'),
                                           secret=features.get('civsync.secret'),
                                           install_time=sync.get_install_time()))

def check_auth():
    if not features.get('civsync.key'):
        login()
        return False
    else:
        init()
        return True

def jlist_to_list(l):
    arr = []
    for i in xrange(l.size()):
        arr.append(l.get(i))
    return arr

@ui.execute_later_decorator
def load_dialog(entries):
    print entries

    menu = ui.LinearLayoutWidget()
    menu.add(ui.Label('Save your games to folder /Applications/Freeciv in your Dropbox.'))
    for entry in entries:
        name = DropboxHelper.getPath(entry).strip('/')
        menu.add(ui.Button(name,
                           functools.partial(load_dropbox_save, name)))
    ui.set(ui.ScrollWrapper(menu))

def load_dropbox_save(name):
    print 'fetching from Dropbox', name
    ui.message('downloading save from Dropbox...')
    DropboxHelper.downloadFile('/' + name, get_download_path())
    check_downloaded()

@ui.execute_later_decorator
def load_from_dropbox():
    if not check_auth(): return

    ui.message("Listing saves from Dropbox...")

    DropboxHelper.listDirectory()

    def wait():
        if DropboxHelper.result:
            jlist = DropboxHelper.result
            print jlist
            DropboxHelper.printList(jlist)
            saves = jlist_to_list(jlist)
            load_dialog(saves)
        else:
            ui.execute_later(wait)

    wait()

def _impl_save(name, path):
    if not check_auth(): return
    print 'uploading', path, 'as', name
    DropboxHelper.uploadFile(path, name)
    ui.async(lambda: sync.request_with_sid('/sync/uploading', name=name,
                                           sharing=features.get('civsync.allow_sharing')))


def check_downloaded():
    if DropboxHelper.downloaded:
        if DropboxHelper.downloadedSuccess:
            download_success()
    else:
        ui.execute_later(check_downloaded)

def download_success():
    _save.load_game(get_download_path())
