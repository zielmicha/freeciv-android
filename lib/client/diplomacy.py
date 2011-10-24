import freeciv

import client

(CLAUSE_ADVANCE, CLAUSE_GOLD, CLAUSE_MAP,
CLAUSE_SEAMAP, CLAUSE_CITY, 
CLAUSE_CEASEFIRE, CLAUSE_PEACE, CLAUSE_ALLIANCE,
CLAUSE_VISION, CLAUSE_EMBASSY, CLAUSE_LAST) = range(11)

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
        self.counterpart = counterpart
        self.client = client
    
    def create_clause(self, giver, type, value):
        pass
    
    def remove_clause(self, giver, type, value):
        pass
    
    def accept_treaty(self, me, other):
        pass
    
    def get_clause_repr(self, type, value):
        return '%s (%d)' % (names[type], value)
    
    def accept(self):
        freeciv.func.py_accept_treaty(self.counterpart)
    
    def cancel(self):
        freeciv.func.py_cancel_treaty(self.counterpart)
    
    def init(self):
        pass

def get_meeting(counterpart):
    c = client.client
    if counterpart not in c.meetings:
        c.meetings[counterpart] = c.create_meeting(counterpart)
    return c.meetings[counterpart]