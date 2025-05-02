






echo run
run() {
	echo test
}


set -x
if [ "$1" = "clean" ]; then # test
	make clean
elif [ "$1" = "run" ]; then
	./try
else 
	make

fi
