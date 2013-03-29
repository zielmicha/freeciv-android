A=project/obj/code
rm -r $A
mkdir -p $A
mkdir $A/lib
mkdir $A/lib/python2.7
echo > $A/lib/python2.7/site.py
cp ../lib/*.py $A/lib/python2.7
mkdir $A/lib/python2.7/client
cp ../lib/client/*.py $A/lib/python2.7/client
echo 'array = str' > $A/lib/python2.7/array.py
STDMODULES="shutil stat os posixpath traceback linecache
types posixpath genericpath warnings fnmatch collections
functools threading httplib urllib string re UserDict _abcoll
abc copy_reg sre_compile sre_constants sre_parse keyword
heapq bisect random __future__ glob socket StringIO urlparse
mimetools tempfile rfc822 gzip struct io subprocess pickle"
for mod in $STDMODULES; do
    cp ../python4android/Python-2.7/Lib/$mod.py $A/lib/python2.7 || exit 1
done
rm -r project/assets/fonts
mkdir project/assets/fonts
cp ../fonts/*.ttf project/assets/fonts
rm -r project/assets/data
cp ../data -a project/assets
true