cdef extern from *:
    void initgraphics()
    void initfreecivclient()
    void initselect()

include "main_common.pxi"

def main():
    print 'main_win.pyx'
    initgraphics()
    initfreecivclient()

    import sys

    sys.path = []
    sys.path = ['modules.zip', os.getcwd()]

    import os

    unpack_data()

    sys.path = [os.path.abspath('modules.zip'), os.getcwd()]

    #import code
    #code.interact()

    import freeciv.main
    freeciv.main.main()

main()
