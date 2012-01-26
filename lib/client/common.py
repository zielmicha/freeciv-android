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

import pygame
import freeciv
import window
import sys
import progress
import time
import features

def set_debug(flag):
    if flag:
        realsurf = pygame.Surface
        def make_surf(size, *args):
            print 'make_surf', size
            return realsurf(size, *args)
        pygame.Surface = make_surf

features.set_applier('debug.makesurf', set_debug, type=bool, default=False)

DO_MASK = False

class SpriteSurface(pygame.Surface):
    pass

@freeciv.register
def load_gfxfile(fn):
    if fn.startswith('flags/'):
        return load_flag(fn[len('flags/'):])
    else:
        return pygame.image.load(fn).convert_alpha()

@freeciv.register
def get_sprite_dimensions(image):
    return image.get_size()

@freeciv.register
def crop_sprite(img, x, y, w, h, mask=None, mask_x=0, mask_y=0):
    surf = pygame.Surface((w, h), pygame.SRCALPHA)
    surf.blit(img, (0, 0), (x, y, w, h))
    if mask:
        mask_sprite(surf, mask, x - mask_x, y - mask_y)
    return surf

mask_i = 0
masking_shown = 0

mask_numbers = [652, 270]
mask_stage = 0

def show_masking_progress():
    global masking_shown, mask_i, mask_stage
    mask_i += 1
    if mask_i > mask_numbers[mask_stage]:
        mask_i -= mask_numbers[mask_stage]
        if mask_stage + 1 < len(mask_numbers):
            mask_stage += 1
    mask_number = mask_numbers[mask_stage]
    if (time.time() - 0.1) > masking_shown:
        masking_shown = time.time()
        progress.draw_frame('masking sprites...', '%s/%s' % (mask_i, mask_number), mask_i / float(mask_number))

def mask_sprite(surf, mask, mx, my):
    show_masking_progress()
    assert mask.get_width() >= surf.get_width() + mx
    assert mask.get_height() >= surf.get_height() + my
    assert mask.get_bitsize() == 32
    assert surf.get_bitsize() == 32
    surf_b = surf.get_buffer()
    mask_b = mask.get_buffer()
    freeciv.mask_sprite(surf_b, surf.get_width(), surf.get_height(), mask_b, mask.get_width(), mx, my)

def py_mask_sprite(surf, mask, mx, my):
    if not DO_MASK:
        return
    
    global mask_i
    mask_i += 1
    msg = 'masking %s' % mask_i
    print msg + '\r',
    sys.stdout.flush()
    
    for x in xrange(surf.get_width()):
        for y in xrange(surf.get_height()):
            r, g, b, a = surf.get_at((x, y))
            mrgba = mask.get_at((x + mx, y + my))
            surf.set_at((x, y), (r, g, b, a * mrgba[3] / 255))
    
    print '\r' + (' ' * len(msg)) + '\r',

@freeciv.register
def canvas_create(w, h):
    return pygame.Surface((w, h))


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
        pygame.draw.rect(canvas, color, (x, y, w, h), 0)
    else:
        nulldebug('canvas_put_rectangle: canvas == NULL')

@freeciv.register
def canvas_put_line(canvas, color, ltype, x, y, dx, dy):
    pygame.draw.line(canvas, color, (x, y), (x + dx, y + dy))

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
    fonts = [ pygame.font.Font('fonts/OFLGoudyStMTT.ttf', 15) for i in range(4) ]
    init_flags()

def init_flags():
    names = ['large', 'shield', 'shield-large', 'flags']
    for name in names:
        load_flags_file(name)

def load_flags_file(name):
    img = pygame.image.load('data/flags/%s-output.png' % name).convert_alpha()
    for line in open('data/flags/%s.index' % name):
        name, rect = line.split(' ', 1)
        rect = map(int, rect.split())
        flag = pygame.Surface(rect[2:], pygame.SRCALPHA)
        flag.blit(img, (0, 0), rect)
        flag_index[name] = flag

def load_flag(name):
    if not name.endswith('.png'):
        name += '.png'
    return flag_index[name]

