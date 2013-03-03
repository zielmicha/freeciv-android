mkdir src/objectfiles
mkdir android/build/apk

PYGAME_SUBSET=android/build/pygame/libs/armeabi
cp $PYGAME_SUBSET/libsdl.so $PYGAME_SUBSET/libpython2.7.so android/build
cp $PYGAME_SUBSET/libsdl.so $PYGAME_SUBSET/libpython2.7.so android
