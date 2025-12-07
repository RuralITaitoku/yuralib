
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

JAP_SRCS = $(wildcard src_jap/*.cpp)
JAP_OBJS = $(patsubst src_jap/%.cpp, objs/%.o, $(JAP_SRCS))
JAP_OBJS += objs/yuraterm.o objs/yura_pipe.o objs/yura.o
JAP0_SRCS = $(wildcard src_jap0/*.cpp)
JAP0_OBJS = $(patsubst src_jap0/%.cpp, objs/%.o, $(JAP0_SRCS))
JAP0_OBJS += objs/yuraterm.o  
UT_SRCS = $(wildcard ut/*.cpp)
UT_OBJS = $(patsubst ut/%.cpp, objs/%.o, $(UT_SRCS))

MD_SRCS = $(wildcard md/*.md)
HTML = $(patsubst md/%.md, html/%.html, $(MD_SRCS))


all: bin/try bin/jap bin/jap0 bin/utjap html 

bin/try: $(OBJS) | bin
	$(CPP) -o $@ $^ -lsqlite3

bin/jap: $(JAP_OBJS)   | bin
	$(CPP) -o $@ $^ -lsqlite3

bin/utjap:	$(UT_OBJS) $(filter-out objs/jap_zero.o, $(JAP_OBJS)) | bin
	$(CPP) -o $@ $^ -lsqlite3 -lgtest -lpthread

bin/jap0:  $(JAP0_OBJS)   | bin
	$(CPP) -o $@ $^ $(LIBS)
	
html: $(HTML)  bin/try
	@echo test $(HTML)


objs/%.o: src/%.cpp | objs
	$(CPP) $(CPPFLAGS) -o $@ -c $<
objs/%.o: src_jap/%.cpp | objs
	$(CPP) $(CPPFLAGS) -o $@ -c $<
objs/%.o: ut/%.cpp | objs
	$(CPP) $(CPPFLAGS) -o $@ -c $<
objs/%.o: src_jap0/%.cpp | objs
	$(CPP) $(CPPFLAGS) -o $@ -c $<

html/%.html: md/%.md html/sidemenu.html
	bin/try markdown -o $@ -i $< -t html/sidemenu.html

html/sidemenu.html: md/sidemenu.md html/temp.html
	bin/try markdown -o $@ -i $< -t html/temp.html -rw '@@@sidemenu@@@'


# $(OBJS): $(SRCS) | build

bin:
	mkdir -p bin

objs:
	mkdir -p objs

install:
	cp bin/try ~/bin/try
	cp bin/jap ~/bin/jap
	cp bin/jap0 ~/bin/jap0

clean:
	rm -r objs/*.o
	rm bin/try bin/jap bin/utjap bin/jap0
	find html/*.html -not -name "temp.html"	-delete



