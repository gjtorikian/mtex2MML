SOURCES = $(shell find src -name '*.c')
OBJS = $(SOURCES:.c=.o)
TESTS = $(shell find tests -name '*.c')
TESTOBJS = $(TESTS:.c=.o)

BISON=bison -y -v
FLEX=flex -P$(YYPREFIX) -olex.yy.c
YYPREFIX=mtex2MML_yy

RM=rm -f
INSTALL=install -c
BINDIR=/usr/local/bin

CURRENT_MAKEFILE  := $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
TEST_DIRECTORY    := $(abspath $(dir $(CURRENT_MAKEFILE)))/tests
CLAR_FIXTURE_PATH := $(TEST_DIRECTORY)/fixtures/
CFLAGS += -Wall -Wextra -Wno-sign-compare -DCLAR_FIXTURE_PATH=\"$(CLAR_FIXTURE_PATH)\" -pedantic -std=gnu99 -iquote inc

#### GENERAL ####

all: clean src/y.tab.o src/lex.yy.o libmtex2MML.a

.PHONY: clean
clean:
	$(RM) src/lex.yy.*
	$(RM) src/*y.*
	$(RM) src/*.o
	$(RM) tests/*.o
	$(RM) tests/.clarcache
	$(RM) tests/clar.suite

src/y.tab.c:
	$(BISON) -p $(YYPREFIX) -d src/mtex2MML.y
	mv y.output src
	mv y.tab.c src
	mv y.tab.h src

src/lex.yy.c:
	$(FLEX) src/mtex2MML.l
	mv lex.yy.c src

src/y.tab.o:	src/y.tab.c
	$(CC) -c -o src/y.tab.o src/y.tab.c

src/lex.yy.o:	src/lex.yy.c src/y.tab.c
	$(CC) -c -o src/lex.yy.o src/lex.yy.c

libmtex2MML.a: $(OBJS)
	$(AR) crv libmtex2MML.a $(OBJS)
	mkdir -p build/
	mv libmtex2MML.a build/
	cp src/mtex2MML.h build/

#### TESTS #####

.PHONY: test
test: mathjax compile_test
	./tests/testrunner
	cat ./tests/mathjax_summary.txt

compile_test: clar.suite tests/helpers.h tests/clar_test.h $(TESTOBJS)
	$(CC) $(CFLAGS) -Wno-implicit-function-declaration $(TESTOBJS) build/libmtex2MML.a -o tests/testrunner

mathjax:
	python tests/mathjax_generate.py

clar.suite:
	python tests/generate.py tests/

#### OTHER ####

.PHONY: format
format:
	astyle --indent=spaces=2 --style=1tbs --keep-one-line-blocks $(SOURCES) $(TESTS)

.PHONY: debug
debug:
	$(CC) tests/debug/mtex2MML_debug.c -o tests/debug/mtex2MML

.PHONY: leakcheck
leakcheck:
	valgrind --leak-check=full --dsymutil=yes --error-exitcode=1 ./tests/testrunner  >/dev/null
