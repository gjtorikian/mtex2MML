# amsmath-tex2MML

This is a Bison grammar to convert TeX math into MathML. It is written in C, with Ruby used for the test suite. Rather than a standalone program, it's meant to be used within another library--perhaps wrapped in a higher-level language for easier use.

This code is a fork of [the itex2MML project](https://golem.ph.utexas.edu/~distler/blog/itex2MML.html), originally written by Jacques Distler and Paul Gartside.

The goal of this particular fork is to implement as much of the AMS-TeX math as possible.

## Building

You need GNU make to build the amsmath-tex2MML code. To build it:

```
cd src
make
```

The tests are written in Ruby, which is a leftover from  the original Ruby wrapper of this library. You need [SWIG](http://www.swig.org/) (>= 1.3) to run the tests. Then, just call `rake` to both make the Ruby library, and run the tests.

## License

As with the original version(s), this is Open Source software, released under a triple license: [GPL](http://choosealicense.com/licenses/gpl-2.0/), [MPL](http://choosealicense.com/licenses/mpl-2.0/), and [LGPL](http://choosealicense.com/licenses/lgpl-2.1/).
