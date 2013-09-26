from freeciv import ui
from freeciv import sync
from freeciv import ui
from freeciv import help
from freeciv import osutil
from freeciv import features
from freeciv import sync

features.add_feature('gold.initiated', type=bool, default=False)

def set_gold_status(status):
    pass

features.set_applier('gold.status', default='none', func=set_gold_status)
features.add_feature('gold.session_warning', type=bool, default=False)

def menu():
    layout = ui.LinearLayoutWidget()
    button = ui.Button('Get Gold', open_gold_link)
    text_label = help.LongTextWidget('Loading...', ui.screen_width, ui.smallfont)

    layout.add(button)
    layout.add(text_label)
    layout.add(button)

    def text_fetched(text):
        text_label.set_text(text)

    ui.async(lambda: sync.request_with_sid('/sale/gold_text'), then=text_fetched)
    ui.set(ui.ScrollWrapper(layout))

def open_gold_link():
    features.set_perm('gold.initiated', True)
    osutil.open_url(sync.PROTO + '://' + sync.HOST + '/sync/login?then=sale/gold&sid=' + sync.get_sid())

def maybe_check_products():
    if features.get('gold.initiated'):
        # if user ever wanted to get gold, check if he did it
        check_products()

def check_products():
    resp = sync.json_request_with_sid('/sale/products')
    if 'gold0plus' in resp:
        features.set_perm('gold.status', 'gold0plus')
    elif 'gold0' in resp:
        features.set_perm('gold.status', 'gold0')

    if 'session_warning' in resp:
        features.set('gold.session_warning', True)

    redisplay_menu()

@ui.execute_later_decorator
def redisplay_menu():
    from freeciv import menus
    if not ui.history:
        menus.main_menu()
