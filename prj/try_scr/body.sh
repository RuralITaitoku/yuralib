

if [ "$1" = "run" ]; then

    echo run

elif [ "$1" = "clean" ]; then
    make clean
else 
    make 
fi