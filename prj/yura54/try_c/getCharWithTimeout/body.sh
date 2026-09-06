
set -x

if [ "$1" = "run" ] ; then
    echo run
else
    gcc main.c -o a.out
fi
    
