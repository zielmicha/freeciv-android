TARGETS=SDL_image/ SDL_ttf/ SDL2/ freetype/
ARCH=$(shell ./getarch.sh)

all: getdep archs dist/module.zip dist/data.tgz

archs: $(ARCH)

i386: archdep
	./buildarch.sh i386

amd64: archdep
	./buildarch.sh amd64

archdep: getdep ../src/callauto.c

../src/callauto.c: ../src/Makefile
	make -C ../src callauto.c

../src/Makefile:
	cd ../src && ./configure

getdep: $(addsuffix autogen.sh, $(TARGETS)) Python

SDL_image/autogen.sh:
	hg clone -r 363 https://hg.libsdl.org/SDL_image/

SDL_ttf/autogen.sh:
	hg clone -r 228 https://hg.libsdl.org/SDL_ttf/

SDL2/autogen.sh:
	git clone https://github.com/zielmicha/SDL2

freetype/autogen.sh: SDL_ttf/autogen.sh
	git clone git://github.com/LuaDist/freetype.git

dist/module.zip: Python
	./package_modules.sh

dist/data.tgz:
	./package_data.sh

Python:
	wget http://www.python.org/ftp/python/2.7.5/Python-2.7.5.tar.bz2 -O Python-2.7.tar.bz2
	tar xvf Python-2.7.tar.bz2
	rm Python-2.7.tar.bz2
	mv Python-2.7.5 Python
