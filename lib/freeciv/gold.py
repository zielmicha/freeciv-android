from freeciv import ui
from freeciv import sync
from freeciv import ui
from freeciv import help
from freeciv import osutil

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
    osutil.open_url(sync.PROTO + '://' + sync.HOST + '/sale/gold?sid=' + sync.get_sid())
