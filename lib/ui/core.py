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

import ui

history = []
overlays = []
_screen = None
_allow_animation = 0

show_fps = False

def set_show_fps(val):
    global show_fps
    show_fps = val

def create_window(size):
    graphics.init()
    fullscreen = features.get('ui.fullscreen')
    if fullscreen:
        size = graphics.get_screen_size()
    graphics.create_window(size, fullscreen=fullscreen)
    if features.get('ui.offscreen'):
        graphics.set_offscreen_window(size)

features.set_applier('ui.showfps', set_show_fps, type=bool, default=False)
features.add_feature('ui.enable_anim', type=bool, default=True)
features.add_feature('ui.fps_limit', type=int, default=30)
features.add_feature('ui.redraw_fps_limit', type=int, default=60)
features.add_feature('ui.offscreen', type=bool, default=False)
features.add_feature('ui.fullscreen', type=bool, default=True)

features.add_feature('stream.enable', type=bool, default=False)
features.add_feature('stream.fd', type=int, default=2)

def replace(new_screen):
    assert isinstance(new_screen, ui.Widget)
    global _screen
    _screen = new_screen
    _set_allow_animation(0)

def replace_anim(new_screen, direction=1):
    if features.get('ui.enable_anim'):
        replace(ui.Animation(get_screen(), new_screen, direction))
    else:
        replace(new_screen)
    _set_allow_animation(direction)

def set(new_screen, anim=True, no_stack=False):
    new_screen._no_stack = no_stack
    if _screen:
        history.append(_screen)
        if anim:
            replace_anim(new_screen)
        else:
            replace(new_screen)
    else:
        replace(new_screen)

def get_allow_animation():
    return _allow_animation

def _set_allow_animation(val):
    global _allow_animation
    _allow_animation = val

def get_screen():
    return _screen

def set_screen(new):
    global _screen
    _screen = new

def back(allow_override=True, anim=True):
    while history and getattr(history[-1], '_no_stack', False):
        history.pop()
    if allow_override and _screen.back() is not True:
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

_fill_image = None
_fill_image_not_resized = None

def set_fill_image(image):
    global _fill_image, _fill_image_not_resized

    _fill_image_not_resized = image
    _fill_image = image

def fill(surf, rect, screen=None):
    if _fill_image:
        size = graphics.get_window().get_size()
        surf.blit(_fill_image, dest=(rect[0], rect[1], size[0], size[1]))
    else:
        surf.fill((255, 255, 255, 0), blend=graphics.MODE_NONE)

LOCK_MOUSE_EVENT = object() # constant

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

def add_overlay(overlay, pos):
    overlay.pos = pos
    overlays.append(overlay)

class Timer(object):
    def __init__(self):
        self.last = 0

    def capture(self):
        self.last = time.time()

    def get_time_delta(self):
        return time.time() - self.last

import threading

class HookList:
    def __init__(self):
        self.list = []
        self.lock = threading.Lock()

    def execute_and_clear(self, *args, **kwargs):
        values = self.clear()
        for callback in values:
            callback(*args, **kwargs)

    def execute(self, *args, **kwargs):
        for callback in self.list:
            callback(*args, **kwargs)

    def clear(self):
        with self.lock:
            l = list(self.list)
            self.list[:] = []
            return l

    def add(self, func):
        with self.lock:
            self.list.append(func)

    def is_bound(self):
        return len(self.list) != 0

    def decorator(self, func):
        return lambda *args, **kwargs: self.add(lambda: func(*args, **kwargs))

tick_hooks = HookList()
draw_hooks = HookList()
layer_hooks = HookList()
idle_hooks = HookList()

# `backward` compatibility
execute_later = tick_hooks.add
execute_later_decorator = tick_hooks.decorator

def async(thing, then=None):
    def wrapper():
        result = thing()
        if then:
            execute_later(lambda: then(result))

    threading.Thread(target=wrapper).start()

def main_tick():
    any_events = main_handle_events()
    if any_events:
        main_draw()
    else:
        main_maybe_draw()
    main_dispatch_ticks()

any_mouse_events = 0
syntetic_events = []

def main_handle_events():
    global any_mouse_events
    events = merge_mouse_events(graphics.get_events() + syntetic_events)
    syntetic_events[:] = []
    if not _screen:
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
            _screen.event(Event(event.type, ev_dict))

    return bool(events)

last_draw = Timer()

def main_maybe_draw():
    if last_draw.get_time_delta() > 1. / features.get('ui.redraw_fps_limit'):
        main_draw()

def main_draw():
    last_draw.capture()

    surf = graphics.get_window()
    fill(surf, (0,0))

    _screen.update_layout()
    _screen.draw(surf, (0, 0))

    for overlay in overlays:
        overlay.draw(surf, overlay.pos)

    draw_hooks.execute_and_clear()

    graphics.flip()

def main_dispatch_ticks():
    tick_hooks.execute_and_clear()

    _screen.update_layout()
    _screen.tick()

    for overlay in overlays:
        overlay.tick()

user_time_spent = 0

def main_tick_wrapper():
    global user_time_spent
    try:
        frame_start = time.time()

        main_tick()

        curr_time = time.time()
        frame_last = curr_time - frame_start
        sleep = (1./features.get('ui.fps_limit')) - frame_last
        idle_sleep(sleep)
        USER_INACTIVITY_MAX = 10
        if any_mouse_events + USER_INACTIVITY_MAX > curr_time:
            # don't count time if user has locked screen or switched app
            # or haven't touched screen for long
            user_time_spent += min(frame_last, 1) + sleep
    except (KeyboardInterrupt, SystemExit):
        raise
    except:
        traceback.print_exc()
        if ui.except_callback:
            ui.except_callback()
        time.sleep(0.5)

def idle_sleep(t):
    if idle_hooks.is_bound():
        idle_hooks.execute(t)
    elif t > 0:
        time.sleep(t)

def main():
    ui.screen_width, ui.screen_height = ui.screen_size = graphics.get_window().get_size()
    while True:
        main_tick_wrapper()

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

def load_font(name, size):
    return graphics.load_font('fonts/ProcionoTT.ttf', size)

def load_image(name):
    return graphics.load_image(name)

def init():
    graphics.init()

    ui.consolefont = load_font(None, 20)
    ui.smallfont = font = load_font(None, 25)
    ui.mediumfont = load_font(None, 32)
    ui.font = ui.bigfont = load_font(None, 50)

    if features.get('stream.enable'):
        from . import stream
        stream.init()

class Event(object):
    def __init__(self, type, dict):
        self.type = type
        for k, v in dict.items():
            setattr(self, k, v)
