all: src lib
src:
	$(MAKE) -C src
lib:
	$(MAKE) -C lib
.PHONY: src lib
