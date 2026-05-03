
# CPP=clang++
CPP=g++
CPPFLAGS= -g -Wall -DDEBUG  -I./include/ -std=c++20 --coverage -O0
LIBS= -lsqlite3 --coverage

#LIB_SRCS = $(wildcard lib/*.cpp)
#LIB_OBJS = $(LIB_SRCS:.cpp=.o)


#libruralis2.so : $(LIB_OBJS)
#	ar rcs $@ $^

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, objs/%.o, $(SRCS))


JAP0_SRCS = $(wildcard src_jap0/*.cpp)
JAP0_OBJS = $(patsubst src_jap0/%.cpp, objs0/%.o, $(JAP0_SRCS))

JAP1_SRCS = $(wildcard src_jap1/*.cpp)
JAP1_OBJS = $(patsubst src_jap1/%.cpp, objs1/%.o, $(JAP1_SRCS))

JAP54_SRCS = $(shell find src_jap54 -name '*.cpp')
JAP54_OBJS = $(patsubst src_jap54/%.cpp, objs54/%.o, $(JAP54_SRCS))

TESTS_SRCS = $(shell find src_tests -name '*.cpp')
TESTS_OBJS = $(patsubst src_tests/%.cpp, objs/%.o, $(TESTS_SRCS))

all: bin/jap0 bin/jap1 bin/jap54 bin/tests

########################################### Build jap0 command. 
bin/jap0:  $(JAP0_OBJS)   | bin
	$(CPP) -o $@ $^ $(LIBS)
	cp bin/jap0 ~/bin/jap0

objs0/%.o: src_jap0/%.cpp | objs0
	$(CPP) $(CPPFLAGS) -o $@ -c $<

########################################### Build jap1 command. 
bin/jap1:  $(JAP1_OBJS)   | bin
	$(CPP) -o $@ $^ $(LIBS)
	cp bin/jap1 ~/bin/jap1

objs1/%.o: src_jap1/%.cpp | objs1
	$(CPP) $(CPPFLAGS) -o $@ -c $<

########################################### Build jap1 command. 
bin/jap54:  $(JAP54_OBJS)   | bin
	$(CPP) -o $@ $^ $(LIBS)
	cp bin/jap54 ~/bin/jap54

objs54/%.o: src_jap54/%.cpp | objs54
	$(CPP) $(CPPFLAGS) -o $@ -c $<

########################################### Build jap tests command. 
bin/tests: $(TESTS_OBJS) | bin
	$(CPP) -o $@ $^ $(LIBS) -lpthread -lgtest

objs/%.o: src_tests/%.cpp | objs
	$(CPP) $(CPPFLAGS) -o $@ -c $<

# $(OBJS): $(SRCS) | build

bin:
	mkdir -p bin

objs:
	mkdir -p objs

objs0:
	mkdir -p objs0

objs1:
	mkdir -p objs1

objs54:
	mkdir -p objs54

install:
	cp bin/jap0 ~/bin/jap0
	cp bin/tests ~/bin/tests

clean:
	find . -name "*.o" -exec rm {} +
	rm bin/*


