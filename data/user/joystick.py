import pygame

std = pygame.image.load('joystick.png')
mpa = pygame.image.load('joystick-map.png')

colors = {
	(0xff, 0xff, 0): 'n',
	(0, 0, 0x80): 'ne',
	(0, 0xff, 0xff): 'e',
	(0, 0xff, 0): 'se',
	(0xff, 0, 0): 's',
	(0, 0, 0): 'sw',
	(0xff, 0, 0xff): 'w',
	(0, 0, 0xff): 'nw',
	(255, 255, 255): '',
}

news = dict( (k,pygame.Surface(std.get_size(), pygame.SRCALPHA)) for k in colors.values() if k )

COLOR = (255, 0, 0, 90)

def d():
	for x in xrange(std.get_width()):
		for y in xrange(std.get_height()):
			if std.get_at((x, y))[3] < 155: continue
			dir = colors.get(mpa.get_at((x, y))[:3], '')
			if dir: news[dir].set_at((x, y), COLOR)

d()

for k, i in news.items():
	pygame.image.save(i, 'joystick-mask-' + k + '.png')
