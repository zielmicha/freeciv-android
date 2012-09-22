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

import ui
import uidialog
import pygame

import sync
import save
import features
import options
import tutorial

class SpacingLayoutWidget(ui.LayoutWidget):
    def __init__(self, item1, item2, size):
        ui.LayoutWidget.__init__(self)
        self.item1 = item1
        self.item2 = item2
        self.items = (item1, item2)
        self.size = (0,0)
        self._asked_size = size
    
    def get_positions(self):
        assert sum(map(lambda a:0 if a==0 else 1, self._asked_size)) == 1, 'exactly one value in tuple `size` should be zero'
        is_horizontal = self._asked_size[1] == 0
        if is_horizontal:
            w = self._asked_size[0]
            self.size = (w, max(self.item1.size[1], self.item2.size[1]))
            yield (0, 0)
            yield (w - self.item2.size[0], 0)
        else:
            h = self._asked_size[1]
            self.size = (max(self.item1.size[0], self.item2.size[0]), h)
            yield (0, 0)
            yield (0, h - self.item2.size[1])

def create_aligned_widget(widget, align, size=None):
    if not size:
        size = ui.screen_size
    if align & ui.RIGHT:
        widget = SpacingLayoutWidget(ui.Spacing(0,0), widget, (size[0], 0))
    if align & ui.BOTTOM:
        widget = SpacingLayoutWidget(ui.Spacing(0,0), widget, (0, size[1]))
    return widget

class PrettyMenu(ui.AbsoluteLayoutWidget):
    def __init__(self):
        ui.AbsoluteLayoutWidget.__init__(self)
        
        self.load_background()
        
        self.left = ui.HorizontalLayoutWidget(spacing=10)
        self.left.add(ui.Spacing(0, 0))
        self.right = ui.HorizontalLayoutWidget(spacing=10)
        self.cont = SpacingLayoutWidget(self.left, self.right, (ui.screen_width, 0))
        self.add(create_aligned_widget(self.cont, ui.BOTTOM, (0, ui.screen_height - 10)), (0,0))
    
    balloon_margin = 30
    
    def show_balloon(self, over, baloon):
        self.update_layout()
        baloon.update_layout()
        pos = self.get_position_of(over)
        self.add(baloon, (pos[0], pos[1] - baloon.size[1] - self.balloon_margin))
    
    def toggle_balloon(self, over, baloon):
        if baloon in self.items:
            self.items.remove(baloon)
        else:
            self.show_balloon(over, baloon)
    
    def load_background(self):
        img = ui.load_image('data/user/intro.jpg')
        img_size = img.get_size()
        surf_size = ui._fill_image.get_size()
        new_height = float(surf_size[0]) / img_size[0] * img_size[1]
        if new_height < surf_size[1]:
            new_height = surf_size[1]
        self.background_margin_top = (new_height - surf_size[1]) / -2.5
        self.background = pygame.transform.smoothscale(img, (surf_size[0], int(new_height)))
    
    def draw(self, surf, (x, y)):
        surf.blit(self.background, (x, y + self.background_margin_top))
        super(PrettyMenu, self).draw(surf, (x, y))

class MenuButton(ui.Button):
    active_bg = (255, 255, 200, 20)
    bg = (150, 150, 50, 80)
    fg = (150, 150, 50)
    
    def __init__(self, text, callback, **kwargs):
        ui.Button.__init__(self, text, callback, force_width=100, **kwargs)
    
    def set_text(self, label):
        if '\n' not in label:
            label += '\n '
        ui.Button.set_text(self, label)

class RedMenuButton(MenuButton):
    bg = (220, 150, 50, 110)

class BalloonButton(ui.Button):
    bg = (220, 150, 0, 110)
    
    def __init__(self, text, callback, **kwargs):
        ui.Button.__init__(self, text, callback, force_width=100, **kwargs)

class Balloon(ui.AbsoluteLayoutWidget):
    margin = 10
    
    def __init__(self):
        ui.AbsoluteLayoutWidget.__init__(self)
        self.content = ui.HorizontalLayoutWidget()
        self.add(self.content, (self.margin, self.margin))
    
    def draw(self, surf, pos):
        rect = pos + (self.content.size[0] + self.margin*2, self.content.size[1] + self.margin*2)
        tpos = (pos[0] + 10, pos[1] + self.content.size[1] + self.margin*2 - 1)
        tw = th = 18
        
        ui._round_rect(surf, (255,255,255,255), rect, 0, 10, 10)
        pygame.gfxdraw.trigon(surf, tpos[0], tpos[1], tpos[0]+tw, tpos[1], tpos[0], tpos[1]+th, (255,255,255))
        pygame.gfxdraw.filled_trigon(surf, tpos[0], tpos[1], tpos[0]+tw, tpos[1], tpos[0], tpos[1]+th, (255,255,255))
        ui._round_rect(surf, (255,255,0,255), rect, 1, 10, 10)
        ui.AbsoluteLayoutWidget.draw(self, surf, pos)

class _D(ui.Label):
    'Label that prints its pos - for debugging'
    def draw(self, surf, pos):
        print pos, '(clip=%r)' % surf.get_clip()
        ui.Label.draw(self, surf, pos)

main_menu_item = None
main_menu_update_shown = False

def main_menu():
    global main_menu_item
    main_menu_item = menu = PrettyMenu()
    
    menu.add(ui.Label('version %s' % features.get('app.version'), color=(255, 0, 0, 150), font=ui.consolefont), (0, 0))
    new_game_button = MenuButton('New\ngame', new_game_menu)
    menu.left.add(new_game_button)
    load_game_button = MenuButton('Load\ngame', save.load_dialog)
    menu.left.add(load_game_button)
    if features.get('app.multiplayer'):
        menu.left.add(MenuButton('Connect', save.connect_dialog))
    
    menu.right.add(MenuButton('Feed\nback', feedback))
    menu.right.add(MenuButton('', options.show_options, image=ui.load_image('data/user/options.png').convert_alpha()))
    menu.right.add(MenuButton('Exit', ui.back))
    menu.right.add(ui.Spacing(0, 0))
    
    ui.replace(menu)

def new_game_menu():
    menu = ui.Menu(force_full = False)
    
    menu.add('Tutorial', tutorial.start)    
    menu.add('Random', save.new_game)
    menu.add('Scenario', save.load_scenario)
    
    ui.set_dialog(menu)

def notify_update(url):
    if not main_menu_item:
        # game was started by "load" command
        print 'not showing update button'
        return
    
    def callback():
        button.set_text('Loading...')
        button.callback = None
        with ui.execute_later_lock:
            ui.execute_later.append(lambda: uidialog.open_url(url))
    
    global main_menu_update_shown
    if main_menu_update_shown:
        return
    main_menu_update_shown = True
    #panel = ui.LinearLayoutWidget()
    #panel.add(ui.Label('There is an update available!'))
    button = RedMenuButton('  New\nversion!', callback)
    #panel.add(button)
    main_menu_item.left.add(button)

def feedback():
    panel = ui.LinearLayoutWidget()
    panel.add(ui.Label('Leaving comments with logs will help me diagnose\npotential problems with game speed and\nunexpected behaviour.'))
    panel.add(ui.Button('Leave a comment with a log (preferred)', lambda: sync.comment(sync.get_install_time(), True)))
    panel.add(ui.Button('Leave a comment without a log', lambda: sync.comment(sync.get_install_time(), False)))
    ui.set(panel)
