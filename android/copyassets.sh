A=project/obj/code
rm -r $A
mkdir -p $A
mkdir $A/lib
mkdir $A/lib/python2.7
echo > $A/lib/python2.7/site.py
cp ../lib/*.py ../lib/client/*.py $A/lib/python2.7
