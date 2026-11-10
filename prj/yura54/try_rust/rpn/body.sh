set -x


if [ "$1" = "run" ]; then
    shift
    cargo run $*
else
    cargo build
fi
