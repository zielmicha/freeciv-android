# Copyright (C) 2013 Michal Zielinski (michal@zielinscy.org.pl)
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

import io

#import jnius
import reflect as jnius_reflect

Wrapper = jnius_reflect.autoclass("com.zielm.p4a.Wrapper")
PorterDuffMode = jnius_reflect.autoclass("android.graphics.PorterDuff$Mode")
Canvas = jnius_reflect.autoclass("android.graphics.Canvas")
Bitmap = jnius_reflect.autoclass("android.graphics.Bitmap")
BitmapConfig = jnius_reflect.autoclass("android.graphics.Bitmap$Config")
BitmapFactory = jnius_reflect.autoclass("android.graphics.BitmapFactory")
jRect = jnius_reflect.autoclass("android.graphics.Rect")
Paint = jnius_reflect.autoclass("android.graphics.Paint")
PorterDuffXfermode = jnius_reflect.autoclass("android.graphics.PorterDuffXfermode")

MotionEvent = jnius_reflect.autoclass("android.view.MotionEvent")

_window = None

def init():
    pass

def create_surface(w, h, alpha=True):
    w = max(1, w); h = max(1, h)
    b = Bitmap.createBitmap(w, h, BitmapConfig.ARGB_8888);
    return Surface(bitmap=b)

create_surface_small = create_surface

def get_screen_size():
    return (1000, 1000)

def get_window():
    global _window
    return _window

def lock_window():
    global _window
    canvas = Wrapper.surfaceHolder.lockCanvas()
    _window = Surface(canvas)
    return _window

def flip():
    Wrapper.surfaceHolder.unlockCanvasAndPost(_window.canvas)
    _window.usable = False

MODE_BLEND = PorterDuffMode.SRC_OVER
MODE_MOD = PorterDuffMode.MULTIPLY
MODE_NONE = PorterDuffMode.DST
MODE_ADD = PorterDuffMode.ADD

_xfermode = { mode:PorterDuffXfermode(mode) for mode in [MODE_BLEND, MODE_MOD, MODE_NONE, MODE_ADD] }

class Surface(object):
    def __init__(self, canvas=None, bitmap=None):
        self.canvas = canvas
        self.bitmap = bitmap
        self.usable = True
        self._paint = None
        self.filename = None

    def _init_draw(self):
        if not self.usable:
            raise RuntimeError('Surface set to unusable (using surface from lock_window after flip?)')
        if not self.canvas:
            self.canvas = Canvas(self.bitmap)
        if not self._paint:
            self._paint = Paint()

    def get_size(self):
        if self.bitmap:
            return self.bitmap.getWidth(), self.bitmap.getHeight()
        else:
            return self.canvas.getWidth(), self.canvas.getHeight()

    def get_width(self):
        return self.get_size()[0]

    def get_height(self):
        return self.get_size()[1]

    def blit(self, image, dest=(0, 0), src=None, blend=MODE_BLEND):
        if not src:
            src = (0, 0, image.get_width(), image.get_height())
        if len(dest) == 2:
            dest = (dest[0], dest[1], src[2], src[3])

        self._init_draw()
        self._paint.setXfermode(_xfermode[blend])
        self.canvas.drawBitmap(image.bitmap, _make_rect(src), _make_rect(dest), self._paint)

    def draw_rect(self, color, rect, width=0, blend=MODE_BLEND):
        self._init_draw()
        self._paint.setColor(_rgba(color))
        self.canvas.drawRect(_make_rect(rect), self._paint)

    def fill(self, color=(128, 0, 128), blend=MODE_BLEND):
        self._init_draw()
        self.canvas.drawColor(_rgba(color), blend)

    def draw_line(self, color, start, end, blend=MODE_BLEND):
        self._init_draw()
        self._paint.setColor(_rgba(color))

    def scale(self, size):
        return Surface(bitmap=Bitmap.createScaledBitmap(self.bitmap, size[0], size[1], True))

    def checked_cropped(self, rect):
        pass

    def gfx_rect(self, color, rect, width, **kwargs):
        self.draw_rect(color, rect, width, **kwargs)

    def get_clip(self):
        return Rect((0, 0, 8000, 8000))

    def __repr__(self):
        return '<Surface 0x%X filename=%r>' % (id(self), self._filename)

def _make_rect(tpl):
    return jRect(tpl[0], tpl[1], tpl[0] + tpl[2], tpl[1] + tpl[3])

def _rgba(tpl):
    alpha = tpl[3] if len(tpl) == 4 else 0xFF
    return _unsigned(alpha << 24 | tpl[0] << 16 | tpl[1] << 8 | tpl[2])

MAXINT = 2**31
import struct

def _unsigned(val):
    # converts signed int to unsigned (C ABI)
    return struct.unpack('i', struct.pack('I', val))[0]

class Rect(tuple):
    def colliderect(self, point):
        x, y, w, h = self
        x1, y1 = point
        return x1 >= x and x1 < x + w and y1 >= y and y1 < y + h

    def inflate(self, W, H):
        x, y, w, h = self
        return x - W, y - H, w + W * 2, h + H * 2

    def clip(self, other):
        x, y, w, h = self
        x1, y1, w1, h1 = other
        return Rect((max(x, x1), max(y, y1), min(x + w, x1 + w1) - max(x, x1), \
            min(y + h, y1 + h1) - max(y, y1)))

    def empty(self):
        x, y, w, h = self
        return w <= 0 or h <= 0

    @property
    def left(self):
        return self[0]

    @property
    def right(self):
        return self[0] + self[2]

    @property
    def top(self):
        return self[1]

    @property
    def bottom(self):
        return self[1] + self[3]

def load_image(fn):
    input_stream = Wrapper.context.getAssets().open(fn)
    bitmap = BitmapFactory.decodeStream(input_stream)
    surf = Surface(bitmap=bitmap)
    surf.filename = fn
    return surf

def load_font(name, size):
    return Font(name, size)

def start_text_input():
    pass

def stop_text_input():
    pass

def get_events():
    events = []
    while True:
        ev = Wrapper.getEvent()
        if not ev: break
        events.append(ev)
    return map(map_event, events)

def map_event(ev):
    name = ev.name
    val = ev.value
    if name == 'touch':
        if val.getAction() in (MotionEvent.ACTION_UP, MotionEvent.ACTION_CANCEL):
            type = const.MOUSEBUTTONUP
        else:
            type = const.MOUSEBUTTONDOWN
        return Event(type, pos=(val.getX(), val.getY()), button=0)
    else:
        return Event(name)

key_map = {}

def map_key(src, dst):
    key_map[src] = dst

class Event:
    def __init__(self, type, **dict):
        self.type = type
        for k, v in dict.items():
            setattr(self, k, v)

    @property
    def dict(self):
        return self.__dict__

    def __repr__(self):
        return 'Event(%s, %s)' % (self.type, self.__dict__)

def sdl_open(path):
    # TODO: this is probably very slow
    input_stream = Wrapper.context.getAssets().open(path)
    out = iter(input_stream.read, -1)
    return io.BytesIO(''.join(map(chr, out)))

class Font(object):
    def __init__(self, name, size):
        self._bounds = jRect()
        self._paint = Paint()
        self._paint.setAnitAlias(True)
        self._size = size
        self._paint.setTextSize(self._size)

    def render(self, text, antialias=1, fg=(0, 0, 0), bg=None):
        self._paint.setColor(_rgba(fg))
        surf = create_surface(*self.size(text))
        surf._init_draw()
        surf.canvas.drawText(text, 0, surf.get_height(), self._paint)
        return surf

    def size(self, text):
        return int(self._paint.measureText(text)), int(self._size * (text.count('\n') + 1))

class const: pass

const = const()

_consts = ['MOUSEBUTTONUP', 'MOUSEBUTTONDOWN', 'MOUSEMOTION', 'TEXTEDITING', 'TEXTINPUT', 'QUIT', 'KEYDOWN', 'KEYUP', 'K_UP', 'K_DOWN', 'K_LEFT', 'K_RIGHT', 'K_SPACE', 'K_ESCAPE', 'K_BACKSPACE', 'K_AC_BACK', 'K_F1', 'K_a', 'K_b', 'K_c', 'K_d', 'K_e', 'K_f', 'K_g', 'K_h', 'K_i', 'K_j', 'K_k', 'K_l', 'K_m', 'K_o', 'K_p', 'K_q', 'K_r', 'K_s', 'K_t', 'K_u', 'K_v', 'K_w', 'K_x', 'K_y', 'K_z']

for item in _consts:
    setattr(const, item, item)
