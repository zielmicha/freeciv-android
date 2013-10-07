import json

class Socket:
    def __init__(self, f, handler):
        self.f = f
        self.handler = handler
        self.disabled = False

    def load(self):
        return json.JSONDecoder(object_hook=from_json).decode(self.f.readline())

    def dump(self, obj):
        self.f.write(Encoder().encode(obj) + '\n')

    def call(self, name, *args, **kwargs):
        return call(self, name, *args, **kwargs)

ext_objects = {}

class Encoder(json.JSONEncoder):
    def default(self, o):
        if isinstance(o, Wrapper):
            return {'__ext_object__': o.id}
        else:
            assert o.__class__.__name__ in ('Surface', 'CroppedSurface')
            ext_objects[id(o)] = o
            return {'__ext_object__': id(o)}

    def encode(self, obj):
        def hint_tuples(item):
            if isinstance(item, tuple):
                return {'__tuple__': True, 'items': [ hint_tuples(e) for e in item ]}
            elif isinstance(item, list):
                return [ hint_tuples(e) for e in item ]
            elif isinstance(item, dict):
                return { hint_tuples(k):hint_tuples(v) for k, v in item.items() }
            elif isinstance(item, str):
                try:
                    return item.decode('ascii')
                except UnicodeError:
                    return {'__utf8__': item.decode('utf8')}
            else:
                return item

        return super(Encoder, self).encode(hint_tuples(obj))

class Wrapper(object):
    def __init__(self, id):
        self.id = id

def from_json(obj):
    if '__ext_object__' in obj:
        ident = obj['__ext_object__']
        if ident in ext_objects:
            return ext_objects[ident]
        else:
            return Wrapper(ident)
    elif '__utf8__' in obj:
        return obj['__utf8__'].encode('utf8')
    elif '__tuple__' in obj:
        return tuple(obj['items'])
    else:
        return obj

def call(sock, name, *args, **kwargs):
    if sock.disabled:
        raise RuntimeError('attempted to call back in no-ack mode  (info: %s)' % sock.disabled)
    ack = True
    if '_noack' in kwargs:
        ack = not kwargs['_noack']
        del kwargs['_noack']
    sock.dump({'call': name, 'args': args, 'kwargs': kwargs, 'ack': ack})
    if ack:
        print 'wait for', name
        res = loop(sock)
        return res

def loop(sock):
    while True:
        func = sock.load()
        if 'return' in func:
            return func['return']
        else:
            if not func['ack']:
                sock.disabled = repr(func)
            result = sock.handler(func['call'], *func['args'], **func['kwargs'])
            if func['ack']:
                sock.dump({'return': result})
            else:
                sock.disabled = False
