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

import client
import pygame

def get_small_image(name):
    try:
        return small_images[small_image_names.index(name)]
    except ValueError:
        raise KeyError(name)

icons_scale = 8

small_image_names = [
    'bulb-0',
    'bulb-1',
    'bulb-2',
    'bulb-3',
    'bulb-4',
    'bulb-5',
    'bulb-6',
    'bulb-7',
    'anarchy',
    'despotism',
    'monarchy',
    'comunism',
    'fanatism',
    'republic',
    'democracy',
    'warming-0',
    'warming-1',
    'warming-2',
    'warming-3',
    'warming-4',
    'warming-5',
    'warming-6',
    'warming-7',
    'elvis',
    'scientist',
    'taxman',
    'content-0',
    'content-1',
    'happy-0',
    'happy-1',
    'unhappy-0',
    'unhappy-1',
    'angry-0',
    'angry-1',
    'nuclear-0',
    'nuclear-1',
    'nuclear-2',
    'nuclear-3',
    'nuclear-4',
    'nuclear-5',
    'nuclear-6',
    'nuclear-7',
]

def load_small_images():
    global small_images
    
    img = client.common.load_gfxfile('data/misc/small.png')
    small_images = client.common.split_sprites(img, (0, 0), (15, 20), (15, 20), (40, 1))[0]

def init():
    load_small_images()