all: graphics.so
graphics.c: graphics.pyx SDL.pxd
	cython graphics.pyx
graphics.so: graphics.c
	gcc graphics.c -o graphics.so -shared -Wall -lpython2.7 -I/usr/include/python2.7 -fPIC
