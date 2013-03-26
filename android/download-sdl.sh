wget -c http://www.libsdl.org/tmp/SDL-2.0.tar.gz
mkdir _unpack
tar -C _unpack/ -xf SDL-2.0.tar.gz
mv _unpack/* project/jni/SDL
rmdir _unpack
