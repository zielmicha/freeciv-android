android/build.sh

cd android

cp -r ../fonts build/public
cp ../lib/*.py build/public
mkdir build/public/client/
cp ../lib/client/*.py build/public/client/
rm -r build/public/data
tar czf build/public/data.tgz ../data
mkdir build/public/saves
cp -p freecivserver build/private/lib/freecivserver
cp -p libfreecivclient.so build/private/lib/freecivclient.so
cp -p libpyjni.so build/private/lib/pyjni.so

. info.sh
cd build/pygame

export PATH="$PATH:$ANDROID_PATH"

(python2.7 build.py --dir ../public --private ../private \
	--package "$PKG_PACKAGE.debug" --name "$PKG_NAME Debug" \
	$PKG_ARG debug \
	--numeric-version 90 --version 0.9.0 2>&1 ) || exit 1 # 

cd ../..
mv build/pygame/bin/${PKG_NAME_NOSPACE}Debug-0.9.0-debug.apk build/apk/
if [ "$1" = "install" ]; then
	./adb.sh install -r build/apk/${PKG_NAME_NOSPACE}Debug-0.9.0-debug.apk
fi
