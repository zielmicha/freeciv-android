# Copyright (C) 2011 Michal Zielinski (michal@zielinscy.org.pl)
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

import graphics
from freeciv.client import _freeciv as freeciv
import window
import sys
import time
from freeciv import features
from freeciv import osutil

DO_MASK = False

@freeciv.register
def load_gfxfile(fn):
    if fn.startswith('flags/'):
        return load_flag(fn[len('flags/'):])
    else:
        if not fn.startswith('data/'):
            fn = 'data/' + fn
            try:
                return graphics.load_image(fn + '.png')
            except graphics.SDLError:
                return graphics.load_image(fn + '.jpg')
        return graphics.load_image(fn)

@freeciv.register
def get_sprite_dimensions(image):
    return image.get_size()

@freeciv.register
def crop_sprite(img, x, y, w, h, mask=None, mask_x=0, mask_y=0):
    surf = graphics.create_surface(w, h)
    surf.blit(img, (0, 0), (x, y, w, h))
    surf.filename = '%s%s[%d,%d,%d,%d]' % (img.filename,
                                           ',masked' if mask else '', x, y, w, h)
    if mask:
        return mask_sprite(surf, mask, x - mask_x, y - mask_y)
    else:
        return surf

mask_i = 0
masking_shown = 0

mask_numbers = [652, 270]
mask_stage = 0

def mask_sprite(surf, mask, mx, my):
    mask = get_white_mask(mask)
    newsurf = graphics.create_surface(*surf.get_size())
    newsurf.blit(surf)
    newsurf.blit(mask, src=(mx, my) + surf.get_size(), blend=graphics.MODE_MOD)
    return newsurf

mask_cache = {}

def get_white_mask(mask):
    # HACK: SDL doesn't allow us to access raw pixel data of textures
    # so load modified image from disk based on surface _filename
    name, params = mask.filename[:-1].split('[', 1)
    params = tuple(map(int, params.split(',')))
    base, ext = name.split('.')
    name = base + '_white.' + ext
    if (name, params) not in mask_cache:
        base_img = graphics.load_image(name)
        mask_cache[name, params] = crop_sprite(base_img, *params)
    return mask_cache[name, params]

@freeciv.register
def canvas_create(w, h):
    return graphics.create_surface(w, h, alpha=False)

def nulldebug(*a):
    pass

@freeciv.register
def canvas_copy(canvas, src, sx, sy, x, y, w, h):
    if canvas:
        canvas.blit(src, (x, y), (sx, sy, w, h))
    else:
        nulldebug('canvas_copy: canvas == NULL')

@freeciv.register
def canvas_put_rectangle(canvas, color, x, y, w, h):
    if canvas:
        canvas.draw_rect(color, (x, y, w, h), 0)
    else:
        nulldebug('canvas_put_rectangle: canvas == NULL')

@freeciv.register
def canvas_put_line(canvas, color, ltype, x, y, dx, dy):
    canvas.draw_line(color, (x, y), (x + dx, y + dy))

@freeciv.register
def canvas_put_sprite(canvas, x, y, sprite, ox, oy, w, h):
    if canvas and sprite:
        canvas.blit(sprite, (x, y), (ox, oy, w, h))
    if not canvas:
        nulldebug('canvas_put_sprite: canvas == NULL')
    if not sprite:
        nulldebug('canvas_put_sprite: sprite == NULL')

@freeciv.register
def canvas_put_sprite_full(canvas, x, y, sprite):
    canvas.blit(sprite, (x, y))

@freeciv.register
def free_sprite(sprite):
    freeciv.func.free_ref(sprite)

@freeciv.register
def canvas_free(sprite):
    freeciv.func.free_ref(sprite)

@freeciv.register
def canvas_put_text(canvas, x, y, font, color, text):
    f = fonts[font]
    surf = f.render(text, 1, color)
    canvas.blit(surf, (x, y))

@freeciv.register
def get_text_size(font, text):
    f = fonts[font]
    return f.size(text)

def split_sprites(img, start, each, size, num):
    y = start[1]
    a = []
    for ny in xrange(num[1]):
        x = start[0]
        l = []
        for nx in xrange(num[0]):
            l.append(crop_sprite(img, x, y, size[0], size[1]))
            x += each[0]
        a.append(l)
        y += each[1]
    return a

FONT_CITY_NAME, FONT_CITY_PROD, FONT_REQTREE_TEXT, FONT_COUNT = range(4)

flag_index = {}

def init():
    global fonts
    fonts = [ graphics.load_font('fonts/OFLGoudyStMTT.ttf', 15) for i in range(4) ]
    init_flags()

def init_flags():
    names = ['large', 'shield', 'shield-large', 'flags']
    for name in names:
        load_flags_file(name)

def load_flags_file(name):
    img = graphics.load_image('data/flags/%s-output.png' % name)
    for line in osutil.open_res('data/flags/%s.index' % name):
        name, rect = line.split(' ', 1)
        rect = map(int, rect.split())
        flag = graphics.create_surface(rect[2], rect[3])
        flag.blit(img, (0, 0), rect)
        flag_index[name] = flag

def load_flag(name):
    if not name.endswith('.png'):
        name += '.png'
    return flag_index[name]
