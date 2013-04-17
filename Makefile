all: src lib data/techtree.index
src/Makefile:
	cd src; ./configure
src/objectfiles:
	mkdir src/objectfiles
data/techtree.index:
	cd data; python gentechtree.py | dot -Tplain > techtree.index
src: src/Makefile src/objectfiles
	$(MAKE) -C src
lib:
	$(MAKE) -C lib
run: all
	./main.sh freeciv.main $(ARG0) $(ARG1)
.PHONY: src lib run
