import os
os.chdir(os.path.dirname(__file__) or '.')

structs = 'sprite,canvas'.split(',')
structs = [ 'struct ' + s for s in structs ] + ['PyObject']

types = {
    'int': 'i',
    'char*': 's',
    'double': 'd',
}

mappers = 'city player tile packet_game_load text_tag_list unit_list color packet_endgame_report message'.split()
int_mappers = 'unit tile city player'.split()
int_mappers = [ 'struct ' + s for s in int_mappers]

def proc(type, name):
    type = type.strip()
    while name.startswith('*'):
        type += '*'
        name = name[1:]
    if type.startswith('const '):
        type = type[len('const '):]
    if type in structs:
        raise ValueError('Not supported')
        return 'O', name + '.py_object'
    if type.endswith('*') and type[:-1] in structs:
        return 'O', 'py_get_pyobject(%s)' % name
    if type.startswith('enum'):
        return 'i', '(int)' + name
    if type.startswith('struct '):
        type = type[len('struct '):]
        if type.endswith('*') and type[:-1] in mappers:
            return 'O', 'py_mapper_%s(%s)' % (type[:-1], name)
        elif type.endswith('*') and type[:-1] in mappers:
            return 'i', '(int)%s' % name
        elif type in mappers:
            return 'O', 'py_mapper_%s(&%s)' % (type, name)
        else:
            raise ValueError('Bad type %s' % type)
    if type == 'bool':
        return 'i', '(int)' + name
    return types[type], name

def _proc_ret(type, name):
    type = type.strip()
    name = name.strip()
    while name.startswith('*'):
        type += '*'
        name = name[1:]
    if type.startswith('const '):
        type = type[len('const '):]
    if type.endswith('*') and type[:-1] in int_mappers:
        return 'int', 'i', '', 'arg_%s' % name, '(%s)arg_%s' % (type, name), name
    if type.endswith('*') and type[:-1] in structs:
        return 'PyObject*', 'O', '''
\t%s argp_%s = py_alloc_struct(arg_%s);
        ''' % (type, name, name), 'arg_%s' % name, 'argp_%s' % name, name
    if type in structs:
        raise ValueError('error')
#        return 'PyObject*', 'O', '''
#\t%s argp_%s;
#\targp_%s.py_object = arg_%s;
#        ''' % (type, name, name, name), 'arg_%s' % name
    if type.startswith('enum '):
        return 'int', 'i', '', 'arg_%s' % name, '(%s)arg_%s' % (type, name), name
    if type == 'bool':
        return 'int', 'i', '', 'arg_%s' % name, '(bool)arg_%s' % name, name
    return type, types[type], '', 'arg_%s' % name, 'arg_%s' % name, name

def proc_ret(*a):
    v = _proc_ret(*a)
    assert len(v) == 6, v
    return v

def p2(x):
    if len(x) == 1:
        print '// bad length', x
    return x

fails = []

import traceback

nign = 0
nproc = 0

was_printed = set()
ignored = []

import sys
sys.stdout = open("src/callauto.c", 'w')
print '#include "pyclient.h"'
names = []
for line in open('callglue').readlines():
    if line.startswith('#') or not line.strip():
        continue
    line = line.strip()
    print '// %s' % line.strip()
    android = False
    
    if line.startswith('__android '):
        android = True
        line = line[len('__android '):].strip()
    
    start, rest = line.split('(', 1)
    rettype, fname = start.rsplit(None, 1)
    
    while fname.startswith('*'):
        rettype += '*'
        fname = fname[1:]
    
    was_printed.add(fname)
    
    nproc += 1
    
    if android:
        print '#ifdef ANDROID'
    
    try:
        rest, _ = rest.split(')', 1)
        if rest.strip() in ('void', ''):
            args = []
        else:
            args = [ p2(a.rsplit(None, 1)) for a in rest.split(',') ]
        
        format = [ proc_ret(type, name) for type, name in args ]
        
        print line.strip() + ';'
        print
        tmplcode = ''
        valscode = []
        names.append((fname, android))
        print 'static PyObject* python_%s(PyObject* self, PyObject* args) {' % fname
        for (type, cformat, mod, val, retval, name) in format:
            print '\t%s arg_%s;' % (type, name)
            valscode.append('&' + val)
            tmplcode += cformat
        joined = ', '.join(valscode)
        if joined:
            joined = ', ' + joined
        print '\tif(PyArg_ParseTuple(args, "%s"%s) == 0) return NULL;' % (tmplcode, joined)
        
        call_args = []
        for (type, cformat, mod, val, retval, name) in format:
            print mod
            call_args.append(retval)
        
        
        if rettype != 'void':
            print '\t%s retval = %s(%s);' % (rettype, fname, ', '.join(call_args))
            tmpl, conv = proc(rettype, 'retval')
            print '\treturn Py_BuildValue("%s", %s);' % (tmpl, conv)
        else:
            print '\t%s(%s);' % (fname, ', '.join(call_args))
            print '\treturn Py_BuildValue("i", 0);'
        print '}'
        
        if rettype != 'void':
            pass
    except:
        traceback.print_exc()
        f = ''
        fails.append((f, line.strip()))
    
    if android:
        print '#endif'

print 'void py_setup_callglue() {'
print 'void* ptr;'
for name, android in names:
    if android:
        print '#ifdef ANDROID'
    print '\tptr = python_%s;' % name
    print '\tPY_CALL("ssi", "add_function", "%s", (int)ptr);' % name
    if android:
        print '#endif'
print '}'
