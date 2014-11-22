#YACC=yacc
YACC=bison -y  -v
LEX=flex -P$(YYPREFIX) -olex.yy.c
SWIG=swig
RUBY=ruby
#RUBY=ruby19

RM=rm -f
INSTALL=install -c
BINDIR=/usr/local/bin

YYPREFIX=mtex2MML_yy

all:    y.tab.c lex.yy.c mtex2MML

str_copy.o:
	$(CC) -fPIC -c -o str_copy.o deps/str-copy/str-copy.c -Ideps

occurrences.o:
	$(CC) -fPIC -c -o occurrences.o deps/occurrences/occurrences.c -Ideps

color_definitions.o:
	$(CC) -fPIC -c -o color_definitions.o color_definitions.c

string_extras.o:
	$(CC) -fPIC -c -o string_extras.o string_extras.c

parse_extras.o:
	$(CC) -fPIC -c -o parse_extras.o parse_extras.c

y.tab.c:	mtex2MML.y string_extras.o occurrences.o str_copy.o parse_extras.o color_definitions.o
		$(YACC) -p $(YYPREFIX) -d mtex2MML.y

lex.yy.c:	mtex2MML.l
		$(LEX) mtex2MML.l

y.tab.o:	y.tab.c mtex2MML.h
		$(CC) $(CFLAGS) -c -o y.tab.o y.tab.c

lex.yy.o:	lex.yy.c y.tab.c mtex2MML.h
		$(CC) $(CFLAGS) -c -o lex.yy.o string_extras.o occurrences.o str_copy.o parse_extras.o color_definitions.o lex.yy.c

mtex2MML:	lex.yy.o y.tab.o mtex2MML.cc mtex2MML.h
		$(CXX) $(CFLAGS) -o mtex2MML lex.yy.o y.tab.o string_extras.o occurrences.o str_copy.o color_definitions.o parse_extras.o mtex2MML.cc

universal:
		CFLAGS='-arch i686 -arch ppc' make all

clean:
		$(RM) y.tab.* lex.yy.c mtex2MML *.o *.output *.so *.dll *.sl *.bundle mtex2MML_ruby.c

install:	mtex2MML
		$(INSTALL) mtex2MML $(BINDIR)

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
EXTRA_CFLAGS = -DHAVE_SNPRINTF -DHAVE_STRUCT_TIMESPEC -DHAVE_STRUCT_TIMEZONE
LD_TARGET = MACOSX_DEPLOYMENT_TARGET=10.4
else
EXTRA_CFLAGS = ''
LD_TARGET = ''
endif

mtex2MML_ruby.c:	mtex2MML.i
			$(SWIG) -ruby -o mtex2MML_ruby.c  mtex2MML.i

mtex2MML_ruby.o:	mtex2MML_ruby.c
			$(CC) $(RUBY_CFLAGS)  $(EXTRA_CFLAGS) -c mtex2MML_ruby.c -I$(RUBYHDRDIR) -I$(RUBYDIR) -I$(RUBYHDRDIR)/$(RUBY_ARCH) -Ideps -o mtex2MML_ruby.o

y.tab_ruby.o:		y.tab.c string_extras.o occurrences.o str_copy.o parse_extras.o color_definitions.o
			$(CC) $(RUBY_CFLAGS) -Dmtex2MML_CAPTURE -c -o y.tab_ruby.o y.tab.c

lex.yy_ruby.o:	lex.yy.c y.tab.c mtex2MML.h
		$(CC) $(RUBY_CFLAGS) -c -o lex.yy_ruby.o string_extras.o occurrences.o str_copy.o parse_extras.o color_definitions.o lex.yy.c

ruby:	mtex2MML_ruby.o y.tab_ruby.o lex.yy_ruby.o
	$(LD_TARGET) $(RUBY_LD) mtex2MML_ruby.o y.tab_ruby.o lex.yy_ruby.o string_extras.o occurrences.o str_copy.o color_definitions.o parse_extras.o -L$(RUBYLIBDIR) $(LIBRUBYARG) -o mtex2MML.$(DYLIB_EXT)

test_ruby:
	$(RUBY) ./mtextomml.rb

install_ruby:	mtex2MML.$(DYLIB_EXT)
	$(INSTALL) mtex2MML.$(DYLIB_EXT) $(RUBY_SITEARCHDIR)
	$(INSTALL) mtextomml.rb mtex_stringsupport.rb $(RUBY_SITEDIR)
