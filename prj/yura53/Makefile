
CPP=g++
CPPFLAGS= -g -Wall -DDEBUG  -I./include/ -std=c++17

#LIB_SRCS = $(wildcard lib/*.cpp)
#LIB_OBJS = $(LIB_SRCS:.cpp=.o)


#libruralis2.so : $(LIB_OBJS)
#	ar rcs $@ $^



SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, objs/%.o, $(SRCS))

MD_SRCS = $(wildcard src/*.md)
HTML = $(patsubst src/%.md, html/%.html, $(MD_SRCS))


all: try html

html: $(HTML)

try: $(OBJS)
	$(CPP)  -o $@ $(OBJS) -lsqlite3

objs/%.o: src/%.cpp | objs
	$(CPP) $(CPPFLAGS) -o $@ -c $<

html/%.html: src/%.md
	./try markdown -o $@ -i $< -t html/temp.html

# $(OBJS): $(SRCS) | build

objs:
	mkdir -p objs

install:
	cp ./try ~/bin/try

clean:
	rm -r objs/*.o
	find html/*.html -not -name "temp.html"	-delete



