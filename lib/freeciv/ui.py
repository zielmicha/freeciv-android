# Copyright (C) 2011 Michal Zielinski (michal@zielinscy.org.pl)
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

import time
import traceback
import graphics

import graphics
import functools
import features
import osutil
import os
import sys

history = []
screen = None
overlays = []

screen_height = 0
screen_width = 0
screen_size = 0, 0

show_fps = False

def set_show_fps(val):
    global show_fps
    show_fps = val

features.set_applier('ui.showfps', set_show_fps, type=bool, default=False)
features.add_feature('ui.enable_anim', type=bool, default=True)

def replace(new_screen):
    assert isinstance(new_screen, Widget)
    global screen
    screen = new_screen

def replace_anim(new_screen, direction=1):
    if features.get('ui.enable_anim'):
        replace(Animation(screen, new_screen, direction))
    else:
        replace(new_screen)

def set(new_screen, anim=True):
    if screen:
        history.append(screen)
        if anim:
            replace_anim(new_screen)
        else:
            replace(new_screen)
    else:
        replace(new_screen)

def back(allow_override=True, anim=True):
    if allow_override and screen.back() is not True:
        return
    elif not history:
        if hasattr(sys, 'exitfunc'):
            sys.exitfunc()
        os._exit(0)
    else:
        new_screen = history.pop()
        if anim:
            replace_anim(new_screen, -1)
        else:
            replace(new_screen)

def set_dialog(new_screen, scroll=False):
    if scroll:
        item = ScrollWrapper(new_screen, height=screen_height*0.7, width=screen_width*0.7, ways=SCROLL_HEIGHT|SCROLL_WIDTH)
    else:
        item = new_screen
    dialog = Dialog(screen, item)
    set(dialog, anim=False)
    return dialog

def message(msg, type=None):
    set_dialog(Label(msg))

def ask(msg, callback):
    def call_callback():
        callback()
        back()

    ui = LinearLayoutWidget()
    ui.add(Label(msg))
    hor = HorizontalLayoutWidget(spacing=10)
    hor.add(Button('Yes', call_callback))
    hor.add(Button('No', back))
    ui.add(hor)
    set_dialog(ui)

def not_implemented():
    message('Sorry. This feature is not implemented.\nCheck Google Play for updates.')

def show_list_dialog(items, callback=None, get_text_func=None, title=None, titlefont=None):
    def default_get_text_func(it):
        if isinstance(it, tuple):
            label, action = it
            return label
        else:
            return it

    def default_callback(it):
        return it[1]()

    def clicked(it):
        back(anim=False)
        (callback or default_callback)(it)

    ui = LinearLayoutWidget()

    if title:
        ui.add(Label(title, font=titlefont))

    for item in items:
        label = (get_text_func or default_get_text_func)(item)
        ui.add(Button(label, functools.partial(clicked, item) ))
    set_dialog(ui)

class Widget(object):
    def back(self):
        return True

    def event(self, ev):
        pass

    def tick(self):
        pass

class Dialog(Widget):
    def __init__(self, screen, item):
        self.item = item
        self.screen = screen

    def draw(self, surf, pos):
        self.screen.draw(surf, pos)

        x, y = self.get_pos()
        size = self.item.size
        spacing = 5
        rect = (x + pos[0] - spacing, y + pos[1] - spacing, size[0] + spacing*2, size[1] + spacing*2)

        round_rect(surf, (255, 255, 255), (0, 0, 0), rect, 10)
        self.item.draw(surf, (x + pos[0], y + pos[1]))

    def get_pos(self):
        size = self.item.size
        x = (screen_width - size[0]) / 2
        y = (screen_height - size[1]) / 2
        return (x, y)

    def tick(self):
        self.item.tick()
        self.screen.tick()

    def back(self):
        back(allow_override=False, anim=False)

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

class Animation(Widget):
    spacing = 0.2

    def __init__(self, src, dest, dir):
        self.src = src
        self.dest = dest
        self.dir = dir
        self.samebg = getattr(self.src, 'screen_background', None) == getattr(self.dest, 'screen_background', None)
        self.screen_background = 0xFFFFFF

        self.frame = 0
        self.duration = 3

    def draw(self, surf, pos):
        width = screen_width * (self.spacing + 1)
        x, y = pos
        time = float(self.frame) / self.duration
        if self.dir == 1:
            a = self.src
            b = self.dest
            at = -time
        else:
            a = self.dest
            b = self.src
            at = time - 1
        a_x = int(at * width)
        b_x = int((at+1) * width)

        if not self.samebg:
            fill(surf, (b_x + x, y), b)
        else:
            fill(surf, (0, 0), b)
        b.draw(surf, (b_x + x, y))
        if not self.samebg:
            fill(surf, (a_x + x, y), a)
        a.draw(surf, (a_x + x, y))

    def tick(self):
        self.frame += 1
        if self.frame == self.duration:
            replace(self.dest)

    def event(self, ev):
        pass

    def back(self):
        return self.dest.back()

_fill_image = None
_fill_image_not_resized = None

def set_fill_image(image):
    global _fill_image, _fill_image_not_resized

    _fill_image_not_resized = image
    _fill_image = image

def fill(surf, rect, screen=None):
    surf.fill((200, 200, 200, 255))
    if _fill_image:
        size = graphics.get_window().get_size()
        surf.blit(_fill_image, dest=(rect[0], rect[1], size[0], size[1]))

LOCK_MOUSE_EVENT = object() # constant

class LayoutWidget(Widget):
    def __init__(self):
        self.items = []
        self.positions = []
        self.holds_mouse = None
        self.holds_mouse_pos = None
        self.last_hovered = None
        self.focus = None

    def add(self, item):
        assert isinstance(item, Widget)
        self.items.append(item)

    def unhover(self):
        for item in self.items:
            self._call_unhover(item)

    @staticmethod
    def _call_unhover(item):
        if hasattr(item, 'unhover'):
            item.unhover()

    def event(self, event):
        if hasattr(event, 'pos'):
            evpos = event.pos

            if self.holds_mouse:
                itemiter = self.get_items_at(evpos, (self.holds_mouse, self.holds_mouse_pos))
            else:
                itemiter = self.get_items_at(evpos)

            handled = False
            for item, itempos in itemiter:
                event.pos = _subpoints(event.pos, itempos)
                result = item.event(event)
                event.pos = _addpoints(event.pos, itempos)
                if result != False:
                    if self.last_hovered != item:
                        self._call_unhover(self.last_hovered)
                        self.last_hovered = None

                    if event.type == graphics.const.MOUSEBUTTONDOWN:
                        if result == LOCK_MOUSE_EVENT:
                            self.holds_mouse = item
                            self.holds_mouse_pos = itempos
                            return LOCK_MOUSE_EVENT
                        self.last_hovered = item
                    handled = True
                    break

            if event.type == graphics.const.MOUSEBUTTONUP:
                self.holds_mouse = None

            if not handled:
                self._call_unhover(self.last_hovered)
                self.last_hovered = None

            return handled
        else:
            if self.focus:
                self.focus.event(event)
            elif self.items:
                self.items[0].event(event)

    def get_position_of(self, item):
        if item in self.items:
            return self.positions[self.items.index(item)]
        for child in self.items:
            if hasattr(child, 'get_position_of'):
                child_pos = self.positions[self.items.index(child)]
                rel_pos = child.get_position_of(item)
                if rel_pos:
                    return rel_pos[0] + child_pos[0], rel_pos[1] + child_pos[1]
        return None

    def get_items_at(self, evpos, yield_this=None):
        if yield_this:
            yield yield_this
        for itempos, item in reversed(zip(self.positions, self.items)):
            relpos = _subpoints(evpos, itempos)
            if relpos[0] > 0 and relpos[1] > 0 and relpos[0] < item.size[0] and relpos[1] < item.size[1]:
                yield item, itempos

    def update_layout(self):
        for item in self.items:
            if hasattr(item, 'update_layout'):
                item.update_layout()

        self.positions = list(self.get_positions())

    def tick(self):
        for item in self.items:
            item.tick()

    def draw(self, surf, pos):
        self.positions = list(self.get_positions())

        for itempos, item in zip(self.positions, self.items):
            item.draw(surf, _addpoints(pos, itempos))

    def draw_clipped(self, surf, pos, rect):
        rect = graphics.Rect(rect)
        cliptex = graphics.create_surface(rect[2], rect[3])
        relpos = _subpoints(pos, (rect[0], rect[1]))
        self.positions = list(self.get_positions())

        for itempos, item in zip(self.positions, self.items):
            bpos = itempos[0] + pos[0], itempos[1] + pos[1]
            item.draw(cliptex, _addpoints(relpos, itempos))

        surf.blit(cliptex, (rect[0], rect[1]))

def _addpoints(a, b):
    return a[0] + b[0], a[1] + b[1]

def _subpoints(a, b):
    return a[0] - b[0], a[1] - b[1]

def render_text(font, text, color=(0, 0, 0)):
    if '\n' in text:
        lines = text.splitlines()
        renders = [ font.render(line, True, color) for line in lines ]
        w = max( render.get_width() for render in renders )
        h = sum( render.get_height() for render in renders )
        surf = graphics.create_surface(w, h)
        y = 0
        for render in renders:
            surf.blit(render, (0, y))
            y += render.get_height()
        return surf
    else:
        return font.render(text, True, color)

class Spacing(Widget):
    def __init__(self, x, y):
        self.size = (x, y)

    def draw(self, surf, pos):
        pass

class LinearLayoutWidget(LayoutWidget):
    def __init__(self, spacing=10, marginleft=0, center=False, force_full=False):
        LayoutWidget.__init__(self)
        self.spacing = spacing
        self.marginleft = marginleft
        self.center = center
        self.force_full = force_full
        self._size = (0, 0)

    @property
    def size(self):
        if self.force_full:
            return (screen_width, self._size[1])
        else:
            return self._size

    def get_positions(self):
        y = 0
        w = screen_width if self.force_full else max([ item.size[0] for item in self.items ] + [0])
        center_at = w*self.center if isinstance(self.center, (int, float)) else w
        for item in self.items:
            y += self.spacing
            centerx = (center_at - item.size[0])/2 if self.center else 0
            yield (self.marginleft + centerx, y)
            y += item.size[1]
        self._size = (w + self.marginleft, y)

class HorizontalLayoutWidget(LayoutWidget):
    def __init__(self, spacing=0, margintop=0):
        LayoutWidget.__init__(self)
        self.spacing = spacing
        self.margintop = margintop
        self.size = (0, 0)

    def get_positions(self):
        x = 0
        h = 0
        for item in self.items:
            x += self.spacing
            yield (x, self.margintop)
            x += item.size[0]
            h = max(h, item.size[1])
        self.size = (x, h)

BOTTOM = 1
LEFT = 0
RIGHT = 2
TOP = 0

class AbsoluteLayoutWidget(LayoutWidget):
    def __init__(self):
        LayoutWidget.__init__(self)
        self.size = (0, 0)

    def add(self, widget, pos, align=0):
        widget.pos = pos
        widget.align = align
        self.items.append(widget)

    def get_positions(self):
        sw, sh = 0, 0
        for item in self.items:
            pos = item.pos
            sw = max(sw, pos[0] + item.size[0])
            sh = max(sh, pos[1] + item.size[1])

        for item in self.items:
            pos = item.pos

            if item.align & BOTTOM:
                pos = pos[0], sh - pos[1] - item.size[1]
            elif item.align & RIGHT:
                pos = sw - pos[0] - item.size[0], pos[1]

            yield pos

        self.size = sw, sh

class Bordered(LinearLayoutWidget):
    def __init__(self, item, force_width=None):
        LinearLayoutWidget.__init__(self)
        self.force_width = force_width
        self.add(item)

    @property
    def size(self):
        if self.force_width:
            return self.force_width, self._size[1]
        else:
            return self._size

    def draw(self, surf, pos):
        surf.draw_rect((0, 0, 0), pos + self.size, 1)
        LinearLayoutWidget.draw(self, surf, pos)

FPS = 30

def add_overlay(overlay, pos):
    overlay.pos = pos
    overlays.append(overlay)

import threading

_execute_later_list = []
_execute_later_lock = threading.Lock()

def execute_later(func):
    with _execute_later_lock:
        _execute_later_list.append(func)

any_mouse_events = 0

def main_handle_events():
    global any_mouse_events
    events = merge_mouse_events(graphics.get_events())
    if not screen:
        return

    for event in events:
        ev_dict = event.dict
        if 'pos' in ev_dict:
            ev_dict = dict(ev_dict)
            x, y = ev_dict['pos']
            ev_dict['pos'] = x, y
            ev_dict['abs_pos'] = ev_dict['pos']
            any_mouse_events = time.time()
        if event.type == graphics.const.QUIT:
            back()
        elif event.type == graphics.const.KEYDOWN and event.key == graphics.const.K_ESCAPE:
            back()
        else:
            screen.event(Event(event.type, ev_dict))

def main_draw():
    surf = graphics.lock_window()
    try:
        fill(surf, (0,0))
        screen.draw(surf, (0, 0))

        for overlay in overlays:
            overlay.draw(surf, overlay.pos)
    finally:
        graphics.flip()

def main_dispatch_ticks():
    with _execute_later_lock:
        execute_later_list = list(_execute_later_list)
        _execute_later_list[:] = []

    screen.tick()

    for overlay in overlays:
        overlay.tick()

    for func in execute_later_list:
        func()

def main_tick():
    main_handle_events()
    main_dispatch_ticks()
    main_draw()

user_time_spent = 0

def main_tick_wrapper():
    global user_time_spent
    try:
        frame_start = time.time()

        main_tick()

        curr_time = time.time()
        frame_last = curr_time - frame_start
        sleep = (1./FPS) - frame_last
        if sleep > 0:
            time.sleep(sleep)
        USER_INACTIVITY_MAX = 10
        if any_mouse_events + USER_INACTIVITY_MAX > curr_time:
            # don't count time if user has locked screen or switched app
            # or haven't touched screen for long
            user_time_spent += min(frame_last, 1) + sleep
    except (KeyboardInterrupt, SystemExit):
        raise
    except:
        #if except_callback:
        #traceback.print_exc()
        #    except_callback()
        raise

def main():
    init_size()
    while True:
        main_tick_wrapper()

def init_size():
    wnd = graphics.lock_window()
    try:
        global screen_width, screen_height, screen_size
        screen_width, screen_height = screen_size = wnd.get_size()
    finally:
        graphics.flip()

def user_time_sleep(c):
    deadline = user_time_spent + c
    while True:
        to_sleep = deadline - user_time_spent
        if to_sleep < 0:
            break
        time.sleep(to_sleep)

def merge_mouse_events(events):
    mouse = None
    res = []
    for ev in events:
        if ev.type == graphics.const.MOUSEMOTION:
            mouse = ev
        else:
            res.append(ev)
    if mouse:
        res.append(mouse)
    return res

class Event(object):
    def __init__(self, type, dict):
        self.type = type
        for k, v in dict.items():
            setattr(self, k, v)

class WithText(Widget):
    def __init__(self, label, callback, font=None, color=None, padding=0, force_width=None, image=None):
        self.callback = callback
        self.font = font or mediumfont
        self.color = color or (0, 0, 0)
        self.label = None
        self.padding = padding
        self.force_width = force_width
        self.image = image
        self._scaled_image = None
        self._scaled_size = None
        self.set_text(label)

    def set_text(self, label):
        if label != self.label:
            self.label = label
            self.redraw()

    def redraw(self):
        self.label_image = render_text(self.font, self.label, self.color)
        size = self.label_image.get_size()
        if self.force_width:
            size = self.force_width, size[1]
        self.size = size[0] + self.padding*2, size[1] + self.padding*2
        self.padding_left = (self.size[0] - self.label_image.get_size()[0])/2
        self.padding_top = (self.size[1] - self.label_image.get_size()[1])/2

    def tick(self):
        pass

    def event(self, event):
        if event.type == graphics.const.MOUSEBUTTONUP:
            if self.callback:
                self.callback()

    def draw(self, surf, pos):
        surf.blit(self.label_image, (pos[0] + self.padding_left, pos[1] + self.padding_top))
        if self.image:
            if self._scaled_size != self.size:
                scale_w = float(self.size[0]) / self.image.get_width()
                scale_h = float(self.size[1]) / self.image.get_height()
                scale = min(scale_w, scale_h)
                w, h = self.image.get_size()
                self._scaled_image = self.image.scale((int(w*scale), int(h*scale)))
                self._scaled_size = self.size

            iw, ih = self._scaled_image.get_size()
            w, h = self.size
            surf.blit(self._scaled_image, (pos[0] + (w - iw)/2, pos[1] + (h - ih)/2))

def _round_rect(surface, color, rect, width, xr, yr):
    # draw normal rect
    surface.draw_rect(color, rect, width)

def round_rect(surf, bg, fg, rect, round=10):
    rect = graphics.Rect(rect)
    _round_rect(surf, bg, rect, 0, round, round)
    _round_rect(surf, fg, rect, 1, round, round)

class Button(WithText):
    active_bg = (255, 255, 200, 150)
    bg = (130, 100, 0, 90)
    fg = (150, 150, 50)

    def __init__(self, label, callback, font=None, color=None, force_width=None, force_height=None, image=None):
        WithText.__init__(self, label, callback, font, color, padding=4, force_width=force_width, image=image)
        self.active = False

    def draw(self, surf, pos):
        if self.active:
            color = self.active_bg
        else:
            color = self.bg
        surf.draw_rect(color, pos + self.size, width=0)
        surf.draw_rect(self.fg, pos + self.size, width=1)
        WithText.draw(self, surf, pos)

    def unhover(self):
        self.active = False

    def event(self, event):
        if event.type == graphics.const.MOUSEBUTTONDOWN:
            self.active = True
        elif event.type == graphics.const.MOUSEBUTTONUP:
            self.active = False
            if self.callback:
                self.callback()

class EditField(Button):
    def __init__(self, label='', font=None, color=None, placeholder=None):
        Button.__init__(self, label, self.callback, font, color)
        self.placeholder = placeholder
        self.set_value(label)

    def callback(self):
        import uidialog
        data = uidialog.inputbox('')
        if data != None:
            self.set_value(data)

    def set_value(self, data):
        self.value = data
        self.set_text(self.placeholder*len(data) if self.placeholder else data)

        if not self.value:
            self.set_text('<touch to change>')

    def get_value(self):
        return self.value

class Label(WithText):
    def __init__(self, label, callback=None, font=None, color=None, image=None):
        WithText.__init__(self, label, callback, font, color, image=image)

class Image(object):
    def __init__(self, image, callback=None):
        self.callback = callback
        self.image = image

    def tick(self):
        pass

    def event(self, event):
        if event.type == graphics.const.MOUSEBUTTONUP:
            if self.callback:
                self.callback()

    def draw(self, surf, pos):
        surf.blit(self.image, pos)

class Tooltip(Label):
    def __init__(self, text, pos, **kwargs):
        Label.__init__(self, text, **kwargs)
        add_overlay(self, pos)

    def remove(self):
        overlays.remove(self)

class Image(Widget):
    def __init__(self, img, callback=None):
        self.image = img
        self.size = self.image.get_size()
        self.callback = callback

    def event(self, event):
        if event.type == graphics.const.MOUSEBUTTONUP:
            if self.callback:
                self.callback()

    def draw(self, surf, pos):
        surf.blit(self.image, pos)

class Menu(LinearLayoutWidget):
    def __init__(self, font=None, force_full=True, center=True):
        LinearLayoutWidget.__init__(self, center=center, force_full=force_full)
        self.font = font or bigfont

    def add(self, label, callback, color=(0, 0, 0)):
        screen_width = graphics.get_window().get_width()
        self.items.append(Button(label, callback, self.font, color=color, force_width=0.5*screen_width))

    @staticmethod
    def yndialog(text, callback):
        def yes():
            callback()
            back()

        menu = Menu()
        menu.items.append(Label(text, color=BLUE))
        menu.add('Yes', yes)
        menu.add('No', back)
        set(menu)

def load_font(name, size):
    return graphics.load_font('fonts/ProcionoTT.ttf', size)

def load_image(name):
    return graphics.load_image(name)

def init():
    global font, smallfont, bigfont, mediumfont, consolefont
    graphics.init()

    consolefont = load_font(None, 20)
    smallfont = font = load_font(None, 25)
    mediumfont = load_font(None, 32)
    font = bigfont = load_font(None, 50)

SCROLL_HEIGHT = 1
SCROLL_WIDTH = 2

class ScrollWrapper(Widget):
    def __init__(self, item, height=None, width=None, ways=SCROLL_HEIGHT):
        self.item = item
        self.y = 0
        self.x = 0
        self.mul = 1
        self.start_dragging = None
        self.was_dragged = False
        self.height = height or screen_height
        self.width = width or screen_width
        self.use_y = ways & SCROLL_HEIGHT
        self.use_x = ways & SCROLL_WIDTH
        self.vx = 0
        self.vy = 0

    @property
    def size(self):
        return (self.width, self.height)

    def draw(self, surf, pos):
        fx, fy = 0, 0
        if self.use_x:
            fx -= self.x
        if self.use_y:
            fy -= self.y

        cliptex = graphics.create_surface(*self.get_clip())
        self.item.draw(cliptex, (fx, fy))
        surf.blit(cliptex, pos)

    def get_clip(self):
        return self.size

    def tick(self):
        self.x += self.vx
        self.y += self.vy

        if self.y > self.item.size[1] - self.height:
            self.y = self.item.size[1] - self.height
            self.vy = 0
        if self.y < 0:
            self.y = 0
            self.vy = 0

        if self.x > self.item.size[0] - self.width:
            self.x = self.item.size[0] - self.width
            self.vx = 0
        if self.x < 0:
            self.x = 0
            self.vx = 0

        self.vx -= _sgn(self.vx)
        self.vy -= _sgn(self.vy)

        self.item.tick()

    def event(self, event):
        if event.type == graphics.const.MOUSEBUTTONDOWN:
            self.vx = 0
            self.vy = 0
            self.start_dragging = event.pos
            self.start_dragging_abs = event.abs_pos
            self.was_dragged = False
            self.canceled_event(event)
            return LOCK_MOUSE_EVENT
        elif event.type == graphics.const.MOUSEMOTION:
            if self.start_dragging:
                dx, dy = _subpoints(self.start_dragging, event.pos)
                if (dx*dx+dy*dy) > 4:
                    self.start_dragging = event.pos
                    self.was_dragged = True
                    self.y += dy
                    self.x += dx
        elif event.type == graphics.const.MOUSEBUTTONUP:
            if self.was_dragged:
                dx, dy = _subpoints(self.start_dragging, event.pos)
                self.vx = _scroll_speed_func(self.vx, dx)
                self.vy = _scroll_speed_func(self.vy, dy)
                self.y += dy
                self.x += dx
            else:
                if self.start_dragging:
                    self.post_mouse_event(Event(graphics.const.MOUSEBUTTONDOWN, {'pos': self.start_dragging, 'abs_pos': self.start_dragging_abs}))
                self.post_mouse_event(event)
            self.start_dragging = None
            self.was_dragged = False
            self.canceled_event(event)
        else:
            self.item.event(event)

    def canceled_event(self, event):
        pass

    def post_mouse_event(self, ev):
        pos = ev.pos
        ev.pos = (pos[0] + self.x, pos[1] + self.y)
        self.item.event(ev)
        ev.pos = pos

    def back(self):
        return self.item.back()

def _scroll_speed_func(v, k):
    if abs(k) < 3:
        return v / 3
    else:
        if abs(k) > 5:
            k = 5 if k > 0 else -5
        return v + (k * 5)

def _sgn(f):
    return 1 if f>0 else (0 if f==0 else -1)
