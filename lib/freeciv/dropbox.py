import osutil
import time
import ui
import features
from freeciv import help
import save as _save

features.add_feature('civsync.allow_sharing', 'none')

@ui.execute_later_decorator
def save(path):
    if features.get('civsync.allow_sharing') == 'none':
        return ask_if_sharing_allowed(lambda: save(path))
    name = make_name(path)

    _impl_save(name, path)

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

def get_download_path():
    return _save.get_save_dir() + '/from-dropbox.sav'

if osutil.is_android:
    from freeciv.dropbox_java import _impl_save, load_from_dropbox, login
else:
    from freeciv.dropbox_civsync import _impl_save, load_from_dropbox, login
