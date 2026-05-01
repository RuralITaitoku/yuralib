
if [ "$1" = "run" ]; then
	cargo run
elif [ "$1" = "clean" ]; then
	cargo clean
else 
	cargo build
fi
