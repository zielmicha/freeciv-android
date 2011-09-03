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

import pygame
import pygame.gfxdraw
import time

history = []
screen = None
overlays = []

screen_height = 0
screen_width = 0
screen_size = 0, 0

def replace(new_screen):
    global screen
    screen = new_screen

def replace_anim(new_screen, direction=1):
    replace(Animation(screen, new_screen, direction))

def set(new_screen, anim=True):
    if screen:
        history.append(screen)
        if anim:
            replace_anim(new_screen)
        else:
            replace(new_screen)
    else:
        replace(new_screen)

def set_dialog(new_screen, scroll=False):
    if scroll:
        item = ScrollWrapper(new_screen, height=screen_height*0.7, width=screen_width*0.7, ways=SCROLL_HEIGHT|SCROLL_WIDTH)
    else:
        item = new_screen
    set(Dialog(screen, item), anim=False)

class Dialog(object):
    def __init__(self, screen, item):
        self.item = item
        self.screen = screen
    
    def draw(self, surf, pos):
        self.screen.draw(surf, pos)
        pygame.gfxdraw.box(surf, (0, 0) + screen_size, (255, 255, 255, 100))
        
        x, y = self.get_pos()
        size = self.item.size
        rect = (x + pos[0], y + pos[1]) + size
        
        pygame.draw.rect(surf, (255, 255, 255), rect)
        self.item.draw(surf, (x + pos[0], y + pos[1]))
        pygame.draw.rect(surf, (0, 0, 0), rect, 1)
    
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
            result = self.item.event(ev)
            ev.pos = _addpoints(ev.pos, pos)
            return result
        else:
            self.item.event(ev)

class Animation(object):
    spacing = 0.2
    
    def __init__(self, src, dest, dir):
        self.src = src
        self.dest = dest
        self.dir = dir
        self.samebg = getattr(self.src, 'screen_background', None) == getattr(self.dest, 'screen_background', None)
        self.screen_background = 0xFFFFFF
        
        self.frame = 0
        self.duration = 6
    
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

_fill_image = None
_fill_image_not_resized = None

def set_fill_image(image):
    global _fill_image, _fill_image_not_resized
    
    _fill_image_not_resized = image
    _fill_image = pygame.transform.smoothscale(image, pygame.display.get_surface().get_size())

def fill(surf, rect, screen=None):
    if not _fill_image:
        surf.fill((255, 255, 255), rect + (screen_size or pygame.display.get_surface().get_size()))
    else:
        surf.blit(_fill_image, rect)

LOCK_MOUSE_EVENT = object() # constant

class LayoutWidget(object):
    def __init__(self):
        self.items = []
        self.positions = []
        self.holds_mouse = None
        self.holds_mouse_pos = None
        self.last_hovered = None
        self.focus = None
    
    def add(self, item):
        assert item != None
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
                    
                    if event.type == pygame.MOUSEBUTTONDOWN:
                        if result == LOCK_MOUSE_EVENT:
                            self.holds_mouse = item
                            self.holds_mouse_pos = itempos
                            return LOCK_MOUSE_EVENT
                        self.last_hovered = item
                    handled = True
                    break
            
            if event.type == pygame.MOUSEBUTTONUP:
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
        surf = pygame.Surface((w, h), pygame.SRCALPHA)
        y = 0
        for render in renders:
            surf.blit(render, (0, y))
            y += render.get_height()
        return surf
    else:
        return font.render(text, True, color)

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
        for item in self.items:
            y += self.spacing
            centerx = (w - item.size[0])/2 if self.center else 0
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

def back(allow_override=True, anim=True):
    if allow_override and hasattr(screen, 'back'):
        screen.back()
    elif not history:
        raise SystemExit
    else:
        new_screen = history.pop()
        if anim:
            replace_anim(new_screen, -1)
        else:
            replace(new_screen)

FPS = 15

autoscale_enabled = False
autoscale_scale = 1

def add_overlay(overlay, pos):
    overlay.pos = pos
    overlays.append(overlay)

def set_autoscale(surf):
    global autoscale_enabled, _fill_image, autoscale_scale
    autoscale_enabled = True
    
    h = surf.get_height() * 600 / surf.get_width()
    autoscale_scale = 600.0 / surf.get_width()
    
    if _fill_image:
        _fill_image = pygame.transform.smoothscale(_fill_image_not_resized, (600, h))
    
    dest = pygame.Surface((600, h))
    
    return dest
    
def autoscale_flip(surf):
    display = pygame.display.get_surface()
    pygame.transform.smoothscale(surf, display.get_size(), display)
    pygame.display.flip()

def flip(surf):
    if autoscale_enabled:
        autoscale_flip(surf)
    else:
        pygame.display.flip()

def maybe_set_autoscale(surf):
    if surf.get_width() < 600:
        return set_autoscale(surf)
    else:
        global autoscale_scale, autoscale_enabled
        autoscale_enabled = False
        autoscale_scale = 1
        return surf
    

def main():
    global screen_width, screen_height, screen_size
    lost_time = 0.0
    per_frame = 1./FPS
    frame_last = 0
    surf = pygame.display.get_surface()
    surf = maybe_set_autoscale(surf)
    screen_width, screen_height = screen_size = surf.get_size()
    while True:
        frame_start = time.time()
        events = pygame.event.get()
        if not screen:
            continue
        was_motion = False
        for event in events:
            ev_dict = event.dict
            if 'pos' in ev_dict:
                ev_dict = dict(ev_dict)
                x, y = ev_dict['pos']
                ev_dict['pos'] =int(x*autoscale_scale), int(y*autoscale_scale)
                ev_dict['abs_pos'] = ev_dict['pos']
            if event.type == pygame.QUIT:
                back()
            elif event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                back()
            elif event.type == pygame.MOUSEMOTION:
                if not was_motion:
                    was_motion = True
                    screen.event(Event(event.type, ev_dict))
            else:
                screen.event(Event(event.type, ev_dict))
        screen.tick()
        
        for overlay in overlays:
            overlay.tick()
        
        fill(surf, (0,0))
        screen.draw(surf, (0, 0))
        
        for overlay in overlays:
            overlay.draw(surf, overlay.pos)
        
        frame_last = time.time() - frame_start
        sleep = per_frame - frame_last
        if sleep > 0:
            time.sleep(sleep)
        else:
            lost_time += -sleep
        
        flip(surf)

class Event(object):
    def __init__(self, type, dict):
        self.type = type
        for k, v in dict.items():
            setattr(self, k, v)

class WithText(object):
    def __init__(self, label, callback, font=None, color=None, padding=0):
        self.callback = callback
        self.font = font or mediumfont
        self.color = color or (0, 0, 0)
        self.label = None
        self.padding = padding
        self.set_text(label)
    
    def set_text(self, label):
        if label != self.label:
            self.label = label
            self.label_image = render_text(self.font, label, self.color)
            size = self.label_image.get_size()
            self.size = size[0] + self.padding*2, size[1] + self.padding*2
            self.padding_left = (self.size[0] - self.label_image.get_size()[0])/2
            self.padding_top = (self.size[1] - self.label_image.get_size()[1])/2
    
    def tick(self):
        pass
    
    def event(self, event):
        if event.type == pygame.MOUSEBUTTONUP:
            if self.callback:
                self.callback()
    
    def draw(self, surf, pos):
        surf.blit(self.label_image, (pos[0] + self.padding_left, pos[1] + self.padding_top))

class Button(WithText):
    def __init__(self, label, callback, font=None, color=None):
        WithText.__init__(self, label, callback, font, color, padding=4)
        self.active = False
    
    def draw(self, surf, pos):
        pygame.draw.rect(surf, (255, 255, 255), pos + self.size, 1)
        if self.active:
            color = (255, 255, 255)
        else:
            color = (255, 255, 0, 50)
        pygame.gfxdraw.box(surf, pos + self.size, color)
        WithText.draw(self, surf, pos)
    
    def unhover(self):
        self.active = False
    
    def event(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN:
            self.active = True
        elif event.type == pygame.MOUSEBUTTONUP:
            self.active = False
            if self.callback:
                self.callback()

class Label(WithText):
    def __init__(self, label, callback=None, font=None, color=None):
        WithText.__init__(self, label, callback, font, color)

class Image(object):
    def __init__(self, image, callback=None):
        self.callback = callback
        self.image = image
    
    def tick(self):
        pass
    
    def event(self, event):
        if event.type == pygame.MOUSEBUTTONUP:
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

class Image(object):
    def __init__(self, img, callback=None):
        self.image = img
        self.size = self.image.get_size()
        self.callback = callback
    
    def tick(self):
        pass
    
    def event(self, event):
        if event.type == pygame.MOUSEBUTTONUP:
            if self.callback:
                self.callback()
    
    def draw(self, surf, pos):
        surf.blit(self.image, pos)

class Menu(LinearLayoutWidget):
    def __init__(self, font=None, force_full=True, center=True):
        LinearLayoutWidget.__init__(self, center=center, force_full=force_full)
        self.font = font or bigfont
    
    def add(self, label, callback, color=(0, 0, 0)):
        self.items.append(Button(label, callback, self.font, color=color))
    
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
    path = 'ttf/%s.ttf' % name
    return pygame.font.Font('Ubuntu-R.ttf', size)

def init():
    global font, smallfont, bigfont, mediumfont, consolefont
    pygame.init()
    
    consolefont = load_font('Cosmetica', 20)
    smallfont = font = load_font('Cosmetica', 25)
    mediumfont = load_font('Classic Robot', 32)
    font = bigfont = load_font('Classic Robot', 50)
    
SCROLL_HEIGHT = 1
SCROLL_WIDTH = 2

class ScrollWrapper(object):
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
    
    @property
    def size(self):
        return (self.width, self.height)
    
    def draw(self, surf, pos):
        x, y = pos
        fx, fy = pos
        if self.use_x:
            fx -= self.x
        if self.use_y:
            fy -= self.y
        
        last = surf.get_clip()
        surf.set_clip(self.get_clip(pos))
        self.item.draw(surf, (fx, fy))
        surf.set_clip(last)
    
    def get_clip(self, pos):
        return pos + self.size
    
    def tick(self):
        if self.y > self.item.size[1] - self.height:
            self.y = self.item.size[1] - self.height
        if self.y < 0:
            self.y = 0
        
        if self.x > self.item.size[0] - self.width:
            self.x = self.item.size[0] - self.width
        if self.x < 0:
            self.x = 0
        
        self.item.tick()
    
    def event(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN:
            self.start_dragging = event.pos
            self.start_dragging_abs = event.abs_pos
            self.was_dragged = False
            self.canceled_event(event)
            return LOCK_MOUSE_EVENT
        elif event.type == pygame.MOUSEMOTION:
            if self.start_dragging:
                dx, dy = _subpoints(self.start_dragging, event.pos)
                if (dx*dx+dy*dy) > 4:
                    self.start_dragging = event.pos
                    self.was_dragged = True
                    self.y += dy
                    self.x += dx
        elif event.type == pygame.MOUSEBUTTONUP:
            if self.was_dragged:
                dx, dy = _subpoints(self.start_dragging, event.pos)
                self.y += dy
                self.x += dx
            else:
                if self.start_dragging:
                    self.post_mouse_event(Event(pygame.MOUSEBUTTONDOWN, {'pos': self.start_dragging, 'abs_pos': self.start_dragging_abs}))
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
        ev.pos = (pos[0], pos[1] + self.y)
        self.item.event(ev)
        ev.pos = pos