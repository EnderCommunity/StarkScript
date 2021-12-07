/**
 *
 *  Process the command line arguments
 *
**/


// Define the needed variabled for this process
// cmplrInputFilePth - the compiler input file path
// cmplrOutputFilePth - the compiler output file path
char *cmplrInputFilePth = NULL,
    *cmplrOutputFilePth = NULL,
    *cmplrOutputFileName = NULL;

// Define the function that will receive the command line arguments
void processArgs(int argc, char *argv[]){

    // Start a loop and go through all the arguments (except for the first argument, because it's
    // just the path of this file)
    for(int i = 1; i < argc; i++){

        // Print the current index and the current argument (debug)
        consoleDebug("[index: %d, value: \"%s\"]", i, argv[i]);

        // Check for any valid command line arguments
        // -input (Indicates that the next argument is going to be the path of the input file)
        // -output (Indicates that the next argument is going to be the path of the output directory)
        // -name (Indicates that the next argument is going to be the name of the output file)
        // -i (Same as -input)
        // -o <path> (Same as -output)
        // -n <path> (Same as -name)

        // Check if the user is passing the input file path
        if(strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "-input") == 0){

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

        }else if(strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "-output") == 0){ // Check if the
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

        }else if(strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "-name") == 0){ // Check if the
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

        }else{

            // Tell the user that this flag does not exist
            consoleWarn("The flag \"%s\" does not exist!", argv[i]);

        }

    }

}