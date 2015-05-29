CURRENT_MAKEFILE  := $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
TEST_DIRECTORY    := $(abspath $(dir $(CURRENT_MAKEFILE)))/tests
CLAR_FIXTURE_PATH := $(TEST_DIRECTORY)/fixtures/
CFLAGS += -fPIC -Wall -Wextra -Wno-sign-compare -DCLAR_FIXTURE_PATH=\"$(CLAR_FIXTURE_PATH)\" -pedantic -std=gnu99 -iquote inc
LDFLAGS += -lm

SOURCES  := $(wildcard src/*.c)
INCLUDES := $(wildcard *.h)
OBJECTS  := $(SOURCES:src/%.c=src/%.o)

TESTS = $(shell find tests -name '*.c')
TESTOBJS = $(TESTS:.c=.o)

YYPREFIX=mtex2MML_yy
BISON=bison -y -v
FLEX=flex -P$(YYPREFIX) -olex.yy.c

RM=rm -rf
INSTALL=install -c
BINDIR=/usr/local/bin

#### GENERAL ####

all: clean lex libmtex2MML.a mtex2MML

.PHONY: clean
clean:
	$(RM) build
	$(RM) src/lex.yy.*
	$(RM) src/*y.*
	$(RM) src/*.o
	$(RM) src/*.orig
	$(RM) tests/*.o
	$(RM) tests/.clarcache
	$(RM) tests/clar.suite

lex: src/y.tab.o src/lex.yy.o

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
	$(CC) $(CFLAGS) -c -o src/lex.yy.o src/lex.yy.c

libmtex2MML.a: $(OBJECTS) lex
	$(AR) crv libmtex2MML.a src/y.tab.o src/lex.yy.o $(OBJECTS)
	mkdir -p build/
	mv libmtex2MML.a build/
	cp src/mtex2MML.h build/

mtex2MML: $(OBJECTS) lex src/mtex2MML.h
	mkdir -p build/
	$(CC) $(CFLAGS) -o mtex2MML $(OBJECTS) src/y.tab.o src/lex.yy.o $(LDFLAGS)
	mv mtex2MML build/

$(OBJECTS): src/%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -lm

install: mtex2MML
	$(INSTALL) build/mtex2MML $(BINDIR)

#### TESTS #####

.PHONY: test
test: compile_test
	./tests/testrunner
	cat ./tests/mathjax_summary.txt

compile_test: mathjax clar.suite tests/helpers.h tests/clar_test.h $(TESTOBJS)
	$(CC) $(CFLAGS) -Wno-implicit-function-declaration $(TESTOBJS) build/libmtex2MML.a -o tests/testrunner $(LDFLAGS)

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
