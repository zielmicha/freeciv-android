cdef extern from *:
    void initgraphics()
    void init_io()
    void initfreecivclient()

def unpack_data():
    curr_version = open('version').read()
    try:
        if open('version_ready').read() == curr_version:
            return
    except IOError:
        pass

    import tarfile
    print 'extracting data...'
    tarfile.open('data.tgz').extractall()

    with open('version_ready', 'w') as f:
        f.write(curr_version)

def main():
    init_io()
    initgraphics()
    initfreecivclient()

    import sys

    sys.path = []
    sys.path = ['modules.zip']

    import os

    unpack_data()

    sys.path = [os.path.abspath('modules.zip')]

    import freeciv.main
    freeciv.main.main()

main()
