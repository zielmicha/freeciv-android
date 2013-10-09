import ui
import graphics

class WithText(ui.Widget):
    def __init__(self, label, callback, font=None, color=None, padding=0, force_width=None, image=None):
        self.callback = callback
        self.font = font or ui.mediumfont
        self.color = color or (0, 0, 0)
        self.label = None
        self.padding = padding
        self.force_width = force_width
        self.image = image
        self._scaled_image = None
        self._scaled_size = None
        self.set_text(label)

    def set_text(self, label):
        if label != self.label:
            self.label = label
            self.redraw()

    def redraw(self):
        self.label_image = ui.render_text(self.font, self.label, self.color)
        size = self.label_image.get_size()
        if self.force_width:
            size = self.force_width, size[1]
        self.size = size[0] + self.padding*2, size[1] + self.padding*2
        self.padding_left = (self.size[0] - self.label_image.get_size()[0])/2
        self.padding_top = (self.size[1] - self.label_image.get_size()[1])/2

    def tick(self):
        pass

    def event(self, event):
        if event.type == graphics.const.MOUSEBUTTONUP:
            if self.callback:
                self.callback()

    def draw(self, surf, pos):
        surf.blit(self.label_image, (pos[0] + self.padding_left, pos[1] + self.padding_top))
        if self.image:
            if self._scaled_size != self.size:
                scale_w = float(self.size[0]) / self.image.get_width()
                scale_h = float(self.size[1]) / self.image.get_height()
                scale = min(scale_w, scale_h)
                w, h = self.image.get_size()
                self._scaled_image = self.image.scale((int(w*scale), int(h*scale)))
                self._scaled_size = self.size

            iw, ih = self._scaled_image.get_size()
            w, h = self.size
            surf.blit(self._scaled_image, (pos[0] + (w - iw)/2, pos[1] + (h - ih)/2))

def _round_rect(surface, color, rect, width, xr, yr):
    # draw normal rect
    surface.draw_rect(color, rect, width)

def round_rect(surf, bg, fg, rect, round=10):
    rect = graphics.Rect(rect)
    _round_rect(surf, bg, rect, 0, round, round)
    _round_rect(surf, fg, rect, 1, round, round)

class Button(WithText):
    active_bg = (255, 255, 200, 150)
    bg = (130, 100, 0, 90)
    fg = (150, 150, 50)

    def __init__(self, label, callback, font=None, color=None, force_width=None, force_height=None, image=None):
        WithText.__init__(self, label, callback, font, color, padding=4, force_width=force_width, image=image)
        self.active = False

    def draw(self, surf, pos):
        if self.active:
            color = self.active_bg
        else:
            color = self.bg
        surf.draw_rect(color, pos + self.size, width=0)
        surf.draw_rect(self.fg, pos + self.size, width=1)
        WithText.draw(self, surf, pos)

    def unhover(self):
        self.active = False

    def event(self, event):
        if event.type == graphics.const.MOUSEBUTTONDOWN:
            self.active = True
        elif event.type == graphics.const.MOUSEBUTTONUP:
            self.active = False
            if self.callback:
                self.callback()

class EditField(Button):
    def __init__(self, label='', font=None, color=None, placeholder=None):
        Button.__init__(self, label, self.callback, font, color)
        self.placeholder = placeholder
        self.set_value(label)

    def callback(self):
        import uidialog
        data = uidialog.inputbox('')
        if data != None:
            self.set_value(data)

    def set_value(self, data):
        self.value = data
        self.set_text(self.placeholder*len(data) if self.placeholder else data)

        if not self.value:
            self.set_text('<touch to change>')

    def get_value(self):
        return self.value

class Label(WithText):
    def __init__(self, label, callback=None, font=None, color=None, image=None):
        WithText.__init__(self, label, callback, font, color, image=image)

class Tooltip(Label):
    def __init__(self, text, pos, **kwargs):
        Label.__init__(self, text, **kwargs)
        ui.add_overlay(self, pos)

    def remove(self):
        ui.overlays.remove(self)

class Image(ui.Widget):
    def __init__(self, img, callback=None):
        self.image = img
        self.size = self.image.get_size()
        self.callback = callback

    def event(self, event):
        if event.type == graphics.const.MOUSEBUTTONUP:
            if self.callback:
                self.callback()

    def draw(self, surf, pos):
        surf.blit(self.image, pos)

class Menu(ui.LinearLayoutWidget):
    def __init__(self, font=None, force_full=True, center=True, for_dialog=False):
        ui.LinearLayoutWidget.__init__(self,
                                       center=False if for_dialog else center,
                                       force_full=False if for_dialog else force_full,
                                       marginleft=0.1 * ui.screen_width if for_dialog else 0)
        self.font = font or ui.bigfont

    def add(self, label, callback, color=(0, 0, 0), button_class=Button):
        screen_width = graphics.get_window().get_width()
        self.items.append(button_class(label, callback,
                                       self.font, color=color, force_width=0.5*screen_width))
