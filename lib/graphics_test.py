import graphics
import time

graphics.init()
wnd = graphics.create_window((640, 800), 24)
wnd.fill()
tex = graphics.create_surface(500, 500)
tex.fill((255, 0, 255))
for i in xrange(42):
    tex.gfx_rect((255, 0, 0), (i * 10, i * 10, 200, 200), 10)
    wnd.blit(tex)
    graphics.flip()
    time.sleep(0.1)
