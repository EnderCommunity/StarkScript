# This is a Makefile, and Makefiles are used to automate commands!
# You can use this makefile only if you're using Linux (You can't use it on Windows)

# The available commands are:
# make             Build the compiler for Linux
#                  This command uses the "gcc" GNU compiler
# make win32       Build the compiler for Windows 32-bit
#                  This command uses the "mingw-w64" compiler
# make win64       Build the compiler for Windows 64-bit
#                  This command uses the "mingw-w64" compiler
# make run-all     Build the compiler for Linux and windows (32-bit and 64-bit)
# make clean       Delete all the compiler binaries
#
# If you wish to use any Windows-related commands, you must install "mingw-w64":
#  _______________________________________________________________________________________________
# |                                                                                               |
# |  $  sudo apt-get install mingw-w64                                                            |
# |_______________________________________________________________________________________________|

# The CC variable is used to store the compile command
CC = gcc

# The CC variable is used to store the Windows 32-bit compile command
W32CC = i686-w64-mingw32-gcc

# The CC variable is used to store the Windows 64-bit compile command
W64CC = x86_64-w64-mingw32-gcc

# The NAME variable is used to store the name of the output executable
NAME=Stark

# The INPUT variable is used to store the needed arguments to tell the compiler where the input
# file is
INPUT = -g ./compiler/stark.c

# The OUTPUT variable is used to store the needed arguments to tell the compiler where we want to
# stored the output executable
OUTPUT = -o ./bin/$(NAME)

# Define the behaviour of the "make" command
all:
	$(CC) $(INPUT) $(OUTPUT).out

# Define the behaviour of the "make win32" command
win32:
	$(W32CC) $(INPUT) $(OUTPUT)-32bit.exe

# Define the behaviour of the "make win64" command
win64:
	$(W64CC) $(INPUT) $(OUTPUT)-64bit.exe

clean:
	rm ./bin/*

# Define the behaviour of the "make run-all" command
run-all:
	make
	make win32
	make win64
