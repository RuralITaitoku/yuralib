
CPP=g++
CPPFLAGS= -g -Wall -DDEBUG  -I./include/ -std=c++17

#LIB_SRCS = $(wildcard lib/*.cpp)
#LIB_OBJS = $(LIB_SRCS:.cpp=.o)


#libruralis2.so : $(LIB_OBJS)
#	ar rcs $@ $^



SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, objs/%.o, $(SRCS))



all: try



try: $(OBJS)
	g++ -o $@ $(OBJS) 

objs/%.o: src/%.cpp | objs
	$(CPP) $(CPPFLAGS) -o $@ -c $<


# $(OBJS): $(SRCS) | build

objs:
	mkdir -p objs


clean:
	rm -r objs

