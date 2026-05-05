set -x


if [ "$1" = "clean" ]; then
    echo claen!
    make clean
    find . -name "*.gcda" -delete
    find . -name "*.gcno" -delete
elif [ "$1" = "run" ]; then
    echo run!
    ./bin/jap54

elif [ "$1" = "lcov" ]; then
    lcov --capture --directory . --rc lcov_branch_coverage=1 --output-file coverage.info --ignore-errors mismatch
    lcov --remove coverage.info '/usr/*' '*/gtest/*' --output-file coverage.info --ignore-errors unused
    genhtml coverage.info --output-directory html --ignore-errors mismatch --branch-coverage
else
    make 2>&1 | tee build.log 
    make install
    ctags -R .
fi
