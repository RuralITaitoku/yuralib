

CC=gcc
CFLAGS= -g -Wall -DDEBUG #  -I./include/ -std=c++20
LIBS= # -lsqlite3

SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, objs/%.o, $(SRCS))

####################### build command
bin/jap54: $(OBJS)  | bin
	$(CC) -o $@ $^ $(LIBS)

####################### build objects
objs/%.o : src/%.c | objs
	$(CC) $(CFLAGS) -o $@ -c $<
    
####################### make dir
bin:
	mkdir -p bin

objs:
	mkdir -p objs

clean:
	rm -r bin
	rm -r objs

all: $(OBJS)
