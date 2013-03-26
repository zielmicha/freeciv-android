all: build
build: builddep
	ndk-build -C project -j4
debugapk: build assets
	cd project; ant debug
debuginstall: debugapk
	cd project; ant installd

# ASSETS
assets: copyassets
	python archive.py project/obj/code > project/assets/code.archive
copyassets:
	./copyassets.sh

# DEPENDENCIES
builddep: project/jni/SDL/Android.mk project/jni/python/Android.mk
project/jni/SDL/Android.mk:
	./download-sdl.sh
../python4android/prepare.sh:
	cd ..; git submodule init; git submodule update
project/jni/python/Android.mk: ../python4android/prepare.sh
	cd ../python4android; ./prepare.sh
	mv ../python4android/build/jni project/jni/python
