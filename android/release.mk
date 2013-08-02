VERSION=1103
VERSION_NAME=1.1.3

release: build/build.xml debug ndk
	cd build; ant release

debug:
	$(MAKE) -f Makefile

build:
	mkdir build

build/AndroidManifest.xml: build project/AndroidManifest.xml
	cat project/AndroidManifest.xml \
		| sed 's/pl.org.zielinscy.freeciv.debug/pl.org.zielinscy.freeciv/g' \
		| sed 's/Freeciv Debug/Freeciv/g' \
		| sed 's/versionCode="1"/versionCode="'$(VERSION)'"/g' \
		| sed 's/versionName="1.0"/versionName="'$(VERSION_NAME)'"/g' \
		| cat  >  build/AndroidManifest.xml

build/build.xml: build/AndroidManifest.xml _links
	android update project --path build --name "Freeciv" --target android-17

ndk:
	ndk-build -C build

_links: build build/src build/jni build/res build/obj build/assets

build/src:
	ln -sf $(PWD)/project/src build/src
build/jni:
	ln -sf $(PWD)/project/jni build/jni
build/res:
	ln -sf $(PWD)/project/res build/res
build/obj:
	ln -sf $(PWD)/project/obj build/obj
build/assets:
	ln -sf $(PWD)/project/assets build/assets
