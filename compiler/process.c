/**
 *
 *  Manage the compiler process
 *
**/


// Define a function that stops the process without causing any memory leaks
// Note that watching out for any memory leaks on sudden termination is not really nesessary, as all operating
// systems nowadays take care of cleaning up after any program after its termination. However, it's
// better to watch out for these memory leaks for a better debugging experience.
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
    if(globalIO.input.dirPth != NULL){

        free(globalIO.input.dirPth);

    }
    if(globalIO.output.fullPth != NULL){

        free(globalIO.output.fullPth);

    }
    if(globalIO.output.fileName != NULL){

        free(globalIO.output.fileName);

    }

    // Print a failure message
    printExtMsg(1);

    // Use the built-in `exit` function to terminate the process
    exit(exitCode);

}