all: src lib
src:
	$(MAKE) -C src
lib:
	$(MAKE) -C lib
run: all
	./main.sh lib/main.py $(ARG0) $(ARG1)
g_test: all
	./main.sh lib/graphics_test.py
.PHONY: src lib run
