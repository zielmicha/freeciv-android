all: src lib data
freeciv-src/data:
	# (old version) mirror of this file: https://cdn.atomshare.net/2738dc98073eb97c35f47d9b0d3b34decf783766ff7afbe08bded9092730b759/freeciv-2.6.0-beta1.tar.bz2
	wget -c http://files.freeciv.org/stable/freeciv-2.6.0.tar.bz2
	sha256sum -c freeciv-2.6-SHA256SUM || exit 1
	tar xjf freeciv-2.6.0.tar.bz2
	(cd freeciv-2.6.0 && patch -p1 <../freeciv-2.6.patch)
	ln -sf freeciv-2.6.0 freeciv-src
	make -C android project/jni/freeciv-client project/jni/freeciv-server
freeciv-src/Makefile: genMakefile.sh src/Client.mk src/Server.mk freeciv-src/data
	./genMakefile.sh
src/objectfiles:
	mkdir src/objectfiles

data: freeciv-src/data/misc/overlays_white.png freeciv-src/data/hexemplio/terrain_white.png freeciv-src/data/hexemplio/grid_white.png freeciv-src/data/amplio2/terrain1_white.png freeciv-src/data/amplio2/grid_white.png freeciv-src/data/trident/tiles_white.png freeciv-src/data/trident/grid_white.png
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
freeciv-src/data/trident/tiles_white.png: freeciv-src/data freeciv-src/data/trident/tiles.png
	python makemask.py freeciv-src/data/trident/tiles.png freeciv-src/data/trident/tiles_white.png
freeciv-src/data/trident/grid_white.png: freeciv-src/data freeciv-src/data/trident/grid.png
	python makemask.py freeciv-src/data/trident/grid.png freeciv-src/data/trident/grid_white.png

src: freeciv-src/Makefile src/objectfiles
	$(MAKE) -C freeciv-src
lib:
	$(MAKE) -C lib
run: all
	./main.sh freeciv.main $(ARG0) $(ARG1)

pythonforandroid:
	p4a symlink_dist --dist-name freeciv-android-jni-dependancies --android_api 17 --ndk_ver r12b --output pythonforandroid
android/project/jni/SDL:
	wget -c https://www.libsdl.org/release/SDL2-2.0.5.tar.gz
	tar xzf SDL2-2.0.5.tar.gz
	mv SDL2-2.0.5 android/project/jni/SDL
	(cd android/project/jni/SDL && patch -p1 <../../../../configure_project/SDL_modify_blending.patch)
	touch android/project/jni/SDL
android/project/jni/SDL2_image:
	wget -c https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.2.tar.gz
	tar xzf SDL2_image-2.0.2.tar.gz
	mv SDL2_image-2.0.2 android/project/jni/SDL2_image
	(cd android/project/jni/SDL2_image && patch -p1 <../../../../configure_project/SDL2_image.patch)
	touch android/project/jni/SDL2_image
android/project/jni/SDL2_ttf:
	wget -c https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.tar.gz
	tar xzf SDL2_ttf-2.0.14.tar.gz
	mv SDL2_ttf-2.0.14 android/project/jni/SDL2_ttf
	touch android/project/jni/SDL2_ttf
android/project/jni/SDL2_mixer:
	wget -c https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.1.tar.gz
	tar xzf SDL2_mixer-2.0.1.tar.gz
	mv SDL2_mixer-2.0.1 android/project/jni/SDL2_mixer
	(cd android/project/jni/SDL2_mixer && patch -p1 <../../../../configure_project/SDL2_mixer.patch)
	touch android/project/jni/SDL2_mixer
android/project/jni/python: pythonforandroid
	mkdir -p android/project/jni/python
	cp -r pythonforandroid/../../build/other_builds/python2/armeabi/python2/Python android/project/jni/python/
	cp -r pythonforandroid/../../build/other_builds/python2/armeabi/python2/Modules android/project/jni/python/
	cp -r pythonforandroid/../../build/other_builds/python2/armeabi/python2/Parser android/project/jni/python/
	cp -r pythonforandroid/../../build/other_builds/python2/armeabi/python2/Objects android/project/jni/python/
	cp -r pythonforandroid/../../build/other_builds/python2/armeabi/python2/Include android/project/jni/python/
	grep -v HAVE_GETSID pythonforandroid/../../build/other_builds/python2/armeabi/python2/pyconfig.h >android/project/jni/python/pyconfig.h
	cp -r configure_project/python/* android/project/jni/python/
	touch android/project/jni/python
android/project/jni/curl:
	# mirror of this file: https://cdn.atomshare.net/2b096f9387fb9b2be08d17e518c62b6537b1f4d4bb59111d5b4fa0272f383f66/curl-7.47.0.tar.bz2
	wget -c https://curl.haxx.se/download/curl-7.47.0.tar.bz2
	tar xjf curl-7.47.0.tar.bz2
	mv curl-7.47.0 android/project/jni/curl/
	cp -r configure_project/curl/* android/project/jni/curl/

pyjnius/jnius:
	git submodule init
	git submodule update

clean: freeciv-src/Makefile
	rm -rf freeciv-src/objectfiles/*

.PHONY: src lib run
