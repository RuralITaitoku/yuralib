
# CPP=clang++
CPP=g++
CPPFLAGS= -g -Wall -DDEBUG  -I./include/ -std=c++20

#LIB_SRCS = $(wildcard lib/*.cpp)
#LIB_OBJS = $(LIB_SRCS:.cpp=.o)


#libruralis2.so : $(LIB_OBJS)
#	ar rcs $@ $^



SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, objs/%.o, $(SRCS))

JAP_SRCS = $(wildcard src_jap/*.cpp)
JAP_OBJS = $(patsubst src_jap/%.cpp, objs/%.o, $(JAP_SRCS))

MD_SRCS = $(wildcard md/*.md)
HTML = $(patsubst md/%.md, html/%.html, $(MD_SRCS))


all: try html jap

html: $(HTML)  

try: $(OBJS)
	$(CPP)  -o $@ $^ -lsqlite3

jap: $(JAP_OBJS) objs/yuraterm.o objs/yura_pipe.o objs/yura.o 
	$(CPP)  -o $@ $^ -lsqlite3


objs/%.o: src/%.cpp | objs
	$(CPP) $(CPPFLAGS) -o $@ -c $<

objs/%.o: src_jap/%.cpp | objs
	$(CPP) $(CPPFLAGS) -o $@ -c $<

html/%.html: md/%.md html/sidemenu.html
	./try markdown -o $@ -i $< -t html/sidemenu.html

html/sidemenu.html: md/sidemenu.md html/temp.html
	./try markdown -o $@ -i $< -t html/temp.html -rw '@@@sidemenu@@@'


# $(OBJS): $(SRCS) | build

objs:
	mkdir -p objs

install:
	cp ./try ~/bin/try
	cp ./jap ~/bin/jap

clean:
	rm -r objs/*.o
	rm ./try ./jap
	find html/*.html -not -name "temp.html"	-delete



