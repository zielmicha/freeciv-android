all: src lib data
freeciv-src/data:
	wget -c http://files.freeciv.org/beta/freeciv-2.6.0-beta1.tar.bz2
	sha256sum -c freeciv-2.6.0-SHA256SUM || exit 1
	tar xjf freeciv-2.6.0-beta1.tar.bz2
	(cd freeciv-2.6.0-beta1 && patch -p1 <../freeciv-2.6.0-beta1.patch)
	ln -sf freeciv-2.6.0-beta1 freeciv-src
	make -C android project/jni/freeciv-client project/jni/freeciv-server
freeciv-src/Makefile: genMakefile.sh src/Client.mk src/Server.mk freeciv-src/data
	./genMakefile.sh
src/objectfiles:
	mkdir src/objectfiles

data: freeciv-src/data/misc/overlays_white.png freeciv-src/data/hexemplio/terrain_white.png freeciv-src/data/hexemplio/grid_white.png freeciv-src/data/amplio2/terrain1_white.png freeciv-src/data/amplio2/grid_white.png
	ln -sf freeciv-src/data
freeciv-src/data/misc/overlays_white.png: freeciv-src/data freeciv-src/data/misc/overlays.png
	python makemask.py freeciv-src/data/misc/overlays.png freeciv-src/data/misc/overlays_white.png
freeciv-src/data/hexemplio/terrain_white.png: freeciv-src/data freeciv-src/data/hexemplio/terrain.png
	python makemask.py freeciv-src/data/hexemplio/terrain.png freeciv-src/data/hexemplio/terrain_white.png
freeciv-src/data/hexemplio/grid_white.png: freeciv-src/data freeciv-src/data/hexemplio/grid.png
	python makemask.py freeciv-src/data/hexemplio/grid.png freeciv-src/data/hexemplio/grid_white.png
freeciv-src/data/amplio2/terrain1_white.png: freeciv-src/data freeciv-src/data/amplio2/terrain1.png
	python makemask.py freeciv-src/data/amplio2/terrain1.png freeciv-src/data/amplio2/terrain1_white.png
freeciv-src/data/amplio2/grid_white.png: freeciv-src/data freeciv-src/data/amplio2/grid.png
	python makemask.py freeciv-src/data/amplio2/grid.png freeciv-src/data/amplio2/grid_white.png

src: freeciv-src/Makefile src/objectfiles
	$(MAKE) -C freeciv-src
lib:
	$(MAKE) -C lib
run: all
	./main.sh freeciv.main $(ARG0) $(ARG1)

pythonforandroid:
	p4a symlink_dist --dist-name freeciv-android-jni-dependancies --android_api 17 --ndk_ver r12b --output pythonforandroid
android/project/jni/SDL: pythonforandroid
	cp -r pythonforandroid/jni/SDL android/project/jni/
	(cd android/project/jni/SDL && patch -p1 <../../../../configure_project/SDL_modify_blending.patch)
	touch android/project/jni/SDL
android/project/jni/SDL2_image: pythonforandroid
	cp -r pythonforandroid/jni/SDL2_image android/project/jni/
	touch android/project/jni/SDL2_image
android/project/jni/SDL2_ttf: pythonforandroid
	cp -r pythonforandroid/jni/SDL2_ttf android/project/jni/
	touch android/project/jni/SDL2_ttf
android/project/jni/SDL2_mixer: pythonforandroid
	cp -r pythonforandroid/jni/SDL2_mixer android/project/jni/
	touch android/project/jni/SDL2_mixer
android/project/jni/python: pythonforandroid
	mkdir -p android/project/jni/python
	cp -r pythonforandroid/../../build/other_builds/python2/armeabi/python2/Python android/project/jni/python/
	cp -r pythonforandroid/../../build/other_builds/python2/armeabi/python2/Modules android/project/jni/python/
	cp -r pythonforandroid/../../build/other_builds/python2/armeabi/python2/Parser android/project/jni/python/
	cp -r pythonforandroid/../../build/other_builds/python2/armeabi/python2/Objects android/project/jni/python/
	cp -r pythonforandroid/../../build/other_builds/python2/armeabi/python2/Include android/project/jni/python/
	cp -r pythonforandroid/../../build/other_builds/python2/armeabi/python2/pyconfig.h android/project/jni/python/
	cp -r configure_project/python/* android/project/jni/python/
	touch android/project/jni/python
android/project/jni/curl:
	wget -c https://curl.haxx.se/download/curl-7.47.0.tar.bz2
	tar xjf curl-7.47.0.tar.bz2
	mv curl-7.47.0 android/project/jni/curl/
	cp -r configure_project/curl/* android/project/jni/curl/

pyjnius/jnius:
	git submodule init
	git submodule update

.PHONY: src lib run
