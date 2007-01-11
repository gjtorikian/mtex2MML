#YACC=yacc
YACC=bison -y  -v
LEX=flex -P$(YYPREFIX) -olex.yy.c

RM=rm -f
INSTALL=install -c
BINDIR=/usr/local/bin

YYPREFIX=itex2MML_yy

all:    y.tab.c lex.yy.c itex2MML

y.tab.c:	itex2MML.y
		$(YACC) -p $(YYPREFIX) -d itex2MML.y

lex.yy.c:	itex2MML.l
		$(LEX) itex2MML.l

y.tab.o:	y.tab.c itex2MML.h
		$(CC) -c -o y.tab.o y.tab.c

lex.yy.o:	lex.yy.c y.tab.c itex2MML.h
		$(CC) -c -o lex.yy.o lex.yy.c

itex2MML:	lex.yy.o y.tab.o itex2MML.cc itex2MML.h
		$(CXX) -o itex2MML lex.yy.o y.tab.o itex2MML.cc

clean:		
		$(RM) y.tab.* lex.yy.c itex2MML *.o *.output *.so *.dll *.sl *.bundle itex2MML_ruby.c

install:	itex2MML
		$(INSTALL) itex2MML $(BINDIR)

RUBY_CFLAGS = $(shell ruby -e 'require "rbconfig"; print Config::CONFIG["CCDLFLAGS"]')
RUBY_LD = MACOSX_DEPLOYMENT_TARGET=10.4 $(shell ruby -e 'require "rbconfig"; print Config::CONFIG["LDSHARED"]')
RUBYLIBDIR =$(shell ruby -e 'require "rbconfig"; print Config::CONFIG["libdir"]') 
RUBY_PREFIX = $(RUBYLIBDIR)/ruby
RUBY_ARCH = $(shell ruby -e 'require "rbconfig"; print Config::CONFIG["arch"]')
RUBYDIR = $(shell ruby -e 'require "rbconfig"; print Config::CONFIG["archdir"]')
RUBY_SITEDIR = $(shell ruby -e 'require "rbconfig"; print Config::CONFIG["sitelibdir"]')
RUBY_SITEARCHDIR = $(shell ruby -e 'require "rbconfig"; print Config::CONFIG["sitearchdir"]')
DYLIB_EXT = $(shell ruby -e 'require "rbconfig"; print Config::CONFIG["DLEXT"]')

itex2MML_ruby.c:	itex2MML.i
			swig -ruby -o itex2MML_ruby.c  itex2MML.i

itex2MML_ruby.o:	itex2MML_ruby.c
			$(CC) $(RUBY_CFLAGS) -c itex2MML_ruby.c -I$(RUBYDIR) -o itex2MML_ruby.o

y.tab_ruby.o:		y.tab.c
			$(CC)  -Ditex2MML_CAPTURE -c -o y.tab_ruby.o y.tab.c

ruby:	itex2MML_ruby.o y.tab_ruby.o lex.yy.o
	$(RUBY_LD) itex2MML_ruby.o y.tab_ruby.o lex.yy.o -L$(RUBYLIBDIR) -lruby -o itex2MML.$(DYLIB_EXT)

test_ruby:
	ruby ./itextomml.rb

install_ruby:	itex2MML.$(DYLIB_EXT)
	$(INSTALL) itex2MML.$(DYLIB_EXT) $(RUBY_SITEARCHDIR)
	$(INSTALL) itextomml.rb $(RUBY_SITEDIR)
