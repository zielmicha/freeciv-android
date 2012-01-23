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
import client
import pygame
import pygame.gfxdraw
import functools

from client import freeciv

import citydlg
import gamemenu
import icons
import sync
import features
import diplodialog
import empiredlg

SELECT_POPUP = 0

class ScreenClient(client.Client):
    def __init__(self, **kwargs):
        client.Client.__init__(self, **kwargs)
        self.turn_loading_dialog = None
        self.init_ui()
    
    def init_ui(self):
        self.ui = ScreenWidget(self)
    
    #def console_line(self, line):
    #    self.ui.console.line(line)
    
    def update_meswin(self, lines):
        self.ui.console.clear()
        for line, attrs, tile in lines:
            self.ui.console.line(line)
    
    def popup_city_dialog(self, city):
        dialog = citydlg.Dialog(self, city)
        ui.set(dialog.ui)
    
    def overview_size_changed(self, w, h):
        self.ui.resize_left_pane(self.ui.overview.size[0])
    
    def update_menus(self, unit):
        actions = unit.get_actions()
        self.ui.menu.update(actions)
    
    def disable_menus(self):
        self.ui.menu.update(None)
    
    def popup_unit_select_dialog(self, units):
        def focus(unit):
            unit.focus()
            ui.back()
        
        panel = ui.LinearLayoutWidget()
        for unit in units:
            name = unit.get_name()
            callback = functools.partial(focus, unit)
            panel.add(ui.Button(name, callback))
        ui.set_dialog(panel, scroll=True)
    
    def quit(self):
        def quit():
            self.disconnect()
            ui.back(anim=False) # close dialog
            ui.back(allow_override=False) # close game
        
        def save():
            self.chat('/save')
            ui.back()
        
        def save_and_sync():
            sync.save_and_sync(self)
        
        menu = ui.Menu(center=0.7)
        menu.add('Quit', quit)
        menu.add('Save', save)
        if features.get('civsync.enable'):
            menu.add('Save & sync', save_and_sync)
        ui.set_dialog(menu, scroll=True)
    
    def city_dialog_is_open(self, city):
        if not isinstance(ui.screen, ui.ScrollWrapper):
            return False
        item = ui.screen.item
        if isinstance(item, citydlg.Dialog) and item.city == city:
            return True
        else:
            return False
    
    def refresh_city_dialog(self, city):
        if self.city_dialog_is_open(city):
            ui.screen.item.refresh()
    
    def update_taxes(self):
        return self.ui.taxes_panel.update()
    
    def create_meeting(self, counterpart):
        return diplodialog.Meeting(self, counterpart)
    
    def set_turn_button_enable(self, enabled):
        dialog_state = self.turn_loading_dialog.is_opened() if self.turn_loading_dialog else False
        if not enabled and not dialog_state:
            self.turn_loading_dialog = ui.set_dialog(ui.Label('ending turn...'))
        elif dialog_state and enabled:
            self.turn_loading_dialog.close()
    
    def handle_authentication_req(self, prompt):
        password = uidialog.inputbox(prompt)
        if password:
            self.authenticate(password)

class ScreenWidget(ui.HorizontalLayoutWidget):
    def __init__(self, client):
        super(ScreenWidget, self).__init__()
        self.client = client
        
        self.map = MapWidget(client)
        self.overview = OverviewWidget(client)
        self.console = ConsoleWidget(client)
        self.menu = gamemenu.Menu(client)
        self.end_turn_button = ui.Button('End turn', self.client.end_turn)
        self.empire_button = ui.Button('Empire', self.empire_dialog)
        self.taxes_panel = TaxesPanel(client)
        
        self.left_panel = ui.LinearLayoutWidget(spacing=0, center=True)
        self.map_wrapper = ui.AbsoluteLayoutWidget()
        
        self.add(self.left_panel)
        self.add(self.map_wrapper)
        
        self.map_wrapper.add(self.map, (0, 0))
        self.map_wrapper.add(self.menu, (0, 0), align=ui.BOTTOM)
        
        self.left_panel.add(self.overview)
        self.left_panel.add(self.console.scroll)
        self.left_panel.add(self.end_turn_button)
        self.left_panel.add(self.taxes_panel)
        self.left_panel.add(ui.Spacing(0, 10))
        self.left_panel.add(self.empire_button)
        
        # key_end_turn()
        
        self.focus = self.map
    
    def resize_left_pane(self, width):
        self.console.width = width
        self.console.scroll.width = width
        self.console.scroll.height = 100
    
    def empire_dialog(self):
        empiredlg.EmpireDialog(self.client).show()
    
    def tick(self):
        self.map.size = ui.screen_width - self.overview.size[0], ui.screen_height
        self.client.tick()
        super(ScreenWidget, self).tick()
    
    def back(self):
        self.map.back()

class TaxesPanel(ui.LinearLayoutWidget):
    def __init__(self, client):
        ui.LinearLayoutWidget.__init__(self, spacing=10)
        self.client = client
        self.update()
    
    def update(self):
        self.items = []
        
        self.update_year()
        self.update_gold_label()
        self.update_tax()
        self.update_layout()
    
    def update_gold_label(self):
        plus = self.client.get_gold_income()
        if plus >= 0:
            plus = '+%d' % plus
        else:
            plus = '%s' % plus
        
        self.add(ui.Label('Gold: %d (%s)' % (self.client.get_gold(), plus), font=ui.consolefont))
    
    def update_tax(self):
        panel = ui.HorizontalLayoutWidget()
        tax, lux, science = self.client.get_tax_values()
        
        science_img = icons.get_small_image('scientist')
        tax_img = icons.get_small_image('taxman')
        lux_img = icons.get_small_image('elvis')
        
        def add(value, img):
            for i in xrange(value/10):
                panel.add(ui.Image(img))
        
        add(tax, tax_img)
        add(lux, lux_img)
        add(science, science_img)
        
        self.add(panel)
    
    def update_year(self):
        year = self.client.get_current_year_name()
        self.add(ui.Label('Year: ' + year, font=ui.consolefont))
    
    def event(self, ev):
        if ev.type == pygame.MOUSEBUTTONDOWN:
            self.callback()
    
    def callback(self):
        ui.set_dialog(TaxesDialog(self.client))

class TaxesDialog(ui.LinearLayoutWidget):
    def __init__(self, client):
        ui.LinearLayoutWidget.__init__(self)
        self.client = client        
        self.update()
        
    def update(self):
        self.items = []
        self.update_tax()
        self.update_buttons()
        self.update_layout()
        
    def update_tax(self):
        panel = ui.LinearLayoutWidget()
        tpl = list(self.client.get_tax_values())
        
        science_img = icons.get_small_image('scientist')
        tax_img = icons.get_small_image('taxman')
        lux_img = icons.get_small_image('elvis')
        
        font = ui.bigfont
        
        def change(type, val):
            tpl[type] += val * 10
            tpl[0] -= val * 10
            a, b, c = map(lambda x: max(0, min(100, x)), tpl)
            self.client.set_tax_values(a, b, c)
            ui.screen.tick()
            self.update()
        
        def add(type, img):
            # spacing here are hard-coded so the layout breaks when font is changed
            img = pygame.transform.smoothscale(img, (30, 45))
            line = ui.HorizontalLayoutWidget()
            img_l = ui.LinearLayoutWidget()
            img_l.add(ui.Image(img))
            img_l.add(ui.Spacing(0, 6))
            line.add(img_l)
            if type != 0:
                line.add(ui.Spacing(10, 0))
                line.add(ui.Button(' - ', functools.partial(change, type, -1), font=font))
                line.add(ui.Spacing(10, 0))
                line.add(ui.Button(' + ', functools.partial(change, type, +1), font=font))
            else:
                line.add(ui.Spacing(123, 0))
            line.add(ui.Spacing(10, 0))
            line.add(ui.Label('%d%%' % tpl[type], font=font))
            panel.add(line)
        
        add(0, tax_img)
        add(1, lux_img)
        add(2, science_img)
        
        self.add(panel)
    
    def update_buttons(self):
        self.add(ui.Button('Change government', self.change_goverment))
    
    def change_goverment(self):
        def commit_government_change(gov):
            gov.change_to()
            ui.back()
        
        panel = ui.LinearLayoutWidget()
        for gov in self.client.get_governments():
            panel.add(ui.Label(gov.name, functools.partial(commit_government_change, gov)))
        ui.set_dialog(panel, scroll=True)

class OverviewWidget(object):
    def __init__(self, client):
        self.client = client
        self.scale_width = 150
    
    @property
    def size(self):
        w, h = self.client.get_overview_size()
        ratio = h / float(w)
        return (self.scale_width, int(ratio * self.scale_width))
    
    def tick(self):
        pass
    
    def event(self, ev):
        pass
    
    def draw(self, surf, pos):
        self.client.draw_overview(surf, pos, scale=self.size)
        pygame.draw.rect(surf, (255,255,255), pos + self.size, 1)

class ConsoleWidget(ui.LinearLayoutWidget):
    def __init__(self, client):
        super(ConsoleWidget, self).__init__(spacing=0)
        self.client = client
        self.width = 0
        self.scroll = ConsoleScrollWrapper(self)
        self.shown = False
    
    @property
    def size(self):
        return (self.width, self._size[1])
    
    def line(self, text):
        self.add(ui.Label(text, font=ui.consolefont))
    
    def clear(self):
        self.items = []
    
    def draw(self, surf, pos):
        if self.shown:
            pygame.gfxdraw.box(surf, pos + self._size, (255, 255, 255, 170))
        super(ConsoleWidget, self).draw(surf, pos)
    
    def draw_clipped(self, surf, pos, clip):
        old_clip = surf.get_clip()
        surf.set_clip(clip)
        
        self.draw(surf, pos)
        
        surf.set_clip(old_clip)
    
    def event(self, ev):
        if ev.type == pygame.MOUSEBUTTONDOWN:
            myabspos = ui._subpoints(ev.abs_pos, ev.pos)
            self.shown = True
            ui.add_overlay(self.scroll, myabspos)
        elif ev.type == pygame.MOUSEBUTTONUP:
            self.shown = False
            if self.scroll in ui.overlays:
                ui.overlays.remove(self.scroll)

class ConsoleScrollWrapper(ui.ScrollWrapper):
    def get_clip(self, pos):
        return pos + (self.item._size[0], self.size[1])
    
    def canceled_event(self, event):
        self.item.event(event)

class MapWidget(object):
    def __init__(self, client):
        self.client = client
        self.last_size = (0, 0)
        self.size = (0, 0)
        
        self.last_recentered_at = None
        self.start_drag = None
        self.last_drag_pos = None
        self.was_dragged = False
        
        self.last_frame_updated = 0
    
    def tick(self):
        pass
    
    def draw(self, surf, pos):
        if self.size != self.last_size:
            self.client.set_map_size(self.size)
            self.last_size = self.size
            
            #self.last_frame_updated += 1
            #if self.last_frame_updated == 3:
            #    self.last_frame_updated = 0
            
            self.client.update_map_canvas_visible()
        
        self.client.draw_map(surf, pos)
    
    def back(self):
        self.client.escape()
    
    def event(self, ev):
        if ev.type == pygame.MOUSEMOTION:
            if self.start_drag:
                if not self.was_dragged:
                    x, y = ev.pos
                    ox, oy = self.start_drag
                    dist = ((x - ox)**2 + (y - oy)**2) ** 0.5
                    if dist > 15:
                        self.was_dragged = True
                        #print 'was_dragged', dist
                if self.was_dragged:
                    self.drag(ev.pos)
                    return
            self.client.mouse_motion(ev.pos)
            return ui.LOCK_MOUSE_EVENT
        elif ev.type == pygame.MOUSEBUTTONDOWN:
            x, y = ev.pos
            if ev.button == 3:
                self.recenter_at(x, y)
            else:
                #print 'start_drag'
                self.start_drag = ev.pos
        elif ev.type == pygame.MOUSEBUTTONUP:
            if self.was_dragged:
                self.drag(ev.pos)
                self.was_dragged = False
            elif ev.button == 1:
                x, y = ev.pos
                freeciv.func.action_button_pressed(x, y, SELECT_POPUP)
            self.start_drag = None
            self.last_drag_pos = None
            return ui.LOCK_MOUSE_EVENT
        elif ev.type in (pygame.KEYDOWN, pygame.KEYUP):
            self.client.key_event(ev.type, ev.key)
    
    def recenter_at(self, x, y):
        self.last_recentered_at = freeciv.func.canvas_pos_to_nearest_tile_id(x, y)
        freeciv.func.recenter_button_pressed(x, y)
    
    def drag(self, pos):
        if not self.last_drag_pos:
            self.last_drag_pos = self.start_drag
        delta = ui._subpoints(self.last_drag_pos, pos)
        x, y = freeciv.func.get_map_view_origin()
        #print 'drag', x + delta[0], y + delta[1]
        freeciv.func.set_mapview_origin(x + delta[0], y + delta[1])
        self.last_drag_pos = pos
        

def init():
    gamemenu.init()
    citydlg.init()
    
    