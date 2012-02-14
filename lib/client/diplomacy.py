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

import freeciv

import client

(CLAUSE_ADVANCE, CLAUSE_GOLD, CLAUSE_MAP,
CLAUSE_SEAMAP, CLAUSE_CITY, 
CLAUSE_CEASEFIRE, CLAUSE_PEACE, CLAUSE_ALLIANCE,
CLAUSE_VISION, CLAUSE_EMBASSY, CLAUSE_LAST) = range(11)

for i in 'DS_WAR DS_ARMISTICE DS_CEASEFIRE DS_ALLIANCE DS_PEACE'.split():
    globals()[i] = getattr(freeciv.const, i)
    
names = 'Advance', 'Gold', 'Map', 'Seamap', 'City', 'Ceasefire', 'Peace', 'Alliance', \
        'Shared vision', 'Embassy', '<nothing>'

@freeciv.register
def handle_diplomacy_init_meeting(counterpart, initiated_from):
    get_meeting(counterpart).init()

@freeciv.register
def handle_diplomacy_cancel_meeting(counterpart, initiated_from):
    pass

@freeciv.register
def handle_diplomacy_create_clause(counterpart, giver, type, value):
    get_meeting(counterpart).create_clause(giver, type, value)

@freeciv.register
def handle_diplomacy_remove_clause(counterpart, giver, type, value):
    get_meeting(counterpart).remove_clause(giver, type, value)

@freeciv.register
def handle_diplomacy_accept_treaty(counterpart, I_accepted, other_accepted):
    get_meeting(counterpart).accept_treaty(I_accepted, other_accepted)

class Meeting(object):
    def __init__(self, client, counterpart):
        self._counterpart = counterpart
        self.client = client
        self.counterpart = client.get_player_with_id(counterpart)
    
    def create_clause(self, giver, type, value):
        pass
    
    def remove_clause(self, giver, type, value):
        pass
    
    def accept_treaty(self, me, other):
        pass
    
    def get_clause_repr(self, type, value):
        return '%s (%d)' % (names[type], value)
    
    def accept(self):
        freeciv.func.py_accept_treaty(self._counterpart)
    
    def cancel(self):
        freeciv.func.py_cancel_treaty(self._counterpart)
    
    def add_clause(self, me, type, value):
        freeciv.func.py_add_clause(self._counterpart,
                                   freeciv.func.player_number(freeciv.func.get_playing()) if me else self._counterpart,
                                   type, value)
    
    def pact(self, type):
        assert type in (CLAUSE_CEASEFIRE, CLAUSE_PEACE, CLAUSE_ALLIANCE, CLAUSE_VISION)
        self.add_clause(False, type, 0)
    
    def init(self):
        pass

def get_meeting(counterpart):
    c = client.client
    if counterpart not in c.meetings:
        c.meetings[counterpart] = c.create_meeting(counterpart)
    return c.meetings[counterpart]

class Player(object):
    def __init__(self, handle):
        assert handle, [ freeciv.func.player_by_number(i) for i in xrange(150) ]
        self.handle = handle
    
    def get_name(self):
        return freeciv.func.player_name(self.handle)
    
    def get_nation_adj(self):
        return freeciv.func.nation_adjective_for_player(self.handle)
    
    def get_nation_pl(self):
        return freeciv.func.nation_plural_for_player(self.handle)
    
    def get_flag(self):
        return freeciv.func.py_get_nation_flag(self.handle)
    
    def can_meet(self):
        return freeciv.func.can_meet_with_player(self.handle)
    
    def meet(self):
        freeciv.func.py_init_meeting(freeciv.func.player_number(self.handle))
    
    def get_state(self):
        return freeciv.func.py_get_dipl_state(self.handle)
    
    def gives_shared_vision(self):
        return freeciv.func.py_gives_shared_vision(self.handle)
    
    def cancel_pact(self, type):
        return freeciv.func.py_cancel_pact(self.handle, type)
    
    def __repr__(self):
        return '<Player handle=%d name=%s>' % (self.handle, self.get_name())

def get_players():
    return map(Player, freeciv.func.get_players())