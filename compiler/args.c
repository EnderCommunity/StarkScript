/**
 *
 *  Process the command line arguments
 *
**/


// Define the function that will receive the command line arguments
void processArgs(int argc, char *argv[]){

    // Start a loop and go through all the arguments (except for the first argument, because it's
    // just the path of this file)
    for(int i = 1; i < argc; i++){

        // Check if the compiler is in debug mode
        consoleDebug("[DEBUG] [index: %d, value: \"%s\"]\n", i, argv[i]);

    }

}