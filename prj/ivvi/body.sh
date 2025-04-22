set -x

if [ "$1" = "clean" ]; then
	make clean
elif [ "$1" = "run" ]; then
	shift
	echo ./ivvi  $*
	./ivvi bookmark.txt  $*
else
	make
fi 
