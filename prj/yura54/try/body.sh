set -x

if [ "$1" = "clean" ]; then
    rm ./try
elif [ "$1" = "run" ]; then
    ./try
else
    g++ 20260314_term.cpp -o try
fi
