# mtex2MML

[![Build Status](https://travis-ci.org/gjtorikian/mtex2MML.svg?branch=master)](https://travis-ci.org/gjtorikian/mtex2MML)

This is a Bison grammar to convert TeX math into MathML. It can be used as a standalone program or as a static library. It is written in standard C99.

The goal of this project is to implement as much of AMS-TeX math as possible.

This code is a fork of [the itex2MML project](https://golem.ph.utexas.edu/~distler/blog/itex2MML.html), originally written by Jacques Distler and Paul Gartside. It has vastly more support for AMS-TeX math than the original, with a much larger test suite.

### Why MathML?!

It's true, MathML is not well supported in browsers. (Kudos to the Firefox team for sticking with it!)

However, you can consider MathML as an intermediate format onto greater things, like conversion to SVG via [mathematical](https://github.com/gjtorikian/mathematical).

## What's supported?

Please refer to [SUPPORTED.md](SUPPORTED.md) for more information on what this lib can do. Right now it has a ~93% compatibility with everything MathJax can do.

The most obvious gap in this library is the inability to define new commands (via `\mathop`, `\def`, `\mathchoice`, etc.). Everything else in standard TeX math should be fine.

## Building

To build mtex2MML, you need:
* [CMake](http://www.cmake.org/download/) (at least version 2.8.9)
* [Bison](https://www.gnu.org/software/bison/)
* [Flex](http://flex.sourceforge.net/)

To fetch dependencies and run the library, call:

```
script/bootstrap
cd build
cmake ..
make
```

## Usage

Inline equations are demarcated by `$...$`. Display equations are demarcated by `$$...$$` or `\[...\]`. You cannot nest equations; for example, `$$...\text{foo $...$ bar}...$$` is not allowed.

### As a library

Both a static and dynamic library are created as part of the `cmake` build process. Include one of them during the compilation of your program.

#### Methods available

The library exposes the following methods:

* `char * mtex2MML_parse(const char * str, unsigned long strlen)`: Converts a single TeX equation in `str` to MathML. Returns just the MathML equation, as a string.

* `char * mtex2MML_global_parse(const char * str, unsigned long strlen, int global_start)`: The same as `mtex2MML_parse`, but allows you to provide a starting integer for equation numbering. Returns just the MathML equation, as a string.

* `int mtex2MML_filter(const char * str, unsigned long strlen)`: Given a string with a mix of TeX math and non-math elements, this returns a single string containing just the converted math elements. Equations are automatically numbered. Returns a `status` indicating success (`0`) or failure. You must access the resulting string with `mtex2MML_output`.

* `int mtex2MML_html_filter(const char * str, unsigned long strlen)`: Given a string with a mix of TeX math and non-math elements, this converts all the math and leaves the rest of the string unmodified. Equations are automatically numbered. Returns a `status` indicating success (`0`) or failure. You must access the resulting string with `mtex2MML_output`. HTML within a math equation are normalized (eg. `<` becomes `&lt;`).

* `int mtex2MML_strict_html_filter(const char * str, unsigned long strlen)`: Given a string with a mix of TeX math and non-math elements, this converts all the math and leaves the rest of the string unmodified. Equations are automatically numbered. Returns a `status` indicating success (`0`) or failure. You must access the resulting string with `mtex2MML_output`. HTML within a math equation are normalized (eg. `<` becomes `&lt;`).

[The *tests/basic.c* suite](tests/basic.c) provides a demonstrate of how these methods can be used.

### As a command

Like any good Unix program, the mtex2MML binary operates on pipes. That is to say, it works like this:

```
echo '\sin y' | mtex2MML --inline > math.txt
```

Use `mtex2MML -h` to get some documentation on all the options.

## Error handling

If a token cannot be parsed, or if the tokenization is nested too deep, the library will bail with a status code. A `0` status indicates a success, while anything else indicates a failure, [as per the Bison documentation](http://www.gnu.org/software/bison/manual/html_node/Parser-Function.html). An error message is also printed to STDERR.

[The *tests/maliciousness.c* suite](tests/maliciousness.c) has a demonstration on how to perform error handling.

## Testing

Assuming you've built the programs, to run the test suite:

```
cd build
ctest -V
```

mtex2MML has a test suite that matches the one found in [MathJax](https://github.com/mathjax/MathJax-test), with a few exceptions:

* Files marked as `.xtex` have features that are not implemented, but probably should be in the future.
* Files marked as `.no_tex` have features that probably won't be implemented.

During the test run, the suite will list the percentage of features that still need coverage.

## Installing

To install the mtex2MML binary, you can run:

```
make install
```

## Contributing

Found a bug or want to request a feature? Great! Check out [CONTRIBUTING.md](CONTRIBUTING.md) for more information!

## License

As with the original version(s), this is Open Source software, released under a triple license: [GPL](http://choosealicense.com/licenses/gpl-2.0/), [MPL](http://choosealicense.com/licenses/mpl-2.0/), and [LGPL](http://choosealicense.com/licenses/lgpl-2.1/).
