all: src lib
src/Makefile:
	cd src; ./configure
src/objectfiles:
	mkdir src/objectfiles
src: src/Makefile src/objectfiles
	$(MAKE) -C src
lib:
	$(MAKE) -C lib
run: all
	./main.sh lib/main.py $(ARG0) $(ARG1)
g_test: all
	./main.sh lib/graphics_test.py
.PHONY: src lib run
