
set -x
if [ "$1" = "run" ]; then
	echo run
	cd build
	./run
elif [ "$1" = "cap" ]; then
	cd ./build/try-cv-241215
	./try-cv
elif [ "$1" = "lap" ]; then
	cd ./build/try-lap-250102
	./try-lap
elif [ "$1" = "task" ]; then
	cd ./build/try-task-250105
	./try-task
elif [ "$1" = "rnd" ]; then
	cd ./build/try-rnd-250111
	./try-rnd
elif [ "$1" = "gtest" ]; then
	cd ./build/250118-try-gtest
	./try-gtest
elif [ "$1" = "u" ]; then
	cd ./build/250125-try-utf8
	./try-utf8lines
elif [ "$1" = "clean" ]; then
	rm -r build
else
	cmake -S src -B build
	cmake --build build
fi
