import simplerpc
import socket
import os
import traceback

import freeciv.main
import freeciv.client
from freeciv.client import clientnative

NO_ACK = ['canvas_copy', 'canvas_put_line', 'canvas_put_sprite_full',
          'canvas_put_rectangle', 'canvas_put_sprite',

          'real_output_window_append', 'dirty_all', 'dirty_rect',
          'update_overview_scroll_window_pos']

class _callback(object):
    def __getattribute__(self, name):
        return lambda *args, **kwargs: call_remote(name, args, kwargs)

def call_remote(name, args, kwargs):
    res = sock.call(name, args, kwargs, _noack=name in NO_ACK)
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
