#!/bin/bash
TARGETS="SDL2 SDL_image freetype SDL_ttf"

if [ -z "$1" ]; then
    echo "usage: buildarch.sh [arch]"
    exit
fi

make getdep || exit 1

builddir="$PWD/build/$1/"

FLAGS_SDL2="--disable-input-tslib"
FLAGS_SDL_image="--with-sdl-prefix=$builddir"
FLAGS_SDL_ttf="--with-sdl-prefix=$builddir --with-freetype=$builddir"
FLAGS_python='CFLAGS="-fPIC" LDFLAGS="-fPIC" '

source "$1.sh" || exit 1
mkdir -p "$builddir"

MY_CFLAGS="$MY_CFLAGS=-fPIC"
MY_LDFLAGS="$MY_LDFLAGS -L$builddir/lib -fPIC"

for target in $TARGETS; do
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
    make install || exit 1

    popd
done

mkdir -p "$builddir/freeciv"
pushd "$builddir/freeciv" || exit 1
#PYTHON_INC=$builddir/include/python2.7
../../../../src/configure || exit 1
make -j4 || exit 1

cp ../../../../lib/Makefile lib.mk
if [ ! -e graphics.c ]; then
    cp -a ../../../../lib/graphics.c .
fi

$MY_CC graphics.c -o graphics.so -shared -Wall -lpython2.7 \
	-I/usr/include/python2.7 -I$builddir/include/SDL2 -L$builddir/lib \
	-fPIC -lSDL2 -lSDL2_image -lSDL2_ttf -fPIC || exit 1

popd
pushd "$builddir"

mkdir -p dist
cp freeciv/*.so dist
cp $(find lib/ -name '*.so.*' -type f) dist
cd dist
$MY_STRIP *.so*
tar czvf ../../../dist_"$1".tgz *.so*

popd
