import pygame
import sys

def make(i):
        for x in xrange(i.get_width()):
                for y in xrange(i.get_height()):
                        r,g,b,a = i.get_at((x, y))
                        C = 255
                        i.set_at((x, y), (C, C, C, a))

i = pygame.image.load(sys.argv[1])
make(i)
pygame.image.save(i, sys.argv[2])

