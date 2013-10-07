
import traceback
import functools

import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), '../..', 'src'))

import freecivclient

get_overview_size = freecivclient.get_overview_size

functions = {}

class _obj: pass

func = _obj()
callback = _obj()
const = _obj()

def _call(name, id, *args):
    return freecivclient.call_f(id, args)

def call(name, *args):
    return freecivclient.call_f(functions[name], args)

def _callback(funname, *args):
    try:
        args = tuple(args)
        name = funname
        if hasattr(callback, name):
            ret = getattr(callback, name)(*args)
            if not isinstance(ret, (list, tuple)):
                ret = (ret, )
            return ret
        else:
            print 'no function named %s %s' % (name, args)
    except Exception as ex:
        if not isinstance(ex, (KeyboardInterrupt, SystemExit)):
            traceback.print_exc(limit=200)
        else:
            print type(ex).__name__
        print 'Abort.'
        os._exit(1)

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

server_side_funcs = {}

def server_side(func):
    server_side_funcs[func.__module__ + '.' + func.__name__] = func
    return func

def run(args=[]):
    freecivclient.run_main(["freeciv-python-client"] + args)

@register('set_const')
def _set_const(name, val):
    setattr(const, name, val)

@register('callback_test')
def _callback_test():
    pass

@register('add_function')
def _add_function(name, id):
    functions[name] = id
    setattr(func, name, functools.partial(_call, name, id))

freecivclient.set_callback(_callback)
