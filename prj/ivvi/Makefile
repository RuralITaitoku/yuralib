
CPP=g++
CPPFLAGS= -g -Wall -DDEBUG -fPIC -I./include/ -std=c++17

#LIB_SRCS = $(wildcard lib/*.cpp)
#LIB_OBJS = $(LIB_SRCS:.cpp=.o)


#libruralis2.so : $(LIB_OBJS)
#	ar rcs $@ $^



SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all: ivvi

ivvi: $(OBJS)
	g++ -o $@ build/$(OBJS) 

%.o: %.cpp
	mkdir -p build/src
	$(CPP) $(CPPFLAGS) -o build/$@ -c $<


