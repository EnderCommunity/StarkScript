/**
 *
 *  Start the compiler
 *
**/


// Include the compiler flags
#include "./flags.h"

// Pre-define the `stopProcess` function so all the included files can use it
void stopProcess(int exitCode);

// Include all the console-related functions
#include "./console.c"

// Include the start message function
#include "./message.c"

// Include the command line arguments processing function
#include "./args.c"

// Include the input and output paths processing function
#include "./io.c"

// Define the main function
int main(int argc, char *argv[]){

    // Print the compiler start message
    printCmplrMsg();

    // Process the command line arguments
    processArgs(argc, argv);

    // Process the input and output paths
    if(processIO(&cmplrInputFilePth, &cmplrOutputFilePth, &cmplrOutputFileName)){

        // Note that all the variables that were passed to the `processIO` function are now cleared,
        // All these variables were used to generate the `globalIO` object!

        // ...

        // Free up the memory used by the output file name variable
        free(globalIO.output.fileName);

        // Free up the used memory by the output path variable
        free(globalIO.output.fullPth);

        // Free up the used memory by the input path variable
        free(globalIO.input.fullPth);

        // Free up the used memory by the working directory variable
        free(globalIO.wrkDir);

    }

    // Print a warning about the state of the compiler
    consoleWarn("No output...");

    // Return a SUCCESS exit code
    return EXIT_SUCCESS;

}

// Define a function that stops the process
void stopProcess(int exitCode){

    // Free up any globally allocated variables
    // Note that there is no need to change the value of any of these variables to NUll (as we only
    // need to do that if we want to keep track of the allocation state of these variables)
    if(cmplrInputFilePth != NULL) {

        free(cmplrInputFilePth);

    }
    if(cmplrOutputFilePth != NULL){

        free(cmplrOutputFilePth);

    }
    if(cmplrOutputFileName != NULL){

        free(cmplrOutputFileName);

    }
    if(globalIO.wrkDir != NULL){

        free(globalIO.wrkDir);

    }
    if(globalIO.input.fullPth != NULL){

        free(globalIO.input.fullPth);

    }
    if(globalIO.output.fullPth != NULL){

        free(globalIO.output.fullPth);

    }
    if(globalIO.output.fileName != NULL){

        free(globalIO.output.fileName);

    }

    // Use the built-in `exit` function to terminate the process
    exit(exitCode);

}