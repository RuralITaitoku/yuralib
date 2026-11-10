set -x

if [ "$1" = "run" ]; then
    echo --- run ---
    ./target/debug/jap54
elif [ "$1" = "clean" ]; then
    set +x
    echo --- clean ---
    set -x
    cargo clean
elif [ "$1" = "win" ]; then
    set +x
    echo --- win ---
    set -x
    cargo build --target x86_64-pc-windows-gnu
else
    cargo build | tee build.log 2>&1
fi
