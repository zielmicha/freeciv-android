import ui
import graphics

class DecoratedWidget(ui.Widget):
    widget_background = None

    def draw(self, surf, pos):
        if self.widget_background:
            surf.draw_rect(self.widget_background, pos + self.size)

class LayoutWidget(DecoratedWidget):
    def __init__(self):
        self.items = []
        self.positions = []
        self.holds_mouse = None
        self.holds_mouse_pos = None
        self.last_hovered = None
        self.focus = None

    def add(self, item):
        assert isinstance(item, ui.Widget)
        self.items.append(item)

    def unhover(self):
        for item in self.items:
            self._call_unhover(item)

    @staticmethod
    def _call_unhover(item):
        if hasattr(item, 'unhover'):
            item.unhover()

    def event(self, event):
        if hasattr(event, 'pos'):
            evpos = event.pos

            if self.holds_mouse:
                itemiter = self.get_items_at(evpos, (self.holds_mouse, self.holds_mouse_pos))
            else:
                itemiter = self.get_items_at(evpos)

            handled = False
            for item, itempos in itemiter:
                event.pos = _subpoints(event.pos, itempos)
                result = item.event(event)
                event.pos = _addpoints(event.pos, itempos)
                if result != False:
                    if self.last_hovered != item:
                        self._call_unhover(self.last_hovered)
                        self.last_hovered = None

                    if event.type == graphics.const.MOUSEBUTTONDOWN:
                        if result == ui.LOCK_MOUSE_EVENT:
                            self.holds_mouse = item
                            self.holds_mouse_pos = itempos
                            return ui.LOCK_MOUSE_EVENT
                        self.last_hovered = item
                    handled = True
                    break

            if event.type == graphics.const.MOUSEBUTTONUP:
                self.holds_mouse = None

            if not handled:
                self._call_unhover(self.last_hovered)
                self.last_hovered = None

            return handled
        else:
            if self.focus:
                self.focus.event(event)
            elif self.items:
                self.items[0].event(event)

    def get_position_of(self, item):
        if item in self.items:
            return self.positions[self.items.index(item)]
        for child in self.items:
            if hasattr(child, 'get_position_of'):
                child_pos = self.positions[self.items.index(child)]
                rel_pos = child.get_position_of(item)
                if rel_pos:
                    return rel_pos[0] + child_pos[0], rel_pos[1] + child_pos[1]
        return None

    def get_items_at(self, evpos, yield_this=None):
        if yield_this:
            yield yield_this
        for itempos, item in reversed(zip(self.positions, self.items)):
            relpos = _subpoints(evpos, itempos)
            if relpos[0] > 0 and relpos[1] > 0 and relpos[0] < item.size[0] and relpos[1] < item.size[1]:
                yield item, itempos

    def update_layout(self):
        for item in self.items:
            item.update_layout()

        self.positions = list(self.get_positions())

    def tick(self):
        for item in self.items:
            item.tick()

    def draw(self, surf, pos):
        DecoratedWidget.draw(self, surf, pos)

        self.positions = list(self.get_positions())

        for itempos, item in zip(self.positions, self.items):
            item.draw(surf, _addpoints(pos, itempos))

    def draw_clipped(self, surf, pos, rect):
        rect = graphics.Rect(rect)
        cliptex = graphics.create_surface(rect[2], rect[3])
        relpos = _subpoints(pos, (rect[0], rect[1]))
        self.positions = list(self.get_positions())

        for itempos, item in zip(self.positions, self.items):
            item.draw(cliptex, _addpoints(relpos, itempos))

        surf.blit(cliptex, (rect[0], rect[1]))

def _addpoints(a, b):
    return a[0] + b[0], a[1] + b[1]

def _subpoints(a, b):
    return a[0] - b[0], a[1] - b[1]


class Spacing(ui.Widget):
    def __init__(self, x, y):
        self.size = (x, y)

    def draw(self, surf, pos):
        pass

class LinearLayoutWidget(LayoutWidget):
    def __init__(self, spacing=10, marginleft=0, center=False, force_full=False):
        LayoutWidget.__init__(self)
        self.spacing = spacing
        self.marginleft = marginleft
        self.center = center
        self.force_full = force_full
        self._size = (0, 0)

    @property
    def size(self):
        if self.force_full:
            return (ui.screen_width, self._size[1])
        else:
            return self._size

    def get_positions(self):
        y = 0
        w = ui.screen_width if self.force_full else max([ item.size[0] for item in self.items ] + [0])
        center_at = w*self.center if isinstance(self.center, (int, float)) else w
        for item in self.items:
            y += self.spacing
            centerx = (center_at - item.size[0])/2 if self.center else 0
            yield (self.marginleft + centerx, y)
            y += item.size[1]
        self._size = (w + self.marginleft, y)

class HorizontalLayoutWidget(LayoutWidget):
    def __init__(self, spacing=0, margintop=0):
        LayoutWidget.__init__(self)
        self.spacing = spacing
        self.margintop = margintop
        self.size = (0, 0)

    def get_positions(self):
        x = 0
        h = 0
        for item in self.items:
            x += self.spacing
            yield (x, self.margintop)
            x += item.size[0]
            h = max(h, item.size[1])
        self.size = (x, h)

BOTTOM = 1
LEFT = 0
RIGHT = 2
TOP = 0

class AbsoluteLayoutWidget(LayoutWidget):
    def __init__(self):
        LayoutWidget.__init__(self)
        self.size = (0, 0)

    def add(self, widget, pos, align=0):
        widget.pos = pos
        widget.align = align
        self.items.append(widget)

    def get_positions(self):
        sw, sh = 0, 0
        for item in self.items:
            pos = item.pos
            sw = max(sw, pos[0] + item.size[0])
            sh = max(sh, pos[1] + item.size[1])

        for item in self.items:
            pos = item.pos

            if item.align & BOTTOM:
                pos = pos[0], sh - pos[1] - item.size[1]
            elif item.align & RIGHT:
                pos = sw - pos[0] - item.size[0], pos[1]

            yield pos

        self.size = sw, sh

class Bordered(LinearLayoutWidget):
    def __init__(self, item, force_width=None):
        LinearLayoutWidget.__init__(self)
        self.force_width = force_width
        self.add(item)

    @property
    def size(self):
        if self.force_width:
            return self.force_width, self._size[1]
        else:
            return self._size

    def draw(self, surf, pos):
        surf.draw_rect((0, 0, 0), pos + self.size, 1)
        LinearLayoutWidget.draw(self, surf, pos)
