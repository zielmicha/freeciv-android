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
        self.add(ui.Label(', '.join(self.client.get_current_tech())))
        tech_panel = ui.HorizontalLayoutWidget()
        tech_panel.add(ui.Button('Change tech goal', self.research_goal_dialog))
        self.add(tech_panel)
        self.add(ui.Label('Players'))
        self.add(ui.Button('Player list', self.player_list))
    
    def research_goal_dialog(self):
        def set_goal(tech):
            tech.set_as_goal()
            self.setup_ui()
            ui.back()
        
        techs = ui.LinearLayoutWidget()
        
        techs.add(ui.Label(', '.join(self.client.get_current_tech())))
        for tech in self.client.get_techs():
            techs.add(ui.Button(tech.name, functools.partial(set_goal, tech)))
        
        ui.set_dialog(techs, scroll=True)
    
    def player_list(self):
        players = ui.LinearLayoutWidget()
        
        for player in self.client.get_players():
            players.add(ui.Label(player.get_name()))
        
        ui.set_dialog(players, scroll=True)