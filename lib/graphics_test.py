import graphics
import time

graphics.init()
wnd = graphics.create_window((640, 800), 24)
wnd.fill()
for i in xrange(40):
    wnd.gfx_rect((255, 0, 0), (i * 10, i * 10, 200, 200), 10)
    graphics.flip()
    time.sleep(0.1)
