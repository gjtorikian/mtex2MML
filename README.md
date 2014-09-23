# amsmath-tex2MML

This is a Bison grammar for TeX math, written in C. It is a fork of [the itex2MML project](https://golem.ph.utexas.edu/~distler/blog/itex2MML.html), originally written by Jacques Distler and Paul Gartside.

The goal of this particular fork is to implement as much of the AMS-TeX math as possible.

## Building

1. You need GNU make to build the itex code.
2. `cd` into *src* and run `make`.

The tests are written in Ruby, which is a callback to the original Ruby wrapper of this library. To run the tests:

1. You need [SWIG](http://www.swig.org/) (>= 1.3).
2. Run `rake` to both make the Ruby library, and run the tests.

## License

As with the original version(s), this is Open Source software, released under a triple license: [GPL](http://choosealicense.com/licenses/gpl-2.0/), [MPL](http://choosealicense.com/licenses/mpl-2.0/), and [LGPL](http://choosealicense.com/licenses/lgpl-2.1/).
