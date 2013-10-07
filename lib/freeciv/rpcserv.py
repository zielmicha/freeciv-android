import simplerpc
import socket
import os
import traceback

import freeciv.main
import freeciv.client
from freeciv.client import clientnative

class _callback(object):
    def __getattribute__(self, name):
        return lambda *args, **kwargs: call_remote(name, args, kwargs)

def call_remote(name, args, kwargs):
    print 'remote', name, args, kwargs
    res = sock.call(name, args, kwargs)
    print 'remote', name, '->', res
    return res

clientnative.callback = _callback()

def handle(name, *args, **kwargs):
    if name == 'get_const':
        return clientnative.const.__dict__
    elif name == 'run':
        return clientnative.run()
    elif name == 'server_side':
        ident = args[0]
        args = args[1:]
        return clientnative.server_side_funcs[ident](*args, **kwargs)
    elif name == 'get_overview_size':
        return clientnative.get_overview_size()
    else:
        print 'call to', name
        return getattr(clientnative.func, name)(*args, **kwargs)

sock = socket.socket()
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(('localhost', 9999))
sock.listen(1)

conn, addr = sock.accept()
sock = simplerpc.Socket(conn.makefile('r+', 0), handle)
try:
    simplerpc.loop(sock)
except:
    traceback.print_exc()
finally:
    os._exit(1)
