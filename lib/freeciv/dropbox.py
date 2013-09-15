import jnius
import reflect as jnius_reflect
import ui

DropboxHelper = jnius_reflect.autoclass('com.zielm.freeciv.DropboxHelper')

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
    msg = 'auth finished (%s, %s)' % (key, secret)
    print msg
    ui.message(msg)
