all: build
build: builddep
	ndk-build -C project -j4
debugapk: build
	cd project; ant debug
debuginstall: debugapk
	cd project; ant installd
builddep: project/jni/SDL/Android.mk project/jni/python/Android.mk
project/jni/SDL/Android.mk:
	./download-sdl.sh
python4android/prepare.sh:
	cd ..; git submodule init; git submodule update
project/jni/python/Android.mk: ../python4android/prepare.sh
	cd ../python4android; ./prepare.sh
	mv ../python4android/build/jni project/jni/python
