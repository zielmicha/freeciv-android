#!/usr/bin/python
import glob
import sys
import math

args = sys.argv[1:]
if len(args) != 3:
	sys.exit('usage: ./compose.py pattern blackwords outputname')

pattern, blackwords, output = args
blackwords = blackwords.split(',')

names = glob.glob(pattern)
if any(blackwords):
	names = [ name for name in names if all( word not in name for word in blackwords ) ]

if not names:
	sys.exit('%s not found' % pattern)

import pygame

print 'loading %d images...' % len(names)
images = [pygame.image.load(name) for name in names]

size = images[0].get_size()

processed_images = []
for name, image in zip(names, images):
	if image.get_size() != size:
		print 'image %s has different size from %s' % (name, names[0])

dimension = int(math.ceil(len(names)**0.5))

w = size[0] * dimension
h = size[1] * dimension
print 'creating image (%d, %d)...' % (w,h)
canvas = pygame.Surface((w, h), pygame.SRCALPHA)

x = 0
y = 0
index = []
for name, image in zip(names, images):
	x += 1
	if x == dimension:
		y += 1
		x = 0
	rx = x * size[0]
	ry = y * size[1]
	index.append((name, rx, ry) + image.get_size())
	canvas.blit(image, (rx, ry), (0, 0) + size)

png_name = output + '-output.png'
print 'saving to %s...' % png_name
pygame.image.save(canvas, png_name)

with open(output + '.index', 'w') as out:
	for defn in index:
		out.write(' '.join(map(str, defn)) + '\n')

print 'creating %s succeed' % output
