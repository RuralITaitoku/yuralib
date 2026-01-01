
# CPP=clang++
CPP=g++
CPPFLAGS= -g -Wall -DDEBUG  -I./include/ -std=c++20
LIBS= -lsqlite3

#LIB_SRCS = $(wildcard lib/*.cpp)
#LIB_OBJS = $(LIB_SRCS:.cpp=.o)


#libruralis2.so : $(LIB_OBJS)
#	ar rcs $@ $^

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, objs/%.o, $(SRCS))


JAP0_SRCS = $(wildcard src_jap0/*.cpp)
JAP0_OBJS = $(patsubst src_jap0/%.cpp, objs/%.o, $(JAP0_SRCS))

all: bin/jap0 

bin/jap0:  $(JAP0_OBJS)   | bin
	$(CPP) -o $@ $^ $(LIBS)
	cp bin/jap0 ~/bin/jap0

objs/%.o: src_jap0/%.cpp | objs
	$(CPP) $(CPPFLAGS) -o $@ -c $<


# $(OBJS): $(SRCS) | build

bin:
	mkdir -p bin

objs:
	mkdir -p objs

install:
	cp bin/jap0 ~/bin/jap0

clean:
	rm -r objs/*.o
	rm bin/jap0


