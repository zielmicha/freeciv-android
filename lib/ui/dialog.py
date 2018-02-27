import ui
import graphics
import functools

from ui.layout import _subpoints, _addpoints

def set_dialog(new_screen, scroll=False, no_stack=False):
    if scroll:
        item = ui.ScrollWrapper(new_screen,
                                height=ui.screen_height*0.7,
                                width=ui.screen_width*0.7,
                                ways=ui.SCROLL_HEIGHT|ui.SCROLL_WIDTH)
    else:
        item = new_screen
    dialog = Dialog(ui.get_screen(), item)
    ui.set(dialog, anim=False, no_stack=no_stack)
    return dialog

def message(msg, type=None):
    set_dialog(ui.Label(msg, callback=ui.back), no_stack=True)

def ask(msg, callback):
    def call_callback():
        callback()
        ui.back()

    gui = ui.LinearLayoutWidget()
    gui.add(ui.Label(msg))
    hor = ui.HorizontalLayoutWidget(spacing=10)
    hor.add(ui.Button('Yes', call_callback))
    hor.add(ui.Button('No', ui.back))
    gui.add(hor)
    set_dialog(gui)

def not_implemented():
    message('Sorry. This feature is not implemented.\nCheck Google Play for updates.')

def show_list_dialog(items, callback=None, get_text_func=None, title=None, titlefont=None, scroll=False):
    def default_get_text_func(it):
        if isinstance(it, tuple):
            label, action = it
            return label
        else:
            return it

    def default_callback(it):
        return it[1]()

    def clicked(it):
        ui.back(anim=False)
        (callback or default_callback)(it)

    gui = ui.LinearLayoutWidget()

    if title:
        gui.add(ui.Label(title, font=titlefont))

    for item in items:
        label = (get_text_func or default_get_text_func)(item)
        gui.add(ui.Button(label, functools.partial(clicked, item) ))
    set_dialog(gui, scroll=scroll)


class Dialog(ui.Widget):
    def __init__(self, screen, item):
        self.item = item
        self.screen = screen

    def draw(self, surf, pos):
        self.screen.draw(surf, pos)

        x, y = self.get_pos()
        size = self.item.size
        spacing = 5
        rect = (x + pos[0] - spacing, y + pos[1] - spacing, size[0] + spacing*2, size[1] + spacing*2)

        ui.round_rect(surf, (255, 255, 255, 240), (0, 0, 0), rect, 10)
        self.item.draw(surf, (x + pos[0], y + pos[1]))

    def get_pos(self):
        size = self.item.size
        x = (ui.screen_width - size[0]) / 2
        y = (ui.screen_height - size[1]) / 2
        return (x, y)

    def tick(self):
        self.item.tick()
        self.screen.tick()

    def back(self):
        ui.back(allow_override=False, anim=False)

    def event(self, ev):
        if hasattr(ev, 'pos'):
            pos = self.get_pos()
            ev.pos = _subpoints(ev.pos, pos)
            if ev.pos[0] < 0 or ev.pos[1] < 0:
                return
            size = self.item.size
            if ev.pos[1] > size[1] or ev.pos[0] > size[0]:
                return
            result = self.item.event(ev)
            ev.pos = _addpoints(ev.pos, pos)
            return result
        else:
            self.item.event(ev)

    def is_opened(self):
        return screen == self

    def close(self):
        if self.is_opened():
            ui.back()

    def update_layout(self):
        self.item.update_layout()
        self.screen.update_layout()
