/**
 *
 *  Start the compiler
 *
**/


//
// Even though it may prove unnecessary, here's the entire map of the compiler directory:
//  _______________________________________________________________________________________________
// |                                                                                               |
// | [folder] Compiler                                                                             |
// |_______________________________________________________________________________________________|
// |                                                                                               |
// | --> [folder] cli                                                                              |
// |                                                                                               |
// |     (?) This folder includes all the files that are related to the command line interface     |
// |_______________________________________________________________________________________________|
// |                                                                                               |
// | --> [folder] flags                                                                            |
// |                                                                                               |
// |     (?) This folder includes all the files that are used to define the values of custom       |
// |         flags.                                                                                |
// |                                                                                               |
// |     (!) You may only add `.h` files within this directory!                                    |
// |_______________________________________________________________________________________________|
// |                                                                                               |
// | --> [folder] info                                                                             |
// |                                                                                               |
// |     (?) This folder includes all the files that are used to define constants that hold any    |
// |         kind of unchanging information (like info about the user's OS)                        |
// |                                                                                               |
// |     (!) You may only add `.h` files within this directory!                                    |
// |_______________________________________________________________________________________________|
// |                                                                                               |
// | --> [folder] initial                                                                          |
// |                                                                                               |
// |     (?) This folder includes all the files that manage the initial compiling process. You may |
// |         read the "initial.c" file within this folder for more info about this.                |
// |_______________________________________________________________________________________________|
// |----|                                                                                          |
// |----| --> [folder] lexer                                                                       |
// |----|                                                                                          |
// |----|     (?) This folder includes all the lexer files.                                        |
// |____|__________________________________________________________________________________________|
// |----|                                                                                          |
// |----| --> [folder] preproc                                                                     |
// |----|                                                                                          |
// |----|     (?) This folder includes all the preprocessor files.                                 |
// |____|__________________________________________________________________________________________|
// |                                                                                               |
// | --> [folder] strings                                                                          |
// |                                                                                               |
// |     (?) This folder includes all the files that are used to define any interchangeable string |
// |         values.                                                                               |
// |                                                                                               |
// |     (!) You may only add `.h` files within this directory!                                    |
// |_______________________________________________________________________________________________|
//

// Include the `time.h` library
// In this project, it's used to keep track of how long the compiler takes to run
#include <time.h>

// Define the start time variable
clock_t startTime;

// Include the compiler flags
#include "./flags.h"

// Pre-define the `stopProcess` function so all the included files can use it
void stopProcess(int exitCode);

// Include all the console-related functions
#include "./cli/console.c"

// Include the start message function
#include "./cli/message.c"

// Include the command line arguments processing function
#include "./cli/args.c"

// Include the input and output paths processing function
#include "./cli/io.c"

// Include the initial compiling components
#include "./initial/initial.c"

// Define the main function
int main(int argc, char *argv[]){

    // Keep track of the start time
    startTime = clock();

    // Print the compiler start message
    printCmplrMsg();

    // Define a variable that can be used to decide if the compiler should attempt to start
    // compiling or not
    int allowCompile = 1;

    // Process the command line arguments
    processArgs(argc, argv, &allowCompile);

    // Process the input and output paths
    if(allowCompile && processIO(&cmplrInputFilePth, &cmplrOutputFilePth, &cmplrOutputFileName)){

        // Note that all the variables that were passed to the `processIO` function are now cleared,
        // All these variables were used to generate the `globalIO` object!

        // This is the content of the `globalIO` object:
        // (struct GlobalIO) {
        //     input: {
        //         fullPth: <absolute input file path>,
        //         dirPth: <absolute input file (folder) directory path>
        //     },
        //     output: {
        //         fullPth: <absolute output directory path>,
        //         fileName: <output file name>
        //     },
        //     wrkDir: <working directory path>,
        //     tempDir: <system's temporary directory>
        // }

        // Note that you are not allowed to change any of the `globalIO` object's values until the
        // end of the compiling process.

        // Now that we have all the information we need about the input and output paths, we need to
        // start the initial part of the compiling process
        initialComp(globalIO);

        // Print a warning about the state of the compiler
        consoleInfo("End of execution...");

        // Now that we're done with the compiling process, we don't need any of the remaining input
        // and output data!

        // Free up the used memory by the working directory variable
        free(globalIO.wrkDir);

        // Free up the used memory by the temporary directory variable
        free(globalIO.tempDir);

        // Free up the used memory by the input path variable
        free(globalIO.input.fullPth);

        // Free up the used memory by the input directory path variable
        free(globalIO.input.dirPth);

        // Free up the used memory by the output path variable
        free(globalIO.output.fullPth);

        // Free up the memory used by the output file name variable
        free(globalIO.output.fileName);

    }

    // Print a success message
    printExtMsg(0);

    // Return a SUCCESS exit code
    return EXIT_SUCCESS;

}

// Include the `stopProcess` function
#include "./process.c"