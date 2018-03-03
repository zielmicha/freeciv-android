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
ls -1 project/libs/*/freeciv-server | while read exec_path ; do
	dirname=`dirname "$exec_path"`
	mkdir "$A/bin/`basename $dirname`"
	cp "$exec_path" "$A/bin/`basename $dirname`"
done
cp ../pyjnius/jnius/reflect.py $A/lib/python2.7/reflect.py
rm -r project/assets/fonts
mkdir project/assets/fonts
cp ../fonts/*.ttf project/assets/fonts
rm -r project/assets/data
mkdir project/assets/data

B=project/obj/res
rm -r $B
mkdir -p $B

(cd ../data; find -type d) | while read line; do
    mkdir -p $B/$line
    mkdir -p project/assets/data/$line
done
rmdir $B/flags
rm -r $B/themes

(cd ../data; find -type f) | while read line; do
    if [[ ! $line =~ ^\./(flags|themes)/.*$ ]] ; then
        if [[ $line =~ \.(tilespec|ruleset|spec|serv|lua|sav|sav.gz)$ ]]; then
            cp ../data/$line $B/$line || exit 1
        elif [[ $line =~ \.(png)$ ]]; then
            cp ../data/$line project/assets/data/$line || exit 1
        fi
    fi
done
cp ../data/civ2civ3/README.civ2civ3 $B/civ2civ3/
cp ../data/experimental/README.experimental $B/experimental/
mkdir -p project/assets/userdata
cp ../userdata/*.png ../userdata/*.jpg project/assets/userdata/
cp ../userdata/android-help.txt project/assets/userdata/
find $B/scenarios/ -type f -name "*.sav" -exec gzip "{}" \;
(cd ../data/flags && ../../../android/compose.py '*-large.png' shield ../../../android/project/assets/data/flags/large)
(cd ../data/flags && ../../../android/compose.py '*-shield-large.png' '' ../../../android/project/assets/data/flags/shield-large)
(cd ../data/flags && ../../../android/compose.py '*.png' shield,large ../../../android/project/assets/data/flags/flags)
(cd ../data/flags && ../../../android/compose.py '*-shield.png' large ../../../android/project/assets/data/flags/shield)
