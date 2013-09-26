#!/bin/bash
A=project/obj/code
rm -r $A
mkdir -p $A
mkdir $A/lib
mkdir $A/lib/python2.7
echo > $A/lib/python2.7/site.py
mkdir -p $A/lib/python2.7/freeciv/client
cp ../lib/*.py $A/lib/python2.7
cp ../lib/freeciv/*.py $A/lib/python2.7/freeciv
cp ../lib/freeciv/client/*.py $A/lib/python2.7/freeciv/client
echo 'array = str' > $A/lib/python2.7/array.py
STDMODULES="shutil stat os posixpath traceback linecache
types posixpath genericpath warnings fnmatch collections
functools threading httplib urllib string re UserDict _abcoll
abc copy_reg sre_compile sre_constants sre_parse keyword
heapq bisect random __future__ glob socket StringIO urlparse
mimetools tempfile rfc822 gzip struct io subprocess pickle
atexit encodings/__init__ encodings/ascii encodings/utf_8
encodings/aliases codecs"
mkdir $A/lib/python2.7/encodings
for mod in $STDMODULES; do
    cp ../python4android/Python-2.7/Lib/$mod.py $A/lib/python2.7/$mod.py || exit 1
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

(cd ../data; find -type f) | while read line; do
    if [[ $line =~ \.(tilespec|ruleset|spec|serv|lua|sav|sav.gz)$ ]]; then
        cp ../data/$line $B/$line || exit 1
    elif [[ $line =~ \.(png|jpg|index)|android-help.txt$ ]]; then
        cp ../data/$line project/assets/data/$line || exit 1
    fi
done
