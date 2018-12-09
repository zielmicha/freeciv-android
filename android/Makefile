all: build javadep assets

release:
	cat project/AndroidManifest.xml \
		| sed 's/pl.org.zielinscy.freeciv.debug/pl.org.zielinscy.freeciv/g' \
		| sed 's/Freeciv Debug/Freeciv/g' \
		| sed 's/versionCode="1"/versionCode="'`grep 'version = ....' ../lib/freeciv/sync.py|grep -o '[[:digit:]]*'`'"/g' \
		| sed 's/versionName="1.0"/versionName="'`grep '#define VERSION_STRING .[.[:digit:]]*' ../src/fc_config.h|grep -o '[.[:digit:]]*'`'"/g' \
		| cat > project/src/main/AndroidManifest.xml
	./gradlew assembleRelease

debugapk: all
	cp project/AndroidManifest.xml project/src/main/AndroidManifest.xml
	./gradlew assembleDebug
#debuginstall: all
#	./gradlew installDebug
#debugrun: debuginstall
#	$(MAKE) run
run:
	adb shell am start -n pl.org.zielinscy.freeciv.debug/org.libsdl.app.SDLActivity
#debugrunlog: debuginstall
#	$(MAKE) runlog
runlog: run
	./adb.py

# JAVA

javadep: dropboxdep

dropboxdep: project/libs/commons-logging-1.1.1.jar project/libs/dropbox-android-sdk-1.5.4.jar project/libs/httpclient-4.0.3.jar project/libs/httpcore-4.0.1.jar project/libs/httpmime-4.0.3.jar project/libs/json_simple-1.1.jar

project/libs/%.jar: project/dropbox-sdk/lib/%.jar
	mkdir -p project/libs
	cp $^ $@

# ASSETS
assets: copyassets
	python archive.py project/obj/code > project/src/main/assets/code.archive
	python archive.py project/obj/res > project/src/main/assets/res.archive
copyassets:
	./copyassets.sh

# BUILD

build: cython project/jni/freeciv-client project/jni/freeciv-server
	(cd .. && make data freeciv-src/Makefile pythonforandroid android/project/jni/SDL android/project/jni/SDL2_image android/project/jni/SDL2_ttf android/project/jni/SDL2_mixer android/project/jni/python android/project/jni/curl)
	(cd ../freeciv-src && make py_integration/callauto.c)
	mkdir -p project/src/main/java/org/libsdl/app
	rm project/src/main/java/org/libsdl/app/* || true
	cp project/jni/SDL/android-project/app/src/main/java/org/libsdl/app/*.java project/src/main/java/org/libsdl/app/
	cat project/jni/SDL/android-project/app/src/main/java/org/libsdl/app/SDLActivity.java | sed 's/protected static SDLActivity mSingleton/public static SDLActivity mSingleton/g' \
		| sed 's/.. "SDL2_image"/"SDL2_image"/g' | sed 's/.. "SDL2_mixer"/"SDL2_mixer"/g' | sed 's/.. "SDL2_ttf"/"SDL2_ttf", "python2.7", "freeciv-client"/g' \
		>project/src/main/java/org/libsdl/app/SDLActivity.java
	"${ANDROID_NDK_HOME}/ndk-build" -C project -j4 freeciv-server
	`ls -1 ${ANDROID_NDK_HOME}/toolchains/arm-linux-androideabi*/prebuilt/*/bin/*strip|head -n 1` --strip-unneeded project/obj/local/armeabi/freeciv-server
	`ls -1 ${ANDROID_NDK_HOME}/toolchains/arm-linux-androideabi*/prebuilt/*/bin/*strip|head -n 1` --strip-unneeded project/obj/local/armeabi-v7a/freeciv-server
	`ls -1 ${ANDROID_NDK_HOME}/toolchains/x86-*/prebuilt/*/bin/*strip|head -n 1` --strip-unneeded project/obj/local/x86/freeciv-server

cython: project/jni/src/graphics.c project/jni/src/android.c project/jni/src/pyjnius.c

project/jni/src/pyjnius.c:
	(cd .. && make pyjnius/jnius)
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

