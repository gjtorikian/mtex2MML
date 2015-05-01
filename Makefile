SOURCES = $(shell find src -name '*.c')
TESTS = $(shell find tests -name '*.c')
OBJS = $(SOURCES:.c=.o)
BISON=bison -y -v
FLEX=flex -P$(YYPREFIX) -olex.yy.c

RM=rm -f
INSTALL=install -c
BINDIR=/usr/local/bin

YYPREFIX=mtex2MML_yy

CFLAGS += -Wall -Wextra -pedantic -std=gnu99 -iquote inc

all: clean src/y.tab.o src/lex.yy.o libmtex2MML.a

.PHONY: clean
clean:
	$(RM) src/y.tab.* src/lex.yy.c src/mtex2MML src/*.o src/*.output src/*.so src/*.dll src/*.sl

%.o: %.c
	$(CC) -o $@ $(CFLAGS) -c $<

src/y.tab.c:
	$(BISON) -p $(YYPREFIX) -d src/mtex2MML.y
	mv y.output src
	mv y.tab.c src
	mv y.tab.h src

src/lex.yy.c:
	$(FLEX) src/mtex2MML.l
	mv lex.yy.c src

src/y.tab.o:	src/y.tab.c
	$(CC) $(CFLAGS) -c -o src/y.tab.o src/y.tab.c

src/lex.yy.o:	src/lex.yy.c src/y.tab.c
	$(CC) -c -o src/lex.yy.o src/lex.yy.c

libmtex2MML.a: $(OBJS)
	$(AR) crv libmtex2MML.a $(OBJS)
	mkdir -p dist/
	mv libmtex2MML.a dist/
	cp src/mtex2MML.h dist/

.PHONY: test
test:
	tests/generate.py tests/
	$(CC) -L. dist/libmtex2MML.a tests/clar.c tests/main.c tests/basic.c -o tests/testrunner
	./tests/testrunner
