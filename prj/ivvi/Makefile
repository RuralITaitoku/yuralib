
CPP=g++
CPPFLAGS= -g -Wall -DDEBUG  -I./include/ -std=c++17

#LIB_SRCS = $(wildcard lib/*.cpp)
#LIB_OBJS = $(LIB_SRCS:.cpp=.o)


#libruralis2.so : $(LIB_OBJS)
#	ar rcs $@ $^



SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, build/%.o, $(SRCS))



all: ivvi


ivvi: $(OBJS)
	g++ -o $@ $(OBJS) 

build/%.o: src/%.cpp | build
	$(CPP) $(CPPFLAGS) -o $@ -c $<

# $(OBJS): $(SRCS) | build

build:
	mkdir -p build


clean:
	rm -r build
