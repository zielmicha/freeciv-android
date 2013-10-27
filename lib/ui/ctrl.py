import features
import ui
import threading
import os
import json
import functools
import graphics

features.add_feature('ctrl.enable', type=bool, default=False)
features.add_feature('ctrl.fd', type=int, default=0)

_bound_events = {}

def maybe_init():
    if features.get('ctrl.enable'):
        print 'ctrl enabled (FD=%d)' % features.get('ctrl.fd')
        t = threading.Thread(target=loop)
        t.daemon = True
        t.start()

def loop():
    input = os.fdopen(features.get('ctrl.fd'), 'r', 1)
    for line in iter(input.readline, ''):
        message = json.loads(line)
        ui.execute_later(functools.partial(process_message, message))

EVENT_NAMES = [
    'MOUSEBUTTONUP', 'MOUSEBUTTONDOWN',
    'MOUSEMOTION', 'TEXTEDITING', 'TEXTINPUT',
    'QUIT', 'KEYDOWN', 'KEYUP',
]

def process_message(message):
    type = message['type']
    if type in EVENT_NAMES:
        process_event(message)
    elif type in _bound_events:
        _bound_events[type](message)
    else:
        print 'unsupported ctrl message', type

def process_event(message):
    supported_keys = ['type', 'pos', 'key', 'unicode', 'text', 'start', 'length',
                          'button']

    dict = {}
    for k in message:
        if k in supported_keys:
            if k != 'type':
                dict[str(k)] = message[k]
        else:
            raise Exception('message denied (key %r)' % k)

    type = getattr(graphics.const, message['type'])
    ui.syntetic_events.append(graphics.Event(type, **dict))

def bind_event(name, func):
    _bound_events[name] = func
