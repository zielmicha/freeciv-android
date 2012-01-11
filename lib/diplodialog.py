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

import client.diplomacy

import ui

class Meeting(client.diplomacy.Meeting):
    def init(self):
        self.dialog = None
    
    def create_clause(self, giver, type, value):
        self.open_dialog()
        self.dialog.add_clause(giver, type, value)
        print 'create_clause', giver, type, value
    
    def remove_clause(self, giver, type, value):
        print 'remove_clause', giver, type, value
    
    def accept_treaty(self, me, other):
        print 'accept_tready', me, other
        self.open_dialog()
        self.dialog.set_accept_treaty(me, other)
    
    def open_dialog(self):
        if not self.dialog:
            self.dialog = MeetingDialog(self)
            ui.set_dialog(self.dialog, scroll=True)

class MeetingDialog(ui.LinearLayoutWidget):
    def __init__(self, meeting):
        super(MeetingDialog, self).__init__()
        self.meeting = meeting
        
        self.left = ConditionsWidget()
        self.right = ConditionsWidget()
        
        self.top = ui.HorizontalLayoutWidget()
        self.top.add(ui.Label('Meeting with %d' % meeting.counterpart))
        self.add(self.top)
        
        self.middle = ui.HorizontalLayoutWidget(spacing=10)
        w = 200
        self.middle.add(ui.Bordered(self.left, force_width=w))
        self.middle.add(ui.Bordered(self.right, force_width=w))
        self.add(self.middle)
        
        self.add(ui.Button('Add condition', self.add_condition))
        
        self.bottom = ui.HorizontalLayoutWidget(spacing=10)
        self.bottom.add(ui.Button('Cancel treaty', self.cancel_treaty))
        self.bottom.add(ui.Button('Accept treaty', self.accept_treaty))
        self.add(self.bottom)
    
    def cancel_treaty(self):
        self.meeting.cancel()
    
    def accept_treaty(self):
        self.meeting.accept()

    def add_condition(self):
        ui.not_implemented()
    
    def add_clause(self, giver, type, value):
        if giver == self.meeting.counterpart:
            panel = self.right
        else:
            panel = self.left
        
        panel.add_condition(type, value, self.meeting.get_clause_repr(type, value))
    
    def set_accept_treaty(self, me, other):
        self.left.set_accept(me)
        self.right.set_accept(other)

class ConditionsWidget(ui.LinearLayoutWidget):
    def __init__(self):
        super(ConditionsWidget, self).__init__()
        self.accepting = ui.Label('-')
        self.add(self.accepting)
        self.panel = ui.LinearLayoutWidget()
        self.add(self.panel)
    
    def add_condition(self, type, value, string):
        self.panel.add(ui.Label(string))
    
    def set_accept(self, b):
        if b:
            self.accepting.set_text('Accepts')
        else:
            self.accepting.set_text('Declines')

if __name__ == '__main__':
    d = MeetingDialog()
    ui.set_dialog(d)
    ui.main()