

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
elif [ "$1" = "clean" ]; then
	rm -r build
else
	cmake -S src -B build
	cmake --build build
fi
