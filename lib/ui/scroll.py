import ui
import graphics
from ui.layout import _subpoints, _addpoints

SCROLL_HEIGHT = 1
SCROLL_WIDTH = 2

def _scroll_speed_func(v, k):
    if abs(k) < 3:
        return v / 3
    else:
        if abs(k) > 5:
            k = 5 if k > 0 else -5
        return v + (k * 5)

def _sgn(f):
    return 1 if f>0 else (0 if f==0 else -1)

class ScrollWrapper(ui.Layer):
    def __init__(self, item, height=None, width=None, ways=SCROLL_HEIGHT):
        self.item = item
        self.y = 0
        self.x = 0
        self.mul = 1
        self.start_dragging = None
        self.was_dragged = False
        self.height = height or ui.screen_height
        self.width = width or ui.screen_width
        self.use_y = ways & SCROLL_HEIGHT
        self.use_x = ways & SCROLL_WIDTH
        self.vx = 0
        self.vy = 0

    @property
    def size(self):
        return (self.width, self.height)

    def update_layout(self):
        self.item.update_layout()

    def draw_content(self, surf, pos):
        self.item.draw(surf, pos)

    def get_content_size(self):
        return self.item.size

    def get_offset(self):
        return self.x, self.y

    def get_clip(self):
        return self.size

    def tick(self):
        self.x += self.vx
        self.y += self.vy

        self.normalize()

        self.vx -= _sgn(self.vx)
        self.vy -= _sgn(self.vy)

        self.item.tick()

    def normalize(self):
        if self.y > self.item.size[1] - self.height:
            self.y = self.item.size[1] - self.height
            self.vy = 0
        if self.y < 0:
            self.y = 0
            self.vy = 0

        if self.x > self.item.size[0] - self.width:
            self.x = self.item.size[0] - self.width
            self.vx = 0
        if self.x < 0:
            self.x = 0
            self.vx = 0

    def event(self, event):
        if event.type == graphics.const.MOUSEBUTTONDOWN:
            self.vx = 0
            self.vy = 0
            self.start_dragging = event.pos
            self.start_dragging_abs = event.abs_pos
            self.was_dragged = False
            self.canceled_event(event)
            return ui.LOCK_MOUSE_EVENT
        elif event.type == graphics.const.MOUSEMOTION:
            if self.start_dragging:
                dx, dy = _subpoints(self.start_dragging, event.pos)
                if (dx*dx+dy*dy) > 16:
                    self.start_dragging = event.pos
                    self.was_dragged = True
                    self.y += dy
                    self.x += dx
        elif event.type == graphics.const.MOUSEBUTTONUP:
            if self.was_dragged:
                dx, dy = _subpoints(self.start_dragging, event.pos)
                self.vx = _scroll_speed_func(self.vx, dx)
                self.vy = _scroll_speed_func(self.vy, dy)
                self.y += dy
                self.x += dx
            else:
                if self.start_dragging:
                    self.post_mouse_event(ui.Event(graphics.const.MOUSEBUTTONDOWN,
                                                   {'pos': self.start_dragging,
                                                    'abs_pos': self.start_dragging_abs}))
                self.post_mouse_event(event)
            self.start_dragging = None
            self.was_dragged = False
            self.canceled_event(event)
        else:
            self.item.event(event)

        self.normalize()

    def canceled_event(self, event):
        pass

    def post_mouse_event(self, ev):
        pos = ev.pos
        ev.pos = (pos[0] + self.x, pos[1] + self.y)
        self.item.event(ev)
        ev.pos = pos

    def back(self):
        return self.item.back()
