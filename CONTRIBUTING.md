# Contributing to StarkScript

We love your input! We want to make contributing to this project as easy and transparent as possible, whether it's:

- Reporting a bug
- Discussing the current state of the code
- Submitting a fix
- Proposing new features
- Becoming a maintainer

## We Develop with Github

We use github to host code, to track issues and feature requests, as well as accept pull requests.

## We Use [Github Flow](https://guides.github.com/introduction/flow/index.html), So All Code Changes Happen Through Pull Requests

Pull requests are the best way to propose changes to the codebase (we use [Github Flow](https://guides.github.com/introduction/flow/index.html)). We actively welcome your pull requests:

1. Fork the repo and create your branch from `master`.
2. If you've added code that should be tested, add tests.
3. If you've changed APIs, update the documentation.
4. Ensure the test suite passes.
5. Make sure your code lints.
6. Issue that pull request!

## Any contributions you make will be under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License

In short, when you submit code changes, your submissions are understood to be under the same [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/) that covers the project. Feel free to contact the maintainers if that's a concern.

## Report bugs using Github's [issues](https://github.com/EnderCommunity/StarkScript/issues/)

We use GitHub issues to track public bugs. Report a bug by opening a new issue; it's that easy!

## Write bug reports with detail, background, and sample code

The issue template should be enough to guide you through writing a proper bug report!

**Great Bug Reports** tend to have:

- A quick summary and/or background

- Steps to reproduce
  - Be specific!
  - Give sample code if you can.
- What you expected would happen
- What actually happens
- Notes (possibly including why you think this might be happening, or stuff you tried that didn't work)

People *love* thorough bug reports. I'm not even kidding.

## Use a Consistent Coding Style

### Comments

Make to sure to comment your code in chunks, detailing what each chunk of code is doing. If you decide to include any libraries, you must specifiy the reason for doing that in a comment.

### Code Structure

The max length of any given line of code is 100 characters. You may exceed this limit if you are defining a long string.

We use 4 whitespaces for code padding, like this:

```js
var something;

function somethingElse(){

    something = "else";
//^^ 4 whitespace characters

}
```

### Using the `consoleError`, `consoleDebug`, `consoleWarn`, and `consoleInfo` functions

You may never start a console message with a new line character, or any whitespace. (You may break this rule when using the `consoleInfo` function)

And, when you use the `consoleError` function, make sure to account for any memory leaks that may occur on sudden termination! You may modify the `stopProcess` function to free up global variables.

## References

This document was adapted from [this template](https://gist.github.com/briandk/3d2e8b3ec8daf5a27a62).
