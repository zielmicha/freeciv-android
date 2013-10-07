import simplerpc
import socket

def handler(name, args, kwargs):
    try:
        func = getattr(callback, name)
    except AttributeError:
        print 'Missing callback', name
    else:
        result = func(*args, **kwargs)
        return result

conn = socket.socket()
conn.connect(('localhost', 9999))
sock = simplerpc.Socket(conn.makefile('r+', 0), handler)

class _callback: pass

callback = _callback()

def _call(name, *args, **kwargs):
    return sock.call(name, *args, **kwargs)

class _func:
    def __getattr__(self, name):
        return lambda *args, **kwargs: _call(name, *args, **kwargs)

func = _func()

class _const:
    def __getattr__(self, k):
        for k, v in sock.call('get_const').items():
            setattr(self, k, v)

const = _const()

def get_overview_size():
    return sock.call('get_overview_size')

def run():
    return sock.call('run')

def register(name_or_func):
    if isinstance(name_or_func, str):
        def decorator(method):
            setattr(callback, name_or_func, method)
            return method
        return decorator
    elif callable(name_or_func):
        setattr(callback, name_or_func.__name__, name_or_func)
        return name_or_func
    else:
        raise TypeError('%r should be str or callable' % name_or_func)

def server_side(func, async=False):
    ident = func.__module__ + '.' + func.__name__
    return lambda *args, **kwargs: _call('server_side', ident, *args,
                                         **dict(kwargs, _noack=async))

def server_side_async(func):
    return server_side(func, async=True)
