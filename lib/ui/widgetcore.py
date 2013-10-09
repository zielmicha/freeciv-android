import ui
import graphics

class Widget(object):
    def back(self):
        return True

    def event(self, ev):
        pass

    def tick(self):
        pass

class Animation(Widget):
    spacing = 0.2

    def __init__(self, src, dest, dir):
        self.src = src
        self.dest = dest
        self.dir = dir
        self.samebg = getattr(self.src, 'screen_background', None) == getattr(self.dest, 'screen_background', None)
        self.screen_background = 0xFFFFFF

        self.frame = 0
        self.duration = 3

    def draw(self, surf, pos):
        width = ui.screen_width * (self.spacing + 1)
        x, y = pos
        time = float(self.frame) / self.duration
        if self.dir == 1:
            a = self.src
            b = self.dest
            at = -time
        else:
            a = self.dest
            b = self.src
            at = time - 1
        a_x = int(at * width)
        b_x = int((at+1) * width)

        if not self.samebg:
            ui.fill(surf, (b_x + x, y), b)
        else:
            ui.fill(surf, (0, 0), b)
        b.draw(surf, (b_x + x, y))
        if not self.samebg:
            ui.fill(surf, (a_x + x, y), a)
        a.draw(surf, (a_x + x, y))

    def tick(self):
        self.frame += 1
        if self.frame == self.duration:
            ui.replace(self.dest)

    def event(self, ev):
        pass

    def back(self):
        return self.dest.back()
