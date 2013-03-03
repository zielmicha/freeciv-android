echo Configuring...
./download-dep || exit
./build-skel.sh || exit
cd src/
./configure || exit
cd ..
echo Success
