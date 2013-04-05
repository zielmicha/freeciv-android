from struct import pack
import os
import sys
import time

def write(out, entries):
    serial = int(time.time() * 1000)
    out.write(pack('q', serial))
    entries = list(entries)
    out.write(pack('I', len(entries)))
    for type, name, content in entries:
        if name.startswith('.'):
            name = name[2:]
        out.write(pack('I', type))
        out.write(pack('I', len(name)))
        out.write(name)
        out.write(pack('I', len(content)))
        out.write(content)

def search_dir(path):
    stack = [path]
    while stack:
        path = stack.pop()
        if os.path.isdir(path):
            yield (1, path, '')
            stack.extend( path + '/' + name for name in os.listdir(path) )
        else:
            yield (2, path, open(path, 'rb').read())

if __name__ == '__main__':
    os.chdir(sys.argv[1])
    write(sys.stdout, search_dir('.'))
