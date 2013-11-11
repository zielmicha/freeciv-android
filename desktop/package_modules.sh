#!/bin/bash
STDMODULES="shutil stat os posixpath traceback linecache
types posixpath genericpath warnings fnmatch collections
functools threading httplib urllib string re UserDict _abcoll
abc copy_reg sre_compile sre_constants sre_parse keyword
heapq bisect random __future__ glob socket StringIO urlparse
mimetools tempfile rfc822 gzip struct io subprocess pickle
atexit encodings/__init__ encodings/ascii encodings/utf_8
encodings/aliases codecs SocketServer hashlib json/decoder
json/encoder json/__init__ json/scanner json/tool webbrowser
shlex base64 contextlib ssl textwrap"

modules=""
for i in $STDMODULES; do
    modules="$modules $i.py"
done

path="$PWD/dist/modules.zip"
rm $path

pushd Python/Lib
zip $path $modules
popd
