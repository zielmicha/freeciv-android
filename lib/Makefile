all: graphics.so
graphics.c: graphics.pyx SDL.pxd
	cython graphics.pyx
graphics.so: graphics.c
	gcc graphics.c -o graphics.so -shared -Wall -lpython2.7 \
		-I/usr/include/python2.7 -I/usr/local/include/SDL/ -I/usr/include/SDL/ \
		-fPIC -L/usr/local/lib -L/usr/local/sdllib -lSDL -lSDL_image -lSDL_ttf
