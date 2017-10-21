export LD_LIBRARY_PATH="/usr/local/lib:/usr/local/sdllib"
if [ "$1" = "" ]; then
	name=freeciv.main
else
	name="$1"
	shift
fi
PYTHONPATH=lib:freeciv-src $INSTRUMENT python -m "$name" "$@"
