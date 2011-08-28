cd android

echo Building zlib...

mkdir build/zlib
ln -sf $PWD/../zlib-1.2.5 build/zlib/jni


cd build/zlib
ndk-build
cd ../..

cp -p build/zlib/libs/armeabi/* .