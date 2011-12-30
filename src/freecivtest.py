import freecivclient
import glob

def callback(funname, *args):
    args = tuple(args)
    print '<%s %r>' % (funname, args)
    g = globals()
    name = 'fun_' + funname
    if name in g:
        fun = g[name]
        ret = fun(*args)
        return ret
    else:
        print 'no function named', name

def fun_callback_test():
    pass

def fun_get_gui_specific_themes_directories():
    return ['../data']

def fun_get_useable_themes_in_directory(path):
    return glob.glob(path + '/*.theme')

def fun_add_function(name, i):
    print '<register', name, 'as', i, '>'
    functions[name] = i
    return 6

def fun_ui_init():
    pass

def fun_popdown_help_dialog():
    ' Destory help dialog '
    pass

def call(name, *args):
    freecivclient.call(functions[name], args)

functions = {}

freecivclient.set_callback(callback)
freecivclient.run_main(["freeciv-python-client"])