## Bug fixes

If you're interested in fixing a bug, there are two files you'll likely need to change:

* *mtex2MML.l*, which contains the grammar rules for the TeX characters.
* *mtex2MML.y*, which acts on the grammar states and converts the data into MathML.

If you submit a PR for something new, you should also add tests. You may need to update [SUPPORTED.md](SUPPORTED.md), too.

## Feature requests

Want something added, but don't want to code? That's cool! Please provide a clear example of the math TeX and a reason why you think it should be added. For example:

> I'd like to be able to use `\douglas` in my equations, like this:
>
>     $$
>     \being{array}
>     \douglas - 2 = 40
>     $$
>
> This shorthand notation is very popular among British mathematicians.

Simply stating "Please add this syntax" without a reason might not get a reply.
