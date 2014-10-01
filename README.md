# mtex2MML

This is a Bison grammar to convert TeX math into MathML. It is written in C, with Ruby used for the test suite. Rather than a standalone program, it's meant to be used within another library--perhaps wrapped in a higher-level language for easier use.

This code is a fork of [the itex2MML project](https://golem.ph.utexas.edu/~distler/blog/itex2MML.html), originally written by Jacques Distler and Paul Gartside.

The goal of this particular fork is to implement as much of the AMS-TeX math as possible, and less on customizations like WebTeX.

## Why MathML?!

It's true, MathML is not well supported in browsers. (Kudos to the Firefox team for sticking with it!)

However, you can consider MathML as an intermediate format onto greater things, like conversion to SVG via [mathematical](https://github.com/gjtorikian/mathematical).

## Building

You need GNU make and [Flex](http://flex.sourceforge.net/) to build the mtex2MML code. To build it:

```
cd src
make
```

The tests are written in Ruby, which is a leftover from the original Ruby wrapper of this library. You need [SWIG](http://www.swig.org/) (>= 1.3) to run the tests, and possibly `gem install minitest`. Then, just call `rake` to both make the Ruby library and run the tests.

(I'll look to remove this requirement for a pure C test framework in The Future :tm:.)

## Usage

Pass in a string to this library and get a MathML representation as a result. *src/mtex2MML.cc* provides an example of how you might do this.

Inline equations are demarcated by `$...$`. Display equations are demarcated by `$$...$$` or `\[...\]`. You cannot nest equations; for example, `$$...\text{foo $...$ bar}...$$` is not allowed.

There are two main differences between mtex and TeX:

1.  In mtex, `$pin$` is a single token, which is translated into `<mi>pin</mi>` in MathML. `$p i n$`, on the other hand, is three tokens, which is translated into `<mi>p</mi><mi>i</mi><mi>n</mi>` in MathML. TeX makes no distinction between these two.
2.  It is possible (though probably not recommended) to insert MathML markup inside mtex equations. So "\<" and "\>" are significant. To obtain a less-than or greater-than sign, you should use `\lt` or `\gt`, respectively.

## What's supported?

Please refer to [SUPPORTED.md](SUPPORTED.md) for more information on what this lib can do.

## Contributing

Found a bug, or want to request a feature? Great! Check out [CONTRIBUTING.md](CONTRIBUTING.md) for more information!

## License

As with the original version(s), this is Open Source software, released under a triple license: [GPL](http://choosealicense.com/licenses/gpl-2.0/), [MPL](http://choosealicense.com/licenses/mpl-2.0/), and [LGPL](http://choosealicense.com/licenses/lgpl-2.1/).
