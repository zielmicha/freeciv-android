import sys, os

sys.path.append(os.path.join(os.path.dirname(__file__), '../src'))

import freecivclient
import glob

def callback(funname, *args):
    if funname == 'add_function':
        name, i = args
        functions[name] = i
        return
    if funname == 'set_const':
        return
    return (5,)

def call(name, *args):
    freecivclient.call_f(functions[name], args)

functions = {}

freecivclient.set_callback(callback)

while True:
    call('call_callback', 5) 