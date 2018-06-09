VERSION=2604
VERSION_NAME=2.6.0-beta3

release: build/build.xml debug ndk dropboxdep
	cd build; ant release

debug:
	$(MAKE) -f Makefile

build:
	mkdir build

build/AndroidManifest.xml: build project/AndroidManifest.xml release.mk
	cat project/AndroidManifest.xml \
		| sed 's/pl.org.zielinscy.freeciv.debug/pl.org.zielinscy.freeciv/g' \
		| sed 's/Freeciv Debug/Freeciv/g' \
		| sed 's/versionCode="1"/versionCode="'$(VERSION)'"/g' \
		| sed 's/versionName="1.0"/versionName="'$(VERSION_NAME)'"/g' \
		| cat  >  build/AndroidManifest.xml

build/build.xml: build/AndroidManifest.xml _links
	"${ANDROIDSDK}/tools/android" update project --path build --name "Freeciv" --target android-17

dropboxdep: build/libs/commons-logging-1.1.1.jar build/libs/dropbox-android-sdk-1.5.4.jar build/libs/httpclient-4.0.3.jar build/libs/httpcore-4.0.1.jar build/libs/httpmime-4.0.3.jar build/libs/json_simple-1.1.jar

build/libs/%.jar: project/dropbox-sdk/lib/%.jar
	mkdir -p build/libs
	cp $^ $@

ndk:
	"${ANDROIDNDK}/ndk-build" -C build

_links: build build/src build/jni build/res build/obj build/assets

build/src:
	ln -sf ../project/src build/src
build/jni:
	ln -sf ../project/jni build/jni
build/res:
	ln -sf ../project/res build/res
build/obj:
	ln -sf ../project/obj build/obj
build/assets:
	ln -sf ../project/assets build/assets
