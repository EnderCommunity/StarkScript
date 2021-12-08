/**
 *
 *  Process the command line arguments
 *
**/


// Include the help catalog
#include "./help.c"

// Define the needed variabled for this process
// cmplrInputFilePth - the compiler input file path
// cmplrOutputFilePth - the compiler output file path
char *cmplrInputFilePth = NULL,
    *cmplrOutputFilePth = NULL,
    *cmplrOutputFileName = NULL;

// Define a function that defines the behaviour of preventive flags
void stopArgsPrc(int *argc, int *i, int *allowCompile){

    // Stop the loop
    *i = *argc;

    // Prevent the compiler from trying to compile anything
    *allowCompile = 0;

    // Free any variables and inform the user about them being ignored
    if(cmplrInputFilePth != NULL){

        // Warn the user about this variable being ignored
        consoleWarn("The passed input file path has been ignored!");

        free(cmplrInputFilePth);
        cmplrInputFilePth = NULL;

    }
    if(cmplrOutputFilePth != NULL){

        // Warn the user about this variable being ignored
        consoleWarn("The passed output directory path has been ignored!");

        free(cmplrOutputFilePth);
        cmplrOutputFilePth = NULL;

    }
    if(cmplrOutputFileName != NULL){

        // Warn the user about this variable being ignored
        consoleWarn("The passed output file name has been ignored!");

        free(cmplrOutputFileName);
        cmplrOutputFileName = NULL;

    }

}

// Define the function that will receive the command line arguments
void processArgs(int argc, char *argv[], int *allowCompile){

    // Start a loop and go through all the arguments (except for the first argument, because it's
    // just the path of this file)
    for(int i = 1; i < argc; i++){

        // Print the current index and the current argument (debug)
        // consoleDebug("[index: %d, value: \"%s\"]", i, argv[i]);

        // There are three types of commands:
        // normal            normal flags do nothing other than their job
        // preventive (p)    preventive flags prevent the compiler from starting the compiling
        //                   process
        // receptive (r)     receptive flags cause the compiler to treat the next argument as an
        //                   input value, not as a flag.

        // The valid command line flags are:
        // --input (r)      Indicates that the next argument is going to be the path of the input file
        // --output (r)     Indicates that the next argument is going to be the path of the output
        //                  directory
        // --name (r)       Indicates that the next argument is going to be the name of the output file
        // --no-gray        Indicates that the user does not wish to see any gray text in the console
        //                  (Note that this flag will take effect only after it's detection, so you may see
        //                  some gray text!)
        // --gcc (p)        Runs the "gcc -v" command
        // -i (r)           Same as --input
        // -o (r)           Same as --output
        // -n (r)           Same as --name

        // Check if the user is passing the input file path
        if(strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0){

            // Check if there is an argument after this one
            if(++i < argc){

                // Check if the `cmplrInputFilePth` is empty
                if(cmplrInputFilePth == NULL){

                    // Save the input file path
                    cmplrInputFilePth = calloc(strlen(argv[i]) + 1, sizeof(char));
                    strcpy(cmplrInputFilePth, argv[i]);

                }else{

                    // Show an error in the console tellling the user that only one input path can
                    // be passed at a time
                    consoleError("Only one input path can passed at a time!");

                }

            }else{

                // Show an error in the console telling the user that the compiler expected another
                // argument after this one
                consoleError("Expected another argument after the \"%s\" argument!", argv[--i]);

            }

        }else if(strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0){ // Check if the
                                                                    //user is passing the output
                                                                    // file path

            // Check if there is an argument after this one
            if(++i < argc){

                // Check if the `cmplrOutputFilePth` is empty
                if(cmplrOutputFilePth == NULL){

                    // Save the output file path
                    cmplrOutputFilePth = calloc(strlen(argv[i]) + 1, sizeof(char));
                    strcpy(cmplrOutputFilePth, argv[i]);

                }else{

                    // Show an error in the console tellling the user that only one output path can
                    // be passed at a time
                    consoleError("Only one output path can passed at a time!");

                }

            }else{

                // Show an error in the console telling the user that the compiler expected another
                // argument after this one
                consoleError("Expected another argument after the \"%s\" argument!", argv[--i]);

            }

        }else if(strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--name") == 0){ // Check if the
                                                                    //user is passing the output
                                                                    // file name

            // Check if there is an argument after this one
            if(++i < argc){

                // Check if the `cmplrOutputFilePth` is empty
                if(cmplrOutputFileName == NULL){

                    // Save the output file path
                    cmplrOutputFileName = calloc(strlen(argv[i]) + 1, sizeof(char));
                    strcpy(cmplrOutputFileName, argv[i]);

                }else{

                    // Show an error in the console tellling the user that only one output path can
                    // be passed at a time
                    consoleError("Only one output name can passed at a time!");

                }

            }else{

                // Show an error in the console telling the user that the compiler expected another
                // argument after this one
                consoleError("Expected another argument after the \"%s\" argument!", argv[--i]);

            }

        }else if(strcmp(argv[i], "--gcc") == 0){ // Print info about the gcc compiler

            // Stop this loop
            stopArgsPrc(&argc, &i, allowCompile);

            // Tell the user that he's going to see the output of the "gcc -v" command
            consoleInfo("Here is the output of the \"gcc -v\" command:");

            // Run the "gcc -v" command within a blue-coloured text context
            // (The output of this command may not be coloured, depending on your OS and terminal)
            consoleLog("%s", CONSOLE_COLOR_BLUE);
            system("gcc -v");
            consoleLog("%s", CONSOLE_COLOR_RESET);

        }else if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0){ // Check if the
                                                            // user is requesting the help catalog

            // Stop this loop
            stopArgsPrc(&argc, &i, allowCompile);

            // Call the help catalog function
            helpCatalog();

        }else if(strcmp(argv[i], "--no-gray") == 0){

            // Change the behaviour of the console functions to not allow any >>default<< gray text
            consoleNoGray = 1;

        }else{

            // Tell the user that this flag does not exist
            consoleWarn("The flag \"%s\" does not exist!", argv[i]);

        }

    }

}