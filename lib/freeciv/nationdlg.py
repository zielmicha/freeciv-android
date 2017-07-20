# coding=utf-8
# Copyright (C) 2017 Pierre Renié
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
import functools
import client

class NationDialog(ui.LinearLayoutWidget):
    def __init__(self, callback):
        super(NationDialog, self).__init__()
        self.callback = callback
        self.setup_ui()

    def setup_ui(self):
        self.add(ui.Label('Select a nation'))

        nationSet_panel = ui.HorizontalLayoutWidget(spacing=10)
        self.nationSet_label = ui.Label('')
        nationSet_panel.add(self.nationSet_label)
        self.nationSet_button = ui.Button('', self.change_nationSet)
        nationSet_panel.add(self.nationSet_button)
        self.set_nationSet(False)
        self.add(nationSet_panel)

        self.add(ui.Label('Nation Groups:'))

        nations_panel = ui.HorizontalLayoutWidget(spacing=10)
        self.nationGroups = ui.LinearLayoutWidget()
        nations_panel.add(ui.ScrollWrapper(self.nationGroups,
                                height=ui.screen_height*0.7,
                                width=ui.screen_width*0.7,ways=ui.SCROLL_HEIGHT|ui.SCROLL_WIDTH))
        self.nations = ui.LinearLayoutWidget()
        nations_panel.add(ui.ScrollWrapper(self.nations,
                                height=ui.screen_height*0.7,
                                width=ui.screen_width*0.7,ways=ui.SCROLL_HEIGHT|ui.SCROLL_WIDTH))
        self.set_nation_group()
        for id, name in enumerate(client.get_nations_groups()):
            self.nationGroups.add(ui.Button(name, functools.partial(self.set_nation_group, id)))
        self.add(nations_panel)

        self.update_layout()

    def set_nationSet(self, isExtended):
        self.nationSet_is_extended = isExtended
        if (isExtended):
            self.nationSet_label.set_text('Nation Set: Extended')
            self.nationSet_button.set_text('Show Core nations only')
        else:
            self.nationSet_label.set_text('Nation Set: Core')
            self.nationSet_button.set_text('Show all nations')

    def change_nationSet(self):
        self.set_nationSet(not self.nationSet_is_extended)

    def set_nation_group(self, group_id=-1):
        self.nations.clear()
        for name, style, id in client.get_nations(group_id):
            self.nations.add(ui.Button(name, functools.partial(self.callback, style, id)))

    def research_goal_dialog():
        print ''

    def research_current_dialog():
        print ''

    def technology_tree_dialog():
        print ''

    def show(self):
        ui.set(self)

