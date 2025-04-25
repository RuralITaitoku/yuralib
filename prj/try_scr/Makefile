CC := g++


SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, build/%.o, $(SRCS))

all: try

build:
	mkdir -p build

try: $(OBJS)
	$(CC) -o $@ $(OBJS)


build/%.o : src/%.cpp | build
	$(CC) -c $< -o $@ -I./include

clean:
	rm -r build
