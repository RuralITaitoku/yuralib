echo run
run() {
	echo $*
	./try $*
}

echo clean
clean() {
	make clean
}

set -x
if [ "$1" = "clean" ]; then # test
	clean
elif [ "$1" = "run" ]; then
	shift 
	run $*
else 
	make
	make install
fi
