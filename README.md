# StarkScript

StarkScript - or the *Stark programming language* - is a compiled C-based programming language that aims to offer the same usability as that of JavaScript's and TypeScript's.

> Note that this is a replacement for the [Murmur programming language](https://github.com/EnderCommunity/Murmur). The compiler of the Murmur programming language felt a bit messy, and it was not proparly documented. So, instead of rewriting lots of its code and re-documenting it, it was decided to completely rewrite the whole compiler and re-do the whole thing properly. (hopefully this won't happen again)

## The development environment

The StarkScript compiler is written in C, and the whole language is compiled down to C code. So, naturally, you must have a C compiler. We recommend the [GNU compiler](https://gcc.gnu.org/).

> It would be better if you use Linux to work on the compiler.
> If you are a Windows user, you could use Windows to work on the compiler, or you could also use the [Windows Subsystem for Linux](https://docs.microsoft.com/en-us/windows/wsl/install) (AKA WSL)

### Linux

If you face trouble when installing the GCC compiler on your operating system, you could try googling "*How to install GNU GCC compiler on -Your Linux Distro-*". Here's an article that covers [setting up the GCC compiler on Ubuntu](https://linuxize.com/post/how-to-install-gcc-compiler-on-ubuntu-18-04/).

### Windows

If you wish to use Windows, you need to download [*MSYS2*](https://www.msys2.org/). (Make sure to update your PATH variable after the installing *MSYS2*)

Execute the folllowing in your *MSYS2* console:

```sh
pacman -Syu

## Run this commands only if the compiler fails
pacman -S mingw-w64-x86_64-toolchain
```

## Compiling and running the StarkScript compiler

If you wish to compile and run the StarkScript compiler, navigate to the `/compiler` directory and do the following:

### For Linux

```sh
gcc -g stark.c -o Stark.out ## Compile using GCC into an OUT file
./Stark.out ## Run the compiler
```

### For Windows

```sh
gcc -g stark.c -o Stark.exe ## Compile using GCC into an EXE file
./Stark ## Run the compiler
```

### Detecting memory leaks

If you wish to check for any memory leaks, you can use `valgrind` on Linux:

```sh
sudo valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./Stark.out
```

## Contributing

Everyone is allowed to contribute to this repository. Just make sure to document all your changes and not exceed the 100 characters per line restriction.

## License

StarkScript's compiler is licensed under a [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/).
