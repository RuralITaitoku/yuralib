set -x


if [ "$1" = "clean" ]; then
    echo claen!
    make clean
    find . -name "*.gcda" -delete
    find . -name "*.gcno" -delete
elif [ "$1" = "run" ]; then
    echo run!
elif [ "$1" = "lcov" ]; then
    lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch
    lcov --remove coverage.info '/usr/*' '*/gtest/*' --output-file coverage.info --ignore-errors unused
    genhtml coverage.info --output-directory html --ignore-errors mismatch
else
    make
    make install
    ctags -R .
fi
