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

// Include the standard input and output library
#include <stdio.h>

// Include the standard library
#include <stdlib.h>

// Include the strings library (which included functions that are useful when dealing with strings)
#include <string.h>

// Define the start time variable
clock_t startTime;

// Include the compiler flags
#include "./flags.h"

// Pre-define the `stopProcess` function so all the included files can use it
void stopProcess(int exitCode);

// Include all the paths-related functions
#include "./paths.c"

// Include all the console-related functions
#include "./cli/console.c"

// Include all the system-related functions
#include "./system.c"

// Include the start message function
#include "./cli/message.c"

// Pre-define the `randNumStr` function so code inside the io.c file can access it
void randNumStr(char *dest, size_t length);

// Include the input and output paths processing function
#include "./cli/io.c"

// Include the command line arguments processing function
#include "./cli/args.c"

// Include the initial compiling components
#include "./initial/initial.c"

// Include all the randomness-related functions
#include "./random.c"

// Define the main function
int main(int argc, char *argv[]){

    // Keep track of the start time
    startTime = clock();

    // Prepare the random number generator
    randInit();

    // Define a variable that can be used to decide if the compiler should attempt to start
    // compiling or not
    int allowCompile = 1;

    // Print the compiler start message
    printCmplrMsg();

    // Process the command line arguments
    processArgs(argc, argv, &allowCompile);

    /// Check if the compiler is allowed to compile files
    if(allowCompile){

        // Process the input and output paths
        processIO(&cmplrInputFilePth, &cmplrOutputFilePth, &cmplrOutputFileName);

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

        // Now, you should have two files in the temporary directory!
        // A ".input" file, and a ".lex" file!
        // You should only care about the ".lex" file. It contains an organised list of all the
        // content of the ".input" file!

        // ...

        // Now that we're done with the compiling process, we don't need any of the remaining input
        // and output data!

        // Check if the user wishes to get a copy of the temporary files
        if(outputSaveTemps){

            // Get the path expression of all the files in the temporary directory
            char *tempDirFiles = joinDirFile(globalIO.tempDir, "*");

            // Move the ".input" file to the output directory
            systemf("%s%s %s", strlen(SYSTEM_COMMAND_MOVE_FILE) + strlen(tempDirFiles) + 1
                                + strlen(globalIO.output.fullPth) + 1,
                    SYSTEM_COMMAND_MOVE_FILE, tempDirFiles, globalIO.output.fullPth);

            // Free up the memory used by the "tempDirFiles" variable
            free(tempDirFiles);

        }

        // Now that you have no other use for the temporary files within the temporary folder, you
        // can delete the whole directory!

        // Execute the delete command
        systemf("%s%s", strlen(SYSTEM_COMMAND_REMOVE_FULL_DIR) + strlen(globalIO.tempDir) + 1,
                    SYSTEM_COMMAND_REMOVE_FULL_DIR, globalIO.tempDir);

        // Check if the temporary folder is still accessible
        if(access(globalIO.tempDir, F_OK) == 0){

            // Warn the use about the temporary folder not being deleted
            consoleWarn("Couldn't delete the temporary directory!");

        }

        // Now, start freeing up all the globally-defined variables!

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

        // Print a success message
        printExtMsg(0, -1);

    }else{

        // Print a success message but with a "no compile" status
        printExtMsg(0, 0);

    }

    // Return a SUCCESS exit code
    return EXIT_SUCCESS;

}

// Include the `stopProcess` function
#include "./process.c"
