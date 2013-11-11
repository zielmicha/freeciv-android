#!/bin/bash
export PATH="/opt/mxe/usr/bin/:$PATH"
CONFIGURE_FLAGS='--host=i686-pc-mingw32'
MY_CC='i686-pc-mingw32-gcc'
MY_STRIP='i686-pc-mingw32-strip'
MY_RANLIB='i686-pc-mingw32-ranlib'
MY_LIBLOC=/opt/mxe/usr/i686-pc-mingw32/lib

FLAGS_SDL_ttf=""
FLAGS_SDL2='--disable-joystick --disable-render-d3d --disable-directx'
FLAGS_Python="--build=x86_64-unknown-linux-gnu"

win32_support() {
    mkdir -p "$builddir/freeciv"
    pushd "$builddir/freeciv" || exit 1

    export PYTHON_INC=/opt/mxe/Python27/include
    ../../../../src/configure || exit 1
    cp ../../../win_config.h config.h || exit 1
    make freecivclient.a -j4 CC=$MY_CC CC_FLAGS_MORE=-I. || exit 1
    $MY_RANLIB freecivclient.a

    cp -a ../../../../lib/graphics.c . || exit 1
    cython --embed ../../../main_win.pyx -o main.c || exit 1

    STATIC=$builddir/lib/lib
    PYLIB=/opt/mxe/Python27/libs

    $MY_CC graphics.c main.c -o graphics.bin \
	    -I$PYTHON_INC -I$builddir/include/SDL2 -L$builddir/lib \
	    ${STATIC}SDL2.a ${STATIC}SDL2_image.a ${STATIC}SDL2_ttf.a ${STATIC}freetype.a \
        $MY_LIBLOC/libjpeg.a $MY_LIBLOC/libpng.a \
        $builddir/freeciv/freecivclient.a $MY_LIBLOC/libbz2.a \
        -L$PYLIB -lpython27 \
        -lz -lm -lwsock32 -lgdi32 -lwinmm -lole32 -limm32 -lversion -luuid -loleaut32 \
        || exit 1
    $MY_STRIP graphics.bin
    target=../../../dist/freeciv_win32.exe
    rm $target
    cp graphics.bin $target
    popd
}

#$PYLIB/select.lib $PYLIB/_socket.lib $PYLIB/_ssl.lib \
#$PYLIB/bz2.lib $PYLIB/_hashlib.lib \
