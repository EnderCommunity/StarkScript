/**
 *
 *  Start the compiler
 *
**/


// Include the compiler flags
#include "./flags.c"

// Include all the console-related functions
#include "./console.c"

// Include the start message function
#include "./message.c"

// Include the command line arguments processing function
#include "./args.c"

// Define the main function
int main(int argc, char *argv[]){

    // Print the compiler start message
    printCmplrMsg();

    // Process the command line arguments
    processArgs(argc, argv);

    // ...

    // Print a warning about the state of the compiler
    consoleWarn("This compiler is still not functional! Please, consider helping us!\n");

    consoleError("Oops...\n");

    // Return a SUCCESS exit code
    return EXIT_SUCCESS;

}