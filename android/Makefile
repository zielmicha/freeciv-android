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

build: cython project/jni/freeciv project/build.xml
	ndk-build -C project -j4

project/build.xml:
	android update project --path project --name "FreecivDebug" --target android-17

cython: project/jni/src/graphics.c project/jni/src/android.c project/jni/src/pyjnius.c

project/jni/src/pyjnius.c:
	./makejnius.sh

project/jni/freeciv:
	ln -sf ../../../src project/jni/freeciv
	(cd ../src && python ../gencallglue.py)

project/jni/src/graphics.c: ../lib/graphics.pyx
	make -C ../lib graphics.c
	cp ../lib/graphics.c project/jni/src/graphics.c

project/jni/src/android.c: ../lib/android.pyx
	cython ../lib/android.pyx -o project/jni/src/android.c

