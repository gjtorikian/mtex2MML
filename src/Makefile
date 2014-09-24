#YACC=yacc
YACC=bison -y  -v
LEX=flex -P$(YYPREFIX) -olex.yy.c
SWIG=swig
RUBY=ruby
#RUBY=ruby19

RM=rm -f
INSTALL=install -c
BINDIR=/usr/local/bin

YYPREFIX=itex2MML_yy

all:    y.tab.c lex.yy.c itex2MML

stack.o: stack.c stack.h

string_extras.o: string_extras.c string_extras.h

parse_extras.o: stack.o parse_extras.c parse_extras.h

y.tab.c:	itex2MML.y stack.o string_extras.o parse_extras.o
		$(YACC) -p $(YYPREFIX) -d itex2MML.y

lex.yy.c:	itex2MML.l
		$(LEX) itex2MML.l

y.tab.o:	y.tab.c itex2MML.h
		$(CC) $(CFLAGS) -c -o y.tab.o y.tab.c

lex.yy.o:	lex.yy.c y.tab.c itex2MML.h
		$(CC) $(CFLAGS) -c -o lex.yy.o stack.o string_extras.o parse_extras.o lex.yy.c

itex2MML:	lex.yy.o y.tab.o itex2MML.cc itex2MML.h
		$(CXX) $(CFLAGS) -o itex2MML lex.yy.o y.tab.o stack.o string_extras.o parse_extras.o itex2MML.cc

universal:
		CFLAGS='-arch i686 -arch ppc' make all

clean:
		$(RM) y.tab.* lex.yy.c itex2MML *.o *.output *.so *.dll *.sl *.bundle itex2MML_ruby.c

install:	itex2MML
		$(INSTALL) itex2MML $(BINDIR)

RUBY_CFLAGS = $(shell $(RUBY) -e 'require "rbconfig"; print RbConfig::CONFIG["CFLAGS"]')
RUBY_LD = $(shell $(RUBY) -e 'require "rbconfig"; print RbConfig::CONFIG["LDSHARED"]')
RUBYLIBDIR =$(shell $(RUBY) -e 'require "rbconfig"; print RbConfig::CONFIG["libdir"]')
RUBY_PREFIX =  $(shell $(RUBY) -e 'require "rbconfig"; print RbConfig::CONFIG["rubylibdir"]')
RUBY_ARCH = $(shell $(RUBY) -e 'require "rbconfig"; print RbConfig::CONFIG["arch"]')
RUBYDIR = $(shell $(RUBY) -e 'require "rbconfig"; print RbConfig::CONFIG["archdir"]')
RUBYHDRDIR = $(shell $(RUBY) -e 'require "rbconfig"; print RbConfig::CONFIG["rubyhdrdir"]')
RUBY_SITEDIR = $(shell $(RUBY) -e 'require "rbconfig"; print RbConfig::CONFIG["sitelibdir"]')
RUBY_SITEARCHDIR = $(shell $(RUBY) -e 'require "rbconfig"; print RbConfig::CONFIG["sitearchdir"]')
LIBRUBYARG = $(shell $(RUBY) -e 'require "rbconfig"; print RbConfig::CONFIG["LIBRUBYARG"]')
DYLIB_EXT = $(shell $(RUBY) -e 'require "rbconfig"; print RbConfig::CONFIG["DLEXT"]')
RUBY_target_os = $(shell $(RUBY) -e 'require "rbconfig"; print RbConfig::CONFIG["target_os"]')

ifneq (, $(findstring darwin, $(RUBY_target_os)) )
EXTRA_CFLAGS = -DHAVE_SNPRINTF -DHAVE_STRUCT_TIMESPEC -DHAVE_STRUCT_TIMEZONE -fpic
LD_TARGET = MACOSX_DEPLOYMENT_TARGET=10.4
else
EXTRA_CFLAGS = ''
LD_TARGET = ''
endif

itex2MML_ruby.c:	itex2MML.i
			$(SWIG) -ruby -o itex2MML_ruby.c  itex2MML.i

itex2MML_ruby.o:	itex2MML_ruby.c
			$(CC) $(RUBY_CFLAGS)  $(EXTRA_CFLAGS) -c itex2MML_ruby.c -I$(RUBYHDRDIR) -I$(RUBYDIR) -I$(RUBYHDRDIR)/$(RUBY_ARCH) -o itex2MML_ruby.o

y.tab_ruby.o:		y.tab.c stack.o string_extras.o parse_extras.o
			$(CC) $(RUBY_CFLAGS) -Ditex2MML_CAPTURE -c -o y.tab_ruby.o y.tab.c

lex.yy_ruby.o:	lex.yy.c y.tab.c itex2MML.h
		$(CC) $(RUBY_CFLAGS) -c -o lex.yy_ruby.o stack.o string_extras.o parse_extras.o lex.yy.c

ruby:	itex2MML_ruby.o y.tab_ruby.o lex.yy_ruby.o
	$(LD_TARGET) $(RUBY_LD) itex2MML_ruby.o y.tab_ruby.o lex.yy_ruby.o stack.o string_extras.o parse_extras.o -L$(RUBYLIBDIR) $(LIBRUBYARG) -o itex2MML.$(DYLIB_EXT)

test_ruby:
	$(RUBY) ./itextomml.rb

install_ruby:	itex2MML.$(DYLIB_EXT)
	$(INSTALL) itex2MML.$(DYLIB_EXT) $(RUBY_SITEARCHDIR)
	$(INSTALL) itextomml.rb itex_stringsupport.rb $(RUBY_SITEDIR)
