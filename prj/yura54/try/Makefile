

CPP=g++
CPPFLAGS= -g -Wall -DDEBUG  -I./include/ -std=c++20
LIBS= -lsqlite3

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, objs/%.o, $(SRCS))

all: $(OBJS)
