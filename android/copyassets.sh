#!/bin/bash
A=project/obj/code
rm -r $A
mkdir -p $A
mkdir $A/lib
mkdir $A/lib/python2.7
mkdir -p $A/lib/python2.7/freeciv/client
mkdir -p $A/lib/python2.7/ui
cp ../lib/*.py $A/lib/python2.7
cp ../lib/freeciv/*.py $A/lib/python2.7/freeciv
cp ../lib/ui/*.py $A/lib/python2.7/ui
cp ../lib/freeciv/client/*.py $A/lib/python2.7/freeciv/client
echo 'array = str' > $A/lib/python2.7/array.py
STDMODULES="shutil stat os posixpath traceback linecache
types posixpath genericpath warnings fnmatch collections
functools threading httplib urllib string re UserDict _abcoll
abc copy_reg sre_compile sre_constants sre_parse keyword
heapq bisect random __future__ glob socket StringIO urlparse
mimetools tempfile rfc822 gzip struct io subprocess pickle
atexit encodings/__init__ encodings/ascii encodings/utf_8
encodings/aliases encodings/hex_codec encodings/string_escape
hashlib weakref _weakrefset codecs SocketServer platform"
mkdir $A/lib/python2.7/encodings
for mod in $STDMODULES; do
    cp ../pythonforandroid/python-install/lib/python2.7/$mod.py $A/lib/python2.7/$mod.py || exit 1
done

# Copy the freeciv-server executables
mkdir $A/bin
ls -1 project/obj/local/*/freeciv-server | while read exec_path ; do
	dirname=`dirname "$exec_path"`
	mkdir "$A/bin/`basename $dirname`"
	cp "$exec_path" "$A/bin/`basename $dirname`"
done
cp ../pyjnius/jnius/reflect.py $A/lib/python2.7/reflect.py
rm -r project/src/main/assets/fonts
mkdir project/src/main/assets/fonts
cp ../fonts/*.ttf project/src/main/assets/fonts
rm -r project/src/main/assets/data
mkdir project/src/main/assets/data

B=project/obj/res
rm -r $B
mkdir -p $B

(cd ../data; find -type d) | while read line; do
    mkdir -p $B/$line
    mkdir -p project/src/main/assets/data/$line
done
rmdir $B/flags
rm -r $B/themes

(cd ../data; find -type f) | while read line; do
    if [[ ! $line =~ ^\./(flags|themes)/.*$ ]] ; then
        if [[ $line =~ \.(tilespec|ruleset|spec|serv|lua|sav|sav.gz)$ ]]; then
            cp ../data/$line $B/$line || exit 1
        elif [[ $line =~ \.(png)$ ]]; then
            cp ../data/$line project/src/main/assets/data/$line || exit 1
        fi
    fi
done
cp ../data/civ2civ3/README.civ2civ3 $B/civ2civ3/
cp ../data/experimental/README.experimental $B/experimental/
mkdir -p project/src/main/assets/userdata
cp ../userdata/*.png ../userdata/*.jpg project/src/main/assets/userdata/
mv project/src/main/assets/userdata/water*.png project/src/main/assets/data/hexemplio/
cp ../userdata/android-help.txt project/src/main/assets/userdata/
find $B/scenarios/ -type f -name "*.sav" -exec gzip "{}" \;
(cd ../data/flags && ../../../android/compose.py '*-large.png' shield ../../../android/project/src/main/assets/data/flags/large)
(cd ../data/flags && ../../../android/compose.py '*-shield-large.png' '' ../../../android/project/src/main/assets/data/flags/shield-large)
(cd ../data/flags && ../../../android/compose.py '*.png' shield,large ../../../android/project/src/main/assets/data/flags/flags)
(cd ../data/flags && ../../../android/compose.py '*-shield.png' large ../../../android/project/src/main/assets/data/flags/shield)
