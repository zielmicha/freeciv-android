import sync
import ui
import features
import functools
import save as _save

from freeciv.dropbox import get_download_path

def _impl_save(name, path):
    def _do():
        data = open(path, 'rb').read()
        sync.request_with_sid('/sync/upload_save',
                              name=name,
                              sharing=features.get('civsync.allow_sharing'),
                              post_data=data)

    ui.async(_do)

def load_from_dropbox():
    ui.message('Listing saves from Dropbox...')
    ui.async(
        lambda: sync.json_request_with_sid('/sync/list'),
        then=load_dialog)

def load_dialog(entries):
    def load_save(data):
        with open(get_download_path(), 'wb') as f:
            f.write(data)
        _save.load_game(get_download_path())

    def callback(entry):
        ui.message('Fetching save...')
        return ui.async(lambda: sync.request_with_sid('/sync/download', name=entry),
                        then=load_save)

    menu = ui.LinearLayoutWidget()
    menu.add(ui.Label('Save your games to folder /Applications/Freeciv in your Dropbox.'))
    for entry in entries:
        menu.add(ui.Button(entry, functools.partial(callback, entry)))
    ui.set(ui.ScrollWrapper(menu))

def login():
    pass
