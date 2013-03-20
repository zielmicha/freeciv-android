l = 'abcdefghijklmopqrstuvwxyz'

for ch in l:
	print '        SDLK_%s' % ch

for ch in l:
	print '    K_%s = SDLK_%s' % (ch, ch)
