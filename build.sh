echo Configuring...
./download-dep || exit
./build-skel.sh || exit
cd server/
./configure || exit
cd ..
cd src/
./configure || exit
cd ..
echo Success
