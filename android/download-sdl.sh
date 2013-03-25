wget -c http://www.libsdl.org/tmp/SDL-1.3.tar.gz
mkdir _unpack
tar -C _unpack/ -xf SDL-1.3.tar.gz
mv _unpack/* project/jni/SDL
rmdir _unpack
