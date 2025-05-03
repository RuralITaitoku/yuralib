






echo run
run() {
	./try
}

echo clean
clean() {
	make clean
}

set -x
if [ "$1" = "clean" ]; then # test
	clean
elif [ "$1" = "run" ]; then
	run
else 
	make

fi
