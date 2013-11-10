TARGETS=SDL_image/ SDL_ttf/ SDL2/ freetype/

all: getdep archs

archs: i386

i386:
	./buildarch.sh i386

amd64:
	./buildarch.sh amd64

getdep: $(addsuffix autogen.sh, $(TARGETS)) Python

SDL_image/autogen.sh:
	hg clone -r 363 https://hg.libsdl.org/SDL_image/

SDL_ttf/autogen.sh:
	hg clone -r 228 https://hg.libsdl.org/SDL_ttf/

SDL2/autogen.sh:
	git clone https://github.com/zielmicha/SDL2

freetype/autogen.sh: SDL_ttf/autogen.sh
	git clone git://github.com/LuaDist/freetype.git

Python:
	wget http://www.python.org/ftp/python/2.7.5/Python-2.7.5.tar.bz2 -O Python-2.7.tar.bz2
	tar xvf Python-2.7.tar.bz2
	mv Python-2.7.5 Python
