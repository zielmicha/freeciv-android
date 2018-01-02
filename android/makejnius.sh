mkdir -p project/obj/jnius
rm -r project/obj/jnius
cp -r ../pyjnius/jnius/ project/obj/jnius
echo 'DEF JNIUS_PLATFORM = "android"' > project/obj/jnius/config.pxi
find project/obj/jnius -name '*.pxi' | while read name; do
    sed -i 's/from .reflect/from reflect/g' "$name"
done
cython project/obj/jnius/jnius.pyx -o project/jni/src/pyjnius.c
