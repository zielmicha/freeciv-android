import ui
import graphics

class Widget(object):
    def back(self, _is_not_overriden=None):
        return True

    def is_back_overriden(self):
        # hack
        try:
            return not self.back(_is_not_overriden=None)
        except TypeError:
            return True

    def event(self, ev):
        pass

    def tick(self):
        pass

    def update_layout(self):
        pass

class Layer(Widget):
    def do_draw(self, surf, pos, offset, clip, full_texture=None):
        if surf == graphics.get_window() and ui.layer_hooks.is_bound():
            if full_texture:
                tex = full_texture
            else:
                tex = graphics.create_surface(*self.get_content_size())
                self.draw_content(tex, (0, 0))
            ui.layer_hooks.execute(id=id(self),
                                   surf=tex,
                                   pos=pos,
                                   offset=offset,
                                   size=clip)
            # not only for decorative purposes - also somehow causes SDL to return right renderer data
            surf.draw_rect((255, 255, 255, 255), pos + clip, blend=graphics.MODE_NONE)
        else:
            if full_texture:
                surf.blit(full_texture, dest=pos, src=offset + clip)
            else:
                cliptex = graphics.create_surface(*clip)
                x, y = offset
                self.draw_content(cliptex, (-x, -y))
                surf.blit(cliptex, pos)

    def draw(self, surf, pos):
        self.do_draw(surf, pos,
                     offset=self.get_offset(),
                     clip=self.get_clip())

class LayerAware(object):
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
