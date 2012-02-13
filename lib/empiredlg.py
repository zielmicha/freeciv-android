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
import functools

class EmpireDialog(ui.LinearLayoutWidget):
    def __init__(self, client):
        super(EmpireDialog, self).__init__()
        self.client = client
        
        self.setup_ui()
    
    def show(self):
        ui.set(ui.ScrollWrapper(self))
    
    def setup_ui(self):
        self.items = []
        self.tech_label = ui.Label('')
        self.add(self.tech_label)
        tech_panel = ui.HorizontalLayoutWidget(spacing=10)
        tech_panel.add(ui.Button('Change tech goal', self.research_goal_dialog))
        tech_panel.add(ui.Button('Change current tech', self.research_current_dialog))
        self.add(tech_panel)
        self.add(ui.Label('Players'))
        self.add(ui.Button('Player list', self.player_list))
        self.update_layout()
    
    def update_tech_label(self):
        self.tech_label.set_text(', '.join(self.client.get_current_tech()))
    
    def tick(self):
        super(EmpireDialog, self).tick()
        self.client.tick() # important
        self.update_tech_label()
    
    def research_goal_dialog(self):
        self.research_list_dialog('set_as_goal', 11)
    
    def research_current_dialog(self):
        self.research_list_dialog('set_as_current', 2)
    
    def research_list_dialog(self, func, level):
        def set_goal(tech):
            getattr(tech, func)()
            self.setup_ui()
            ui.back()
        
        techs = ui.LinearLayoutWidget()
        
        techs.add(ui.Label(', '.join(self.client.get_current_tech())))
        for tech in self.client.get_techs(level):
            techs.add(ui.Button(tech.name, functools.partial(set_goal, tech)))
        
        ui.set_dialog(techs, scroll=True)
    
    def player_list(self):
        def meet(player):
            ui.back()
            ui.back()
            player.meet()
        
        players = ui.LinearLayoutWidget()
        
        for player in self.client.get_players():
            p = ui.HorizontalLayoutWidget()
            if player.can_meet():
                p.add(ui.Button('Meet', functools.partial(meet, player)))
            p.add(ui.Label('%s (%s)' % (player.get_name(), player.get_nation_adj())))
            players.add(p)
        
        ui.set_dialog(players, scroll=True)

