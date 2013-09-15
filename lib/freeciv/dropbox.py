import jnius
import reflect as jnius_reflect
import ui
import features

DropboxHelper = jnius_reflect.autoclass('com.zielm.freeciv.DropboxHelper')

features.add_feature('civsync.key', None)
features.add_feature('civsync.secret', None)

def login():
    DropboxHelper.init()
    DropboxHelper.doAuth()
    check_finish()

def check_finish():
    if DropboxHelper.authFinished:
        auth_finished()
    else:
        ui.execute_later(check_finish)

def auth_finished():
    key = DropboxHelper.tokenKey
    secret = DropboxHelper.tokenSecret
    features.set_perm('civsync.key', key)
    features.set_perm('civsync.secret', secret)
    ui.message(msg)
