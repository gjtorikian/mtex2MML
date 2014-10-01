## Bug fixes

If you're interested in fixing a bug, there are two files you'll likely need to change:

* *itex2MML.l*, which contains the grammar rules for the TeX characters
* *itex2MML.y*, which acts on the grammar states and converts the data into MathML

If you submit a PR, you should also think about updating [SUPPORTED.md](SUPPORTED.md). You may need to add tests, too.

## Feature requests

Want something added? Great. Please provide a clear example of the math TeX and a reason why you think it should be added. For example:

> I'd like to be able to use `\douglas` in my equations, like this:
>
>     $$
>     \being{array}
>     \douglas - 2 = 40
>     $$
>
> This shorthand notation is very popular among British mathematicians.
