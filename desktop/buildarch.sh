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

source "$1.sh" || exit 1
mkdir -p "$builddir"

for target in $TARGETS; do
    pushd $PWD
    pushd $target || exit 1
    dir="$PWD"

    if [ ! -e good_configure ]; then
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
