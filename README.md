# StarkScript

StarkScript - or the *Stark programming language* - is a compiled C-based programming language that aims to offer the same usability as that of JavaScript's and TypeScript's.

> Note that this is a replacement for the [Murmur programming language](https://github.com/EnderCommunity/Murmur). The compiler of the Murmur programming language felt a bit messy, and it was not proparly documented. So, instead of rewriting lots of its code and re-documenting it, it was decided to completely rewrite the whole compiler and re-do the whole thing properly. (hopefully this won't happen again)

## Progress

So far, the compiler has a functional *CLI*, and the compiler can filter out comments from input files.

*A roadmap will be added soon...*

## The development environment

The StarkScript compiler is written in C, and the whole language is compiled down to C code. So, naturally, you must have a C compiler. We recommend the [GNU compiler](https://gcc.gnu.org/).

> It would be better if you use Linux to work on the compiler.
> If you are a Windows user, you could use Windows to work on the compiler, or you could also use the [Windows Subsystem for Linux](https://docs.microsoft.com/en-us/windows/wsl/install) (AKA WSL)

### Linux

If you face trouble when installing the GCC compiler on your operating system, you could try googling "*How to install GNU GCC compiler on -Your Linux Distro-*". Here's an article that covers [setting up the GCC compiler on Ubuntu](https://linuxize.com/post/how-to-install-gcc-compiler-on-ubuntu-18-04/).

> If you wish to build the compiler for Windows on Linux, you must install `mingw-w64`! You can read more about this in the [Makefile](./Makefile)....

### Windows

If you wish to use Windows, you need to download [*MSYS2*](https://www.msys2.org/). (Make sure to update your PATH variable after the installing *MSYS2*)

Execute the folllowing in your *MSYS2* console:

```sh
pacman -Syu

## Run this commands only if the compiler fails
pacman -S mingw-w64-x86_64-toolchain
```

## Getting started

First, you need to compile the compiler using the `gcc` command:

```sh
## Navigate to the compiler folder
cd compiler/

## Compile the `stark.c` file
## Replace the {ext} part with the appropriate executable extention for your OS
## For windows, it's "exe". And for Linux, it's `out`.
gcc -g stark.c -o Stark.{ext}
```

> If you do not wish to compile the compiler, you can use the provided binaries in the `bin` directory!

You can use the `--help` flag to get help with the general use of all the things you can do with the compiler.

For starters, to compile a `example.stark` file, you can use this command:

```sh
./Stark --input /path/to/example.stark
```

If you're a Linux user, you can use the `make` command to make things easier. You can run this command to simply compile the compiler for Linux:

```sh
make
```

> More `make` commands are avaliable, you can read the [Makefile](./Makefile) for more info!

### Detecting memory leaks

If you wish to check for any memory leaks, you can use `valgrind` on Linux:

```sh
sudo valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./Stark.out
```

## Contributing

Everyone is allowed to contribute to this repository. You can read the [contribution guide](./CONTRIBUTING.md)!

## License

StarkScript's compiler is licensed under a [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/).
