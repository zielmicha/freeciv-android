for name in *.ruleset; do
	if [ ! -e  ../../old-data/nation/$name ]; then
		echo rm $name
		git rm $name
	fi
done
