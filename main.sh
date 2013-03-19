export LD_LIBRARY_PATH="/usr/local/lib"
if [ "$1" = "" ]; then
	name=lib/main.py
else
	name="$1"
fi
PYTHONPATH=lib:src python "$name"
