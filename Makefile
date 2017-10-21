all: src lib freeciv-src/data
freeciv-src/Makefile: genMakefile.sh src/Client.mk src/Server.mk
	./genMakefile.sh
src/objectfiles:
	mkdir src/objectfiles

freeciv-src/data: freeciv-src/data/misc/overlays_white.png freeciv-src/data/hexemplio/terrain_white.png freeciv-src/data/hexemplio/grid_white.png freeciv-src/data/amplio2/terrain1_white.png freeciv-src/data/amplio2/grid_white.png
	ln -sf freeciv-src/data
freeciv-src/data/misc/overlays_white.png: freeciv-src/data/misc/overlays.png
	python makemask.py freeciv-src/data/misc/overlays.png freeciv-src/data/misc/overlays_white.png
freeciv-src/data/hexemplio/terrain_white.png: freeciv-src/data/hexemplio/terrain.png
	python makemask.py freeciv-src/data/hexemplio/terrain.png freeciv-src/data/hexemplio/terrain_white.png
freeciv-src/data/hexemplio/grid_white.png: freeciv-src/data/hexemplio/grid.png
	python makemask.py freeciv-src/data/hexemplio/grid.png freeciv-src/data/hexemplio/grid_white.png
freeciv-src/data/amplio2/terrain1_white.png: freeciv-src/data/amplio2/terrain1.png
	python makemask.py freeciv-src/data/amplio2/terrain1.png freeciv-src/data/amplio2/terrain1_white.png
freeciv-src/data/amplio2/grid_white.png: freeciv-src/data/amplio2/grid.png
	python makemask.py freeciv-src/data/amplio2/grid.png freeciv-src/data/amplio2/grid_white.png

src: freeciv-src/Makefile src/objectfiles
	$(MAKE) -C freeciv-src
lib:
	$(MAKE) -C lib
run: all
	./main.sh freeciv.main $(ARG0) $(ARG1)
.PHONY: src lib run
