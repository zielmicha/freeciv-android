import ui
import features
import sync
import osutil
import time
import functools

if osutil.is_android:
    import jnius
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
    sync.request_with_sid('/sync/register',
                          key=features.get('civsync.key'),
                          secret=features.get('civsync.secret'),
                          install_time=sync.get_install_time())

def check_auth():
    if not features.get('civsync.key'):
        login()
        return False
    else:
        init()
        return True

def make_name(path):
    name = path.split('/')[-1]
    compressor = ''
    if not name.endswith('.sav'):
        name, compressor = name.rsplit('.', 1)
        compressor = '.' + compressor
    if name.endswith('.sav'):
        name = name[:-4]
    name += '-' + time.strftime('%Y-%m-%d_%H.%M')
    name += '.sav'
    name += compressor
    return name

@ui.execute_later_decorator
def save(path):
    if not check_auth(): return
    name = make_name(path)
    print 'uploading', path, 'as', name
    DropboxHelper.uploadFile(path, name)
    sync.request_with_sid('/sync/uploading', name=name)

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

def jlist_to_list(l):
    arr = []
    for i in xrange(l.size()):
        arr.append(l.get(i))
    return arr

def load_dialog(entries):
    print entries

    def callback(entry):
        print 'need to load', name

    menu = ui.LinearLayoutWidget()
    for entry in entries:
        menu.add(ui.Button(DropboxHelper.getPath(entry),
                           functools.partial(callback, entry)))
    ui.set(ui.ScrollWrapper(menu))
