
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
JAP0_OBJS = $(patsubst src_jap0/%.cpp, objs0/%.o, $(JAP0_SRCS))

JAP1_SRCS = $(wildcard src_jap1/*.cpp)
JAP1_OBJS = $(patsubst src_jap1/%.cpp, objs1/%.o, $(JAP1_SRCS))

all: bin/jap0 bin/jap1 

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



# $(OBJS): $(SRCS) | build

bin:
	mkdir -p bin

objs0:
	mkdir -p objs0

objs1:
	mkdir -p objs1

install:
	cp bin/jap0 ~/bin/jap0

clean:
	rm -r objs/*.o
	rm bin/jap0


