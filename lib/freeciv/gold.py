import ui
from freeciv import sync
from freeciv import help
import osutil
import features
from freeciv import sync

import functools
import microjson as json

features.add_feature('gold.enable', type=bool, default=False)
features.add_feature('gold.initiated', type=bool, default=False)

def set_gold_status(status):
    pass

features.set_applier('gold.status', default='none', func=set_gold_status)
features.add_feature('gold.session_warning', type=bool, default=False)

def menu():
    layout = ui.LinearLayoutWidget(marginleft=10)
    buttons = ui.HorizontalLayoutWidget(spacing=10)
    text_label = help.LongTextWidget('Loading...', ui.screen_width, ui.smallfont)

    layout.add(buttons)
    layout.add(text_label)
    layout.add(buttons)

    ui.async(check_products)

    def text_fetched(text):
        data = json.loads(text)
        text_label.set_text(data['text'])
        for btn in data['buttons']:
            button = ui.Button(btn['text'],
                               functools.partial(open_gold_link, btn['url'], btn.get('restart')))
            buttons.add(button)

    ui.async(lambda: sync.request_with_sid('/sale/gold_text'), then=text_fetched)
    ui.set(ui.ScrollWrapper(layout))

def open_gold_link(then, restart):
    features.set_perm('gold.initiated', True)
    osutil.open_url('%s://%s/sync/login?then=%s&sid=%s' % (
        sync.PROTO, sync.HOST, then, sync.get_sid()))

    def callback():
        ui.async(lambda: check_products(force=True))

    if restart:
        ui.set_dialog(ui.Button('Touch after finishing transaction', callback))

def maybe_check_products():
    if features.get('gold.initiated'):
        # if user ever wanted to get gold, check if he did it
        check_products()

def check_products(force=False):
    resp = sync.json_request_with_sid('/sale/products')
    if 'gold0plus' in resp:
        features.set_perm('gold.status', 'gold0plus')
    elif 'gold0' in resp:
        features.set_perm('gold.status', 'gold0')

    if 'session_warning' in resp:
        features.set('gold.session_warning', True)

    if force:
        ui.history = []

    redisplay_menu()

@ui.execute_later_decorator
def redisplay_menu():
    from freeciv import menus
    if not ui.history:
        menus.main_menu()
