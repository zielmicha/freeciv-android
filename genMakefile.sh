#!/bin/bash

set -e
SRC="freeciv-src"

PYTHON=python2.7 # python2.7_d
if [ "$PYTHON_INC" = "" ]; then
PYTHON_INC=/usr/include/$PYTHON
fi
CC_FLAGS="-g -Ipy_integration -Iclient -Iclient/include -Iclient/agents -Iclient/luascript -Icommon -Icommon/aicore -Icommon/scriptcore -Idependencies/cvercmp -Iutility -I$PYTHON_INC -I$SRC -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Iai -Iai/classic -Iai/default -Iai/stub -Iai/threaded -Idependencies/lua-5.3/src -Idependencies/tolua-5.2/include -DHAVE_CONFIG_H -fPIC $MY_CFLAGS"

export MKTMP="$PWD/$SRC/Makefile.tmp"
test -f "$MKTMP" && rm "$MKTMP"

output() {
    echo "$1" >> $MKTMP
}

ev=""
cev=""
sev=""
if [ -e src/callauto.c ]; then
    rm src/callauto.c
fi

output "CC_FLAGS_MORE="
output "CC_FLAGS=\$(CC_FLAGS_MORE) $CC_FLAGS"
output "CC=gcc"

pushd "$SRC"
ln -sf ../src py_integration
src_client=""
src_server=""
for name in common/*.c common/aicore/*.c common/scriptcore/*.c utility/*.c dependencies/lua-5.3/src/*.c dependencies/tolua-5.2/src/lib/*.c; do
    src_client="$src_client $name"
    src_server="$src_server $name"
    objfile=objectfiles/$(basename $name .c).o
    ev="$ev $objfile"
    output "$objfile: $name"
    output "	\$(CC) \$(CC_FLAGS) $additional -c -o $objfile $name"
done
for name in py_integration/callauto.c py_integration/*.c `ls -1 client/*.c|grep -v gui_` client/agents/*.c client/luascript/*.c dependencies/cvercmp/*.c; do
    src_client="$src_client $name"
    objfile=objectfiles/$(basename $name .c).o
    cev="$cev $objfile"
    output "$objfile: $name"
    output "	\$(CC) \$(CC_FLAGS) $additional -c -o $objfile $name"
done
for name in server/*.c server/generator/*.c server/scripting/*.c server/advisors/*.c ai/*.c ai/*/*.c; do
    src_server="$src_server $name"
    objfile=objectfiles/$(basename $name .c).o
    sev="$sev $objfile"
    output "$objfile: $name"
    output "	\$(CC) \$(CC_FLAGS) $additional -c -o $objfile $name"
done
popd

src_client=`echo $src_client|sed 's/\\//\\\\\\//g'`
src_server=`echo $src_server|sed 's/\\//\\\\\\//g'`
sed -e "s/LIST_OF_LOCAL_SRC_FILES/$src_client/g" src/Client.mk >$SRC/Android.mk
sed -e "s/LIST_OF_LOCAL_SRC_FILES/$src_server/g" src/Server.mk >android/project/jni/freeciv-server/Android.mk

echo "all: freecivclient.so freeciv-server" > $SRC/client.mk
echo "objectfiles_gen: $ev $cev $sev
" >> $SRC/client.mk
echo "freecivclient.so: $ev $cev
	\$(CC) -fPIC -shared -o freecivclient.so $ev $cev -lm -lz -l$PYTHON -lcurl -lSDL2_mixer $MY_LDFLAGS" >> $SRC/client.mk
echo "freeciv-server: $ev $sev
	\$(CC) -fPIC -pthread -o freeciv-server $ev $sev -lm -lz -l$PYTHON -lcurl $MY_LDFLAGS" >> $SRC/client.mk
echo "freecivclient.a: $ev $cev
	ar rcs freecivclient.a $ev $cev" >> $SRC/client.mk
echo "py_integration/callauto.c: py_integration/callglue
	python ../gencallglue.py" >> $SRC/client.mk
echo "clean:
	rm objectfiles/* freecivclient.so $SRC/callauto.c" >> $SRC/client.mk
cat $SRC/Makefile.tmp >> $SRC/client.mk
mv $SRC/client.mk $SRC/Makefile
rm "$MKTMP"
mkdir -p $SRC/objectfiles
