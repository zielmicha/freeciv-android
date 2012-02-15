android/build.sh || exit 1

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

rm bin/*.ap?.d
rm bin/*.ap?
(python2.7 build.py --dir ../public --private ../private \
	--package "$PKG_PACKAGE" --name "$PKG_NAME" \
	$PKG_ARG release \
	--numeric-version $RELEASE_VERSION_ID --version $RELEASE_VERSION 2>&1 ) || exit 1 # 

cd ../..
mv build/pygame/bin/${PKG_NAME_NOSPACE}-$RELEASE_VERSION-release.apk build/apk/
if [ "$1" = "install" ]; then
	./adb.sh uninstall ${PKG_PACKAGE}
	./adb.sh install -r build/apk/${PKG_NAME_NOSPACE}-$RELEASE_VERSION-release.apk
fi
