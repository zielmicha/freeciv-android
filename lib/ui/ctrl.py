import features
import ui
import threading
import os
import json
import functools
import graphics
import threading

features.add_feature('ctrl.enable', type=bool, default=False)
features.add_feature('ctrl.fd', type=int, default=0)

_bound_events = {}
_message_available = threading.Condition()
_messages = []

def maybe_init():
    if features.get('ctrl.enable'):
        print 'ctrl enabled (FD=%d)' % features.get('ctrl.fd')
        t = threading.Thread(target=loop)
        t.daemon = True
        t.start()
        ui.idle_hooks.add(idle_sleep)

def idle_sleep(dt):
    with _message_available:
        if dt > 0:
            _message_available.wait(dt)
        for message in _messages:
            process_message(message)
        _messages[:] = []

def loop():
    input = os.fdopen(features.get('ctrl.fd'), 'r', 1)
    for line in iter(input.readline, ''):
        message = json.loads(line)
        with _message_available:
            _messages.append(message)
            _message_available.notify()

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
