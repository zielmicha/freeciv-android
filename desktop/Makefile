TARGETS=SDL_image/ SDL_ttf/ SDL2/ freetype/

all: getdep archs

archs: i386

i386:
	./buildarch.sh i386

amd64:
	./buildarch.sh amd64

getdep: $(addsuffix autogen.sh, $(TARGETS))

SDL_image/autogen.sh:
	hg clone -r 363 https://hg.libsdl.org/SDL_image/

SDL_ttf/autogen.sh:
	hg clone -r 228 https://hg.libsdl.org/SDL_ttf/

SDL2/autogen.sh:
	git clone https://github.com/zielmicha/SDL2

freetype/autogen.sh: SDL_ttf/autogen.sh
	git clone git://github.com/LuaDist/freetype.git
