import ui
from freeciv import features
from freeciv import sync
import osutil
from freeciv import help

import save as _save

import time
import functools

if osutil.is_android:
    import jnius
    import reflect as jnius_reflect
    DropboxHelper = None

features.add_feature('civsync.key', None)
features.add_feature('civsync.secret', None)
features.add_feature('civsync.allow_sharing', 'none')

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
    if features.get('civsync.allow_sharing') == 'none':
        return ask_if_sharing_allowed(lambda: save(path))
    if not check_auth(): return
    name = make_name(path)
    print 'uploading', path, 'as', name
    DropboxHelper.uploadFile(path, name)
    ui.async(lambda: sync.request_with_sid('/sync/uploading', name=name,
                                           sharing=features.get('civsync.allow_sharing')))

def ask_if_sharing_allowed(then):
    def notokay():
        features.set_perm('civsync.allow_sharing', 'false')
        ui.back()
        then()

    def okay():
        features.set_perm('civsync.allow_sharing', 'true')
        ui.back()
        then()

    msg = \
          'civsync.com may put saves you upload to Dropbox on a public list, for others to play.' \
          '\n\n' \
          'By clicking "I agree" you share your saves on CC0 license (public domain) ' \
          'and allow Freeciv to upload them to civsync.com.'.strip()

    dialog = ui.LinearLayoutWidget()
    panel = ui.HorizontalLayoutWidget(spacing=10)
    panel.add(ui.Button('I agree', okay))
    panel.add(ui.Button('I don\'t agree', notokay))
    dialog.add(help.LongTextWidget(msg, ui.screen_width / 3, ui.smallfont))
    dialog.add(panel)
    ui.set_dialog(dialog)

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

@ui.execute_later_decorator
def load_dialog(entries):
    print entries

    def callback(entry):
        print 'fetching from Dropbox', entry.path
        ui.message('downloading save from Dropbox...')
        DropboxHelper.downloadFile(entry.path, get_download_path())
        check_downloaded()

    menu = ui.LinearLayoutWidget()
    menu.add(ui.Label('Save your games to folder /Applications/Freeciv in your Dropbox.'))
    for entry in entries:
        menu.add(ui.Button(DropboxHelper.getPath(entry).strip('/'),
                           functools.partial(callback, entry)))
    ui.set(ui.ScrollWrapper(menu))

def get_download_path():
    return _save.get_save_dir() + '/from-dropbox.sav'

def check_downloaded():
    if DropboxHelper.downloaded:
        if DropboxHelper.downloadedSuccess:
            download_success()
    else:
        ui.execute_later(check_downloaded)

def download_success():
    _save.load_game(get_download_path())

class DBButton(ui.Button):
    fg = (0, 0x7E, 0xE5)
    bg = (255, 255, 255, 180)
    color = fg
    active_bg = bg

    def __init__(self, *args, **kwargs):
        ui.Button.__init__(self, *args, **kwargs)
        self._image = ui.load_image('data/dropbox_logo.png')

    def set_text(self, label):
        ui.Button.set_text(self, '     ' + label)

    def draw(self, surf, pos):
        ui.Button.draw(self, surf, pos)
        h = self.size[1]
        surf.blit(self._image, dest=pos + (h, h))
