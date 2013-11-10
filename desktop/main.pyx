cdef extern from *:
    void initgraphics()
    void init_io()
    void initfreecivclient()

def main():
    print 'running main.pyx'
    init_io()
    initgraphics()
    initfreecivclient()

    import sys
    import os
    os.chdir('..')
    sys.path.append('lib')

    import freeciv.main
    freeciv.main.main()

main()
