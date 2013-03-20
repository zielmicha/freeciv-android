all: src lib
src:
	$(MAKE) -C src
lib:
	$(MAKE) -C lib
run: all
	./main.sh
g_test: all
	./main.sh lib/graphics_test.py
.PHONY: src lib run
