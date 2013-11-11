cdef extern from *:
    void initgraphics()
    void init_io()
    void initfreecivclient()

def main():
    init_io()
    initgraphics()
    initfreecivclient()

    import sys

    sys.path = []
    sys.path = ['dist/modules.zip']

    import os

    print os, sys.path

    sys.path = [os.path.abspath('dist/modules.zip')]

    os.chdir('..')
    sys.path.append('lib')

    import freeciv.main
    freeciv.main.main()

main()
