structs = 'sprite,canvas'.split(',')
structs = [ 'struct ' + s for s in structs ]

types = {
    'int': 'i',
    'char*': 's', 
}

ignore = 'get_overview_area_dimensions gfx_fileextensions get_sprite_dimensions ' \
         'city_dialog_is_open get_text_size gui_set_rulesets add_idle_callback ' \
         'caravan_dialog_is_open popup_pillage_dialog color_alloc get_gui_specific_themes_directories ' \
         'get_useable_themes_in_directory ui_main'.split()

mappers = 'city player unit tile packet_game_load text_tag_list unit_list color packet_endgame_report'.split()

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
        elif type in mappers:
            return 'O', 'py_mapper_%s(&%s)' % (type, name)
        else:
            raise ValueError('Bad type %s' % type)
    if type == 'bool':
        return 'i', '(int)' + name
    return types[type], name

def proc_ret(type):
    if type.endswith('*') and type[:-1] in structs:
        return 'PyObject*', 'O', '''
\t%s retstru = py_alloc_struct(retval);
\treturn retstru;
        ''' % (type, )
    if type in structs:
        return 'PyObject*', 'O', '''
\t%s retstru;
\tretstru.py_object = retval;
\treturn retstru;
        ''' % type
    if type.startswith('enum '):
        return 'int', 'i', 'return (%s)retval;' % type
    if type == 'bool':
        return 'int', 'i', 'return (bool)retval;'
    return type, types[type], 'return retval;'

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
sys.stdout = open("src/clientauto.c", 'w')
print '#include "pyclient.h"'
for line in open('gui-stub').readlines() + open('gui-manual').readlines():
    if line.startswith('File') or not line.strip():
        continue
    print '// %s' % line.strip()
    start, rest = line.strip().split('(', 1)
    rettype, fname = start.rsplit(None, 1)
    
    while fname.startswith('*'):
        rettype += '*'
        fname = fname[1:]
    
    if fname in was_printed:
        print '// continue %s - was processed' % fname
        continue
    was_printed.add(fname)
    
    if fname in ignore:
        nign += 1
        ignored.append(line)
        print '// ignored'
        print 
        continue
    
    nproc += 1
    
    try:
        rest, _ = rest.split(')', 1)
        if rest.strip() in ('void', ''):
            args = []
        else:
            args = [ p2(a.rsplit(None, 1)) for a in rest.split(',') ]
        
        format = [ proc(type, name)[0] for type, name in args ]
        args = [ proc(type, name)[1] for type, name in args ]
        
        print line.strip() + '{'
        joinedargs = ', '.join(args)
        if joinedargs:
            joinedargs = ', ' + joinedargs
        print '\tPyObject* ret = PY_CALL("s%s", "%s"%s);' % (''.join(format), fname, joinedargs)
        if rettype != 'void':
            mrettype, retcode, retproc = proc_ret(rettype)
            print '\t%s retval;' % mrettype
            val = '\tif(PyArg_ParseTuple(ret, "%s", &retval) == 0) fprintf(stderr, "TypeError: bad return value from %s (expected %r)\\n");' % (retcode, fname, retcode)
            print val
            print '\t%s' % retproc
        print '}'
        
        if rettype != 'void':
            pass
    except:
        f = traceback.format_exc()
        fails.append((f, line.strip()))

for i, (f, n) in enumerate(fails):
    print >>sys.stderr, '// %d failed' % (i+1), n
    print >>sys.stderr, '//  ' +f.replace('\n', '\n//  ')

print '// IGNORED:'
for ign in ignored:
    print '// ', ign.strip()

print '// processed %d ignored %d' % (nproc, nign)