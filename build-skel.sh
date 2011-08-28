ln -sf $PWD/src/utility server
ln -sf $PWD/src/common server
mkdir src/objectfiles
mkdir server/objectfiles
mkdir android/build/apk

PYGAME_SUBSET=android/build/pygame/libs/armeabi
cp $PYGAME_SUBSET/libsdl.so $PYGAME_SUBSET/libpython2.7.so android/build
cp $PYGAME_SUBSET/libsdl.so $PYGAME_SUBSET/libpython2.7.so android
