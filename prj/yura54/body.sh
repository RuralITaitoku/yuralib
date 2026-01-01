set -x


if [ "$1" = "clean" ]; then
    echo claen!
    make clean
elif [ "$1" = "run" ]; then
    echo run!
else
    make
    make install
fi
