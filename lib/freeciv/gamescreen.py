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
from __future__ import division

import ui
import uidialog
import client
import functools

from client import freeciv

import graphics
import citydlg
import gamemenu
import icons
import features
import diplodialog
import empiredlg
import help
import dropbox
import mapdrawer

SELECT_POPUP = 0

features.add_feature('app.full_label_toggle_button', type=bool)
features.add_feature('app.map_tiles', type=bool, default=False)

class ScreenClient(client.Client):
    def __init__(self, **kwargs):
        client.Client.__init__(self, **kwargs)
        self.turn_loading_dialog = None
        self.init_ui()

    def init_ui(self):
        self.ui = ScreenWidget(self)

    #def console_line(self, line):
    #    self.ui.console.line(line)

    def end_turn(self):
        self.update_meswin([('Ending turn...', None, None)])
        super(ScreenClient, self).end_turn()

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
        self.ui.menu.update(unit)

    def disable_menus(self):
        self.ui.menu.update(None)

    def popup_caravan_dialog(self, unit, home, dest):
        can_establish, can_trade, can_wonder = self.get_caravan_options(unit, home, dest)
        def establish_trade_route():
            unit.perform_activity(client.actions.ACTIVITY_ESTABLISH_TRADE_ROUTE)

        def help_wonder():
            unit.perform_activity(client.actions.ACTIVITY_HELP_BUILD_WONDER)

        items = []

        if not can_establish and not can_wonder:
            return

        if can_establish:
            items.append(('Establish trade route', establish_trade_route))

        if can_wonder:
            items.append(('Help building wonder', help_wonder))

        items.append(('Do nothing', lambda: None))

        ui.show_list_dialog(items, title='Your %s from %s has arrived to city %s'
                            % (unit.get_name(), home.get_name(), dest.get_name()),
                            titlefont=ui.consolefont)

    def popup_diplomat_dialog(self, diplomat_action):
        if diplomat_action.city:
            self.popup_city_diplomat_dialog(diplomat_action)
        else:
            self.popup_unit_diplomat_dialog(diplomat_action)
        # SPY_SABOTAGE_UNIT: "",
        # DIPLOMAT_BRIBE: "",
        # DIPLOMAT_INCITE: "",

    def popup_city_diplomat_dialog(self, diplomat_action):
        if diplomat_action.spy:
            message = 'Choose Your spy\'s strategy'
        else:
            message = 'Choose Your diplomat\'s strategy'

        action_titles = {
            freeciv.const.DIPLOMAT_MOVE: "Keep moving",
            freeciv.const.DIPLOMAT_EMBASSY: "Establish Embassy",
            freeciv.const.DIPLOMAT_INVESTIGATE: "Investigate City",
            freeciv.const.DIPLOMAT_SABOTAGE: "Sabotage City",
            freeciv.const.DIPLOMAT_INCITE: "Incite Revolt",
            freeciv.const.DIPLOMAT_STEAL: "Steal Technology",
            freeciv.const.SPY_POISON: "Poison City",
        }

        simple_actions = [freeciv.const.DIPLOMAT_EMBASSY,
                          freeciv.const.DIPLOMAT_INVESTIGATE,
                          freeciv.const.DIPLOMAT_SABOTAGE,
                          freeciv.const.DIPLOMAT_MOVE,
                          freeciv.const.SPY_POISON]

        def do_action(action):
            if action in simple_actions:
                diplomat_action.perform_simple_action(action)
            elif action == freeciv.const.DIPLOMAT_SABOTAGE:
                # TODO: spy can choose building
                diplomat_action.perform_simple_action(action,
                                                      value=freeciv.const.B_LAST+1)
            elif action == freeciv.const.DIPLOMAT_STEAL:
                # TODO: spy can choose technology
                diplomat_action.perform_simple_action(action, value=freeciv.const.A_UNSET)
            elif action == freeciv.const.DIPLOMAT_INCITE:
                diplomat_action.request_answer(action)
            else:
                ui.not_implemented()

        items = []
        for action in diplomat_action.get_actions():
            if action in action_titles:
                title = action_titles[action]
                items.append((title, functools.partial(do_action, action)))

        ui.show_list_dialog(items, title=message, titlefont=ui.consolefont)

    def popup_incite_dialog(self, diplomat_action, cost, possible):
        if not possible:
            ui.message('Revolt not possible')
            return
        if cost > self.get_gold():
            ui.message('You don\'t have enough money (needed %d)' % cost)
            return

        def yes():
            diplomat_action.perform_simple_action(freeciv.const.DIPLOMAT_INCITE)

        ui.ask('Incite revolt? (costs %d)' % cost, yes)

    def popup_unit_diplomat_dialog(self, diplomat_action):
        message = 'Subvert enemy unit'

    def popup_unit_select_dialog(self, units):
        def focus(unit):
            unit.focus()
            ui.back()

        panel = ui.LinearLayoutWidget()
        for unit in units:
            name = unit.get_name()
            callback = functools.partial(focus, unit)
            p = ui.HorizontalLayoutWidget()
            p.add(ui.Image(unit.get_image(), callback)) # Label(' ' * 10, callback, image=
            p.add(ui.Button(name, callback))
            panel.add(p)
        ui.set_dialog(panel, scroll=True)

    def quit(self):
        def quit():
            self.disconnect()
            ui.back(anim=False) # close dialog
            ui.back(allow_override=False) # close game

        def save():
            self.chat('/save')
            ui.back()

        def save_db():
            ui.back()
            self.save_and_get_name(lambda path: dropbox.save(path))

        def show_help():
            help.show()

        menu = ui.Menu(for_dialog=True)
        menu.add('Quit', quit)
        menu.add('Save', save)
        menu.add('Save to Dropbox', save_db, button_class=dropbox.DBButton)
        menu.add('Help', show_help)
        ui.set_dialog(menu, scroll=True)

    def city_dialog_is_open(self, city):
        return bool(self.get_city_dialog(city))

    def refresh_city_dialog(self, city):
        if self.city_dialog_is_open(city):
            self.get_city_dialog(city).refresh()

    def get_city_dialog(self, city):
        if isinstance(ui.get_screen(), ui.ScrollWrapper):
            item = ui.get_screen().item
        else:
            item = ui.get_screen()
        if isinstance(item, citydlg.Dialog) and item.city == city:
            return item
        else:
            return None

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

    def popup_notify(self, text):
        panel = ui.LinearLayoutWidget()
        panel.add(ui.Label(text, font=ui.consolefont))
        panel.add(ui.Button('Okay', ui.back))
        ui.set_dialog(panel)

class ScreenWidget(ui.AbsoluteLayoutWidget):
    def __init__(self, client):
        super(ScreenWidget, self).__init__()
        width = 150

        def make_button(name, func):
            return ui.Button(name, func,
                             force_width=width - 15,
                             padding=1)

        self.client = client

        if features.get('app.map_tiles'):
            import maptiles
            self.map = maptiles.MapWidget(client)
        else:
            self.map = mapdrawer.MapWidget(client)
        self.overview = OverviewWidget(client)
        self.console = ConsoleWidget(client)
        self.menu = gamemenu.Menu(client)
        self.end_turn_button = make_button('End turn', self.client.end_turn)
        self.empire_button = make_button('Empire', self.empire_dialog)
        self.taxes_panel = TaxesPanel(client)

        self.left_panel = ui.LinearLayoutWidget(spacing=0, center=True, marginleft=0)
        self.left_panel.background = (190, 160, 110, 170)

        self.add(self.map, (0, 0))
        self.add(self.menu, (0, 0), align=ui.BOTTOM)
        self.add(self.left_panel, (0, 0), align=ui.LEFT)
        self.update_layout()

        self.left_panel.add(self.overview)
        self.left_panel.add(self.console.scroll)
        self.left_panel.add(self.end_turn_button)
        self.left_panel.add(self.taxes_panel)
        self.left_panel.add(ui.Spacing(0, 10))
        self.left_panel.add(self.empire_button)
        self.left_panel.add(self.menu.left_widget)

        if features.get('app.full_label_toggle_button'):
            full_label_toggle_button = ui.Button('city labels', client.toggle_full_labels, font=ui.consolefont)
            self.left_panel.add(full_label_toggle_button)

        # key_end_turn()

        self.focus = self.map

    def resize_left_pane(self, width):
        self.console.width = width
        self.console.scroll.width = width
        self.console.scroll.height = 100

    def empire_dialog(self):
        empiredlg.EmpireDialog(self.client).show()

    def tick(self):
        self.map.size = ui.screen_width, ui.screen_height
        self.client.tick()
        super(ScreenWidget, self).tick()

    def event(self, ev):
        if ev.type == graphics.const.KEYDOWN and ev.key == graphics.const.K_F1:
            self.client.quit()
        else:
            return super(ScreenWidget, self).event(ev)

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
            for i in xrange(int(value/10)):
                panel.add(ui.Image(img))

        add(tax, tax_img)
        add(lux, lux_img)
        add(science, science_img)

        self.add(panel)

    def update_year(self):
        year = self.client.get_current_year_name()
        self.add(ui.Label('Year: ' + year, font=ui.consolefont))

    def event(self, ev):
        if ev.type == graphics.const.MOUSEBUTTONDOWN:
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
            ui.get_screen().tick()
            self.update()
            ui.execute_later(self.update)

        def add(type, img):
            # spacing here are hard-coded so the layout breaks when font is changed
            img = img.scale((30, 45))
            line = ui.HorizontalLayoutWidget()
            img_l = ui.LinearLayoutWidget()
            img_l.add(ui.Image(img))
            img_l.add(ui.Spacing(0, 6))
            line.add(img_l)
            if type != 0:
                line.add(ui.Spacing(10, 0))
                w = 40
                line.add(ui.Button(' - ', functools.partial(change, type, -1), font=font,
                                   force_width=w))
                line.add(ui.Spacing(10, 0))
                line.add(ui.Button(' + ', functools.partial(change, type, +1), font=font,
                                   force_width=w))
            else:
                line.add(ui.Spacing(116, 0))
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

class OverviewWidget(ui.Widget):
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
        if ev.type == graphics.const.MOUSEBUTTONDOWN:
            w, h = self.client.get_overview_size()
            scale = float(w) / self.scale_width
            self.client.overview_click(int(ev.pos[0] * scale), int(ev.pos[1] * scale))

    def draw(self, surf, pos):
        self.client.draw_overview(surf, pos, scale=self.size)
        surf.draw_rect((255,255,255), pos + self.size, 1)

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
            surf.draw_rect((255, 255, 255, 170), pos + self._size, 0, blend=graphics.MODE_NONE)
        super(ConsoleWidget, self).draw(surf, pos)

    def draw_clipped(self, surf, pos, clip):
        rect = graphics.Rect(clip)
        cliptex = graphics.create_surface(rect[2], rect[3])
        relpos = ui.layout._subpoints(pos, (rect[0], rect[1]))

        self.draw(cliptex, relpos)

        surf.blit(cliptex, (rect[0], rect[1]))

    def event(self, ev):
        if ev.type == graphics.const.MOUSEBUTTONDOWN:
            myabspos = ui.layout._subpoints(ev.abs_pos, ev.pos)
            self.shown = True
            ui.add_overlay(self.scroll, myabspos)
        elif ev.type == graphics.const.MOUSEBUTTONUP:
            self.shown = False
            if self.scroll in ui.overlays:
                ui.overlays.remove(self.scroll)

class ConsoleScrollWrapper(ui.ScrollWrapper):
    def get_clip(self):
        return (self.item._size[0], self.size[1])

    def canceled_event(self, event):
        self.item.event(event)

def init():
    gamemenu.init()
    citydlg.init()
