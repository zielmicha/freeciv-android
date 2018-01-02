import graphics
import ui
import osutil
from client import freeciv

class TechTreeWidget(ui.Widget):
    '''
    As tech tree is too big to fit in single texture
    redraw it each frame.
    '''

    # Quick fix because __dealloc__ is never called: share this big structure as a static variable to avoid multiple allocation
    # FIXME: there is still a memory leak in the small TechTreeWidget object created again and again, and never destroyed.
    handle = 0

    def __init__(self):
        if TechTreeWidget.handle != 0:
            freeciv.func.destroy_reqtree(TechTreeWidget.handle)
        TechTreeWidget.handle = freeciv.func.create_reqtree(freeciv.func.get_playing(), True)
        self.size = freeciv.func.py_get_overview_size(TechTreeWidget.handle)

    def draw(self, surf, surf_pos):
        freeciv.func.py_draw_reqtree(TechTreeWidget.handle, surf, 0, 0, surf_pos[0], surf_pos[1], 0, 0)

    def __dealloc__(self):
        freeciv.func.destroy_reqtree(TechTreeWidget.handle)

def show(client):
    widget = TechTreeWidget()
    widget = ui.ScrollWrapper(widget, ways=ui.SCROLL_WIDTH | ui.SCROLL_HEIGHT)
    ui.set(widget)

