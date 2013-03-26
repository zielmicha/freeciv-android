all: graphics.so
graphics.c: graphics.pyx SDL.pxd
	cython graphics.pyx
graphics.so: graphics.c
	gcc graphics.c -o graphics.so -shared -Wall -lpython2.7 \
		-I/usr/include/python2.7 -I/usr/local/include/SDL2/ -I/usr/include/SDL2/ \
		-fPIC -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf
