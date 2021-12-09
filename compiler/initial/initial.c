/**
 *
 *  Manage the initial part of the compiling process
 *
**/


// The initial part of the compiling process consists of the preprocessor, and the lexer!

// The preprocessor is the part of the compiler that takes care of removing meaningless text within
// the language files, and it also combines all the used language files into one big file. We will
// be calling this file the "mega input file"...
#include "./preproc/preproc.c"

// The lexer is the part of the compiler that takes care of listing, identifying, and assigning
// types to every word and character within the "mega input file"...
#include "./lexer/lexer.c"

// Define a function that triggers the initial part of compiling
void initialComp(struct GlobalIO globalIO){

    // Open a file stream in read-only mode to read the content of the input file
    FILE *inputFile = fopen(globalIO.input.fullPth, "r");

    // Check if the file stream wasn't opened successfully
    if(inputFile == NULL){

        // Tell the user that the input file is inaccessible
        consoleError("Couldn't access the input file!");

    }

    // Trigger the preprocessor
    preproc(inputFile);
    
    // Trigger the lexer
    lexer();

    // Close the file stream
    fclose(inputFile);

}