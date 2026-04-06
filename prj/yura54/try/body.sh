set -x

if [ "$1" = "clean" ]; then
    rm ./try
elif [ "$1" = "run" ]; then
    ./try
else
    g++ async_get_char.cpp -o try
fi
