import ui
import features
import sync
import osutil
import time

if osutil.is_android:
    import jnius
    import reflect as jnius_reflect
    DropboxHelper = None

features.add_feature('civsync.key', None)
features.add_feature('civsync.secret', None)

# Important: all calls to Java need to be done in UI thread

def init():
    global DropboxHelper
    if not DropboxHelper:
        DropboxHelper = jnius_reflect.autoclass('com.zielm.freeciv.DropboxHelper')
        DropboxHelper.init()
        ui.execute_later(_message_checker)

def _message_checker():
    if DropboxHelper.needAuth:
        DropboxHelper.needAuth = False
        features.set_perm('civsync.key', None)
        features.set_perm('civsync.secret', None)
        login()

    msg = DropboxHelper.getMessage()
    if msg:
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
        DropboxHelper.tokenKey = features.get('civsync.key')
        DropboxHelper.tokenSecret = features.get('civsync.secret')
        DropboxHelper.useTokens()
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
    if not check_auth():
        return
    name = make_name(path)
    print 'uploading', path, 'as', name
    DropboxHelper.uploadFile(path, name)
    sync.request_with_sid('/sync/uploading', name=name)
