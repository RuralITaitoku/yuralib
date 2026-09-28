


if [ "$1" = "run" ]; then
    echo --- run ---
    ./target/debug/jap54
elif [ "$1" = "clean" ]; then
    echo --- clean ---
    cargo clean
else
    cargo build | tee build.log 2>&1
fi
