#!/bin/bash
TARGETS="SDL2 SDL_image freetype SDL_ttf Python"

if [ -z "$1" ]; then
    echo "usage: buildarch.sh [arch]"
    exit
fi

make getdep || exit 1

builddir="$PWD/build/$1/"

mkdir -p dist

source "$1.sh" || exit 1

FLAGS_SDL2="--disable-input-tslib --disable-dbus --enable-static $FLAGS_SDL2"
FLAGS_SDL_image="--with-sdl-prefix=$builddir --disable-jpg-shared --disable-png-shared $FLAGS_SDL_image"
FLAGS_SDL_ttf="--with-sdl-prefix=$builddir --with-freetype=$builddir --with-freetype-prefix=$builddir $FLAGS_SDL_ttf"
FLAGS_python='CFLAGS="-fPIC" LDFLAGS="-fPIC" '"$FLAGS_python"

mkdir -p "$builddir"

MY_CFLAGS="$MY_CFLAGS=-fPIC"
MY_LDFLAGS="$MY_LDFLAGS -L$builddir/lib -fPIC"

cp Setup Python/Modules/Setup
mkdir -p "$builddir/Python/Modules"
cp Setup $builddir/Python/Modules/Setup

for target in $TARGETS; do
    if [ "$target" = Python -a $1 = win32 ]; then
        # Python is stupid and doesn't support cross-compilation
        continue
    fi
    pushd $PWD
    pushd $target || exit 1
    dir="$PWD"

    if [ ! \( -e good_configure -o \( -e configure -a ! -e autogen.sh \) \) ]; then
        ./autogen.sh --help || exit 1
        touch good_configure
    fi
    popd
    mkdir -p "$builddir/$target"
    cd "$builddir/$target" || exit 1
    if [ ! -e Makefile ]; then
        "$dir/configure" $CONFIGURE_FLAGS $(eval 'echo $FLAGS_'$target) \
            --prefix=$builddir || exit 1
    fi

    make -j4 || exit 1
    if [ "$SKIPINSTALL" = "" ]; then
        make install || exit 1
    fi

    popd
done

if [ $1 = win32 ]; then
    win32_support
    exit $?
fi

# Build _io module

pushd "$builddir/Python"
io_build_dir=$(dirname "$(find -name iobase.o)")
ar rcs _io.a $io_build_dir/*.o || exit 1
popd

mkdir -p "$builddir/freeciv"
pushd "$builddir/freeciv" || exit 1
export PYTHON_INC=$builddir/include/python2.7
../../../../src/configure || exit 1
make -j4 || exit 1
make freecivclient.a || exit 1

cp ../../../../lib/Makefile lib.mk
if [ ! -e graphics.c ]; then
    cp -a ../../../../lib/graphics.c .
fi

cython --embed ../../../main.pyx -o main.c || exit

STATIC=$builddir/lib/lib

$MY_CC graphics.c main.c ../Python/_io.a -o graphics.bin \
	-I$PYTHON_INC -I$builddir/include/SDL2 -L$builddir/lib \
	${STATIC}SDL2.a ${STATIC}SDL2_image.a ${STATIC}SDL2_ttf.a ${STATIC}freetype.a \
    ${STATIC}python2.7.a $MY_LIBLOC/libjpeg.a $MY_LIBLOC/libpng.a \
    $builddir/freeciv/freecivclient.a \
    -lbz2 -lX11 -lssl -lcrypto -lz -lm -lutil -ldl \
    -pthread -lpthread \
    || exit 1

$MY_STRIP graphics.bin

target=../../../dist/freeciv_$1
rm $target
cp graphics.bin $target
popd


pushd "$builddir"
popd
