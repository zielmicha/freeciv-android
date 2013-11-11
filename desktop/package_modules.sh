#!/bin/bash
STDMODULES="shutil stat os posixpath traceback linecache
types posixpath genericpath warnings fnmatch collections
functools threading httplib urllib string re UserDict _abcoll
abc copy_reg sre_compile sre_constants sre_parse keyword
heapq bisect random __future__ glob socket StringIO urlparse
mimetools tempfile rfc822 gzip struct io subprocess pickle
atexit encodings/__init__ encodings/ascii encodings/utf_8
encodings/aliases  encodings/hex_codec encodings/cp852
codecs SocketServer hashlib json/decoder json/encoder
json/__init__ json/scanner json/tool webbrowser shlex
base64 contextlib ssl textwrap tarfile weakref copy
_weakrefset code codeop"

WINMODULES="ntpath nturl2path"
STDMODULES="$STDMODULES $WINMODULES"

modules=""
for i in $STDMODULES; do
    modules="$modules $i.py"
done

path="$PWD/dist/modules.zip"
rm $path
winpath="$PWD/dist/winmodules.zip"
rm $winpath

pushd Python/Lib
zip $path $modules
popd

pushd ../lib
zip $path $(find -name '*.py')
popd

zip $path site.py
