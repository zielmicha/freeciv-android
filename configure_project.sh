#!/bin/bash

set -e

sdk_dir=/mnt/home/nosav/freeciv-workspace/sdk-tools-22.6.3
ndk_dir=/mnt/home/nosav/freeciv-workspace/android-ndk-r12b
api_ver=17
ndk_ver=r12b

already_configured=""
if [[ -e freeciv-2.6.0-beta1 ]] ; then
	echo "Will not overwrite" freeciv-2.6.0-beta1 "=> aborting"
	already_configured=1
fi
if [[ -e android/project/jni/SDL ]] ; then
	echo "Will not overwrite" android/project/jni/SDL "=> aborting"
	already_configured=1
fi
if [[ -e android/project/jni/SDL2_image ]] ; then
	echo "Will not overwrite" android/project/jni/SDL2_image "=> aborting"
	already_configured=1
fi
if [[ -e android/project/jni/SDL2_mixer ]] ; then
	echo "Will not overwrite" android/project/jni/SDL2_mixer "=> aborting"
	already_configured=1
fi
if [[ -e android/project/jni/SDL2_ttf ]] ; then
	echo "Will not overwrite" android/project/jni/SDL2_ttf "=> aborting"
	already_configured=1
fi
if [[ -e android/project/jni/python ]] ; then
	echo "Will not overwrite" android/project/jni/python "=> aborting"
	already_configured=1
fi
if [[ "$already_configured" ]] ; then
	exit
fi

wget -c http://files.freeciv.org/beta/freeciv-2.6.0-beta1.tar.bz2
sha256sum -c freeciv-2.6.0-SHA256SUM || exit 1
tar xjf freeciv-2.6.0-beta1.tar.bz2
(cd freeciv-2.6.0-beta1 && patch -p1 <../freeciv-2.6.0-beta1.patch)
ln -sf freeciv-2.6.0-beta1 freeciv-src

test -L pythonforandroid && rm pythonforandroid

# This command takes several minutes during first run, and installs a pythonforandroid distribution in your home directory.
# If you run this command again, it will re-use the installed distribution, so in case you want to reconfigure workspace from scratch, next runs will be much faster.
p4a symlink_dist --dist-name freeciv-android-jni-dependancies --sdk_dir "$sdk_dir" --ndk_dir "$ndk_dir" --android_api "$api_ver" --ndk_ver "$ndk_ver" --output pythonforandroid

echo "Copying JNI sources to android/project/jni/"
cp -r pythonforandroid/jni/SDL* android/project/jni/
(cd android/project/jni/SDL && patch -p1 <../../../../configure_project/SDL_modify_blending.patch)
mkdir android/project/jni/python
cp -r pythonforandroid/../../build/other_builds/python2/armeabi/python2/Python android/project/jni/python/
cp -r pythonforandroid/../../build/other_builds/python2/armeabi/python2/Modules android/project/jni/python/
cp -r pythonforandroid/../../build/other_builds/python2/armeabi/python2/Parser android/project/jni/python/
cp -r pythonforandroid/../../build/other_builds/python2/armeabi/python2/Objects android/project/jni/python/
cp -r pythonforandroid/../../build/other_builds/python2/armeabi/python2/Include android/project/jni/python/
cp -r pythonforandroid/../../build/other_builds/python2/armeabi/python2/pyconfig.h android/project/jni/python/
cp -r configure_project/python/* android/project/jni/python/

git submodule init; git submodule update

#echo "The pythonforandroid distribution is installed in" `readlink pythonforandroid`
#echo "If you want to save disk space, you can delete unuseful files by running: p4a clean_builds && p4a clean_download_cache"

