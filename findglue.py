import os, glob, sys

start = '*******************************************************************/'
end = '/* PORTME */'

def tokenize_lines(fn):
    lines = open(fn).read().splitlines()
    funcs = []
    i = 0
    while i < len(lines):
        line = lines[i]
        i_start = i
        if end in line:
            #print '%d: %s' % (i, line)
            content = []
            while i >= 0:
                line = lines[i]
                if start in line:
                    content.reverse()
                    ret_content = []
                    for line in content:
                        if '{' in line:
                            break
                        ret_content.append(line)
                    ret = '\n'.join(ret_content)
                    yield ' '.join(ret.split())
                    break
                content.append(line)
                i -= 1
            if i == -1:
                print >>sys.stderr, '%s:%d: Bad func call' % (fn, i_start)
            i = i_start + 1
        i += 1

path = 'src/client/gui-stub/*.c'

cfiles = glob.glob(path)
out = open('gui-stub', 'w')

for cfile in cfiles:
    print >>out
    print >>out, 'File', cfile
    for text in tokenize_lines(cfile):
        print >>out, text

out.close()