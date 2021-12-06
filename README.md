# StarkScript

StarkScript is a compiled C-based programming language that aims to offer the same usability as that of JavaScript's and TypeScript's.

> Note: The development of this programming language is going to be painfully slow.

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
