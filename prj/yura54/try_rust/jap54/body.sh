


if [ "$1" = "run" ]; then
    echo --- run ---

else
    cargo build | tee build.log 2>&1
fi
