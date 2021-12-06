/**
 *
 *  Start the compiler
 *
**/


// Include the compiler flags
#include "./flags.c"

// Pre-define the `stopProcess` function so all the included files can use it
void stopProcess(int exitCode);

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

    if(cmplrInputFilePth != NULL){

        // ...

        // Free the memory used by the `cmplrInputFilePth` and `cmplrOutputFilePth` variable
        free(cmplrInputFilePth);
        free(cmplrOutputFilePth);

    }else{

        consoleError("No input file path was passed!\n");

    }

    // Print a warning about the state of the compiler
    consoleWarn("This compiler is still not functional! Please, consider helping us!\n");

    // Return a SUCCESS exit code
    return EXIT_SUCCESS;

}

// Define a function that stops the process
void stopProcess(int exitCode){

    // Free up any globally allocated variables depending on the compiling stage that the error occured in
    if(cmplrInputFilePth != NULL) {

        free(cmplrInputFilePth);

    }
    if(cmplrOutputFilePth != NULL){

        free(cmplrOutputFilePth);

    }

    // Use the built-in `exit` function to terminate the process
    exit(exitCode);

}