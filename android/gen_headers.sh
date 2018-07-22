#!/bin/sh

FREECIV_DIR=freeciv-2.6.0
FREECIV_TARBALL=$FREECIV_DIR.tar.bz2
# This script runs Freeciv's ./configure script in Android, to generate fc_config.h and freeciv_config.h
# You need about 500 MB of free space in your Android device, but you can delete it after the headers have been generated.
# Run this file on an Android device :
# - install Termux from Google Play
# - Open Termux and copy this file to the termux home directory:
#		cp /storage/sdcard0/gen_headers.sh .
# - Optional: also copy $FREECIV_TARBALL to the termux home directory if you want to avoid downloading it again
# - Run: sh gen_headers.sh

set -e

echo Installing dependancies...
pkg install clang pkg-config libcurl-dev

wget -c http://files.freeciv.org/stable/$FREECIV_TARBALL || true
echo "7c20399198d6c7d846fed9a69b02e01134ae5340a3ae0f99d1e38063ade6c999  $FREECIV_TARBALL" | sha256sum -c -
echo Extracting...
tar xjf $FREECIV_TARBALL

(cd $FREECIV_DIR && ./configure --enable-client=stub --enable-fcmp=no)
echo >>$FREECIV_DIR/gen_headers/fc_config.h
echo '#define BINDIR "/notexisting"' >>$FREECIV_DIR/gen_headers/fc_config.h

echo "fc_config.h and freeciv_config.h have been generated in $FREECIV_DIR/gen_headers"
echo "Copy them to external storage and then to your computer (the 'src' folder in your workspace)."
echo "For example, type: cp $FREECIV_DIR/gen_headers/*.h /storage/sdcard0/"

