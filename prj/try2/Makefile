CPP = g++
CPPFLAGS := 
CPP_OPT = --std+11 
BUILD := build
SRC := src

SRCS := $(shell find src -name "*.cpp")
OBJS = $(patsubst src/%.cpp, build/%.o, $(SRCS))

all : test

test: $(OBJS)
	g++ -o $@ $(OBJS)

build/%.o : src/%.cpp
	mkdir -p $(@D)
	g++ -o $@ -c $<

#$(BUILD)/%.o : $(SRC)/%.cpp
#	$(CPP) $(CPPFLAGS) -o $@ -c $<

		
