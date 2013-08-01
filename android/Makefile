all: build assets

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

setupemulator:
	adb shell stop
	adb shell setprop dalvik.vm.checkjni false
	adb shell setprop log.redirect-stdio true
	adb shell start

# ASSETS
assets: copyassets
	cd project/obj/code; ziptar cf --zip ../../assets/code.archive .
	cd project/obj/res; ziptar cf --zip ../../assets/res.archive .
copyassets:
	./copyassets.sh

# BUILD

build: builddep cython project/jni/freeciv project/build.xml
	ndk-build -C project -j4

project/build.xml:
	android update project --path project --name "FreecivDebug" --target android-17

cython: project/jni/src/android.c project/jni/src/pyjnius.c

project/jni/src/pyjnius.c:
	./makejnius.sh

project/jni/freeciv:
	ln -sf $(PWD)/../src project/jni/freeciv

project/jni/src/graphics.c: ../lib/graphics.pyx
	make -C ../lib graphics.c
	cp ../lib/graphics.c project/jni/src/graphics.c

project/jni/src/android.c: ../lib/android.pyx
	cython ../lib/android.pyx -o project/jni/src/android.c

# DEPENDENCIES

builddep: project/jni/python/Android.mk

submodules: ../python4android/prepare.sh

../python4android/prepare.sh:
	cd ..; git submodule init; git submodule update

project/jni/python/Android.mk: ../python4android/prepare.sh
	cd ../python4android; ./prepare.sh
	mv ../python4android/build/jni project/jni/python
