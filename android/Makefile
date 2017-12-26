all: build javadep assets

release:
	$(MAKE) -f release.mk

debugapk: all
	cd project; ant debug
debuginstall: debugapk
	cd project; ant installd
debugrun: debuginstall
	$(MAKE) run
run:
	adb shell am start -n pl.org.zielinscy.freeciv.debug/org.libsdl.app.SDLActivity
debugrunlog: debuginstall
	$(MAKE) runlog
runlog: run
	./adb.py

# JAVA

javadep: dropboxdep

dropboxdep: project/libs/commons-logging-1.1.1.jar project/libs/dropbox-android-sdk-1.5.4.jar project/libs/httpclient-4.0.3.jar project/libs/httpcore-4.0.1.jar project/libs/httpmime-4.0.3.jar project/libs/json_simple-1.1.jar

project/libs/%.jar: project/dropbox-sdk/lib/%.jar
	cp $^ $@

# ASSETS
assets: copyassets
	python archive.py project/obj/code > project/assets/code.archive
	python archive.py project/obj/res > project/assets/res.archive
copyassets:
	./copyassets.sh

# BUILD

build: cython project/jni/freeciv-client project/jni/freeciv-server project/build.xml
	(cd .. && make freeciv-src/data freeciv-src/Makefile pythonforandroid android/project/jni/SDL android/project/jni/SDL2_image android/project/jni/SDL2_ttf android/project/jni/SDL2_mixer android/project/jni/python pyjnius android/project/jni/curl)
	(cd ../freeciv-src && make py_integration/callauto.c)
	"${ANDROIDNDK}/ndk-build" -C project -j4

project/build.xml:
	"${ANDROIDSDK}/tools/android" update project --path project --name "FreecivDebug" --target android-17

cython: project/jni/src/graphics.c project/jni/src/android.c project/jni/src/pyjnius.c

project/jni/src/pyjnius.c:
	./makejnius.sh

project/jni/freeciv-client:
	ln -sf ../../../freeciv-src project/jni/freeciv-client
project/jni/freeciv-server:
	mkdir -p project/jni/freeciv-server
	ln -sf ../../../../freeciv-src/ai project/jni/freeciv-server/ai
	ln -sf ../../../../freeciv-src/common project/jni/freeciv-server/common
	ln -sf ../../../../freeciv-src/dependencies project/jni/freeciv-server/dependencies
	ln -sf ../../../../src/fc_config.h project/jni/freeciv-server/fc_config.h
	ln -sf ../../../../src/freeciv_config.h project/jni/freeciv-server/freeciv_config.h
	ln -sf ../../../../freeciv-src/server project/jni/freeciv-server/server
	ln -sf ../../../../freeciv-src/utility project/jni/freeciv-server/utility

project/jni/src/graphics.c: ../lib/graphics.pyx
	make -C ../lib graphics.c
	cp ../lib/graphics.c project/jni/src/graphics.c

project/jni/src/android.c: ../lib/android.pyx
	cython ../lib/android.pyx -o project/jni/src/android.c

