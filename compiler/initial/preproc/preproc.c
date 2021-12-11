/**
 *
 *  Manage the preprocessor
 *
**/


// The first thing the preprocessor needs to do is combine all the files into a "mega input file"
// This is the combining format that the preprocessor is going to follow:
//
//
// (?) "<content>" represents random code, and "<import>" represents an importing narrative
//
// A file with this content:
//    ______________________________________________________
//   |                                                      |
//   |   <content>                                          |
//   |   <import>                                           |
//   |   <import>                                           |
//   |   <content>                                          |
//   |______________________________________________________|
//
// Will be like this when converted to a "mega input file":
//    ______________________________________________________
//   |                                                      |
//   |   <content>                                          |
//   |   #file ./example1.stark ? /path/to/example1.stark   |
//   |   <content>                                          |
//   |   #endfile                                           |
//   |   #file ./example2.stark ? /path/to/example2.stark   |
//   |   <content>                                          |
//   |   #endfile                                           |
//   |   <content>                                          |
//   |______________________________________________________|
//
//
// In short words, the preprocessor is going to replace each line that includes an import narrative
// with two guiding lines with the content of the imported file placed between those two lines.
//
// The opening guiding line follows this format:
// "#file <!library name>/<relative file path> ? <absolute file path>"
// And the closing guiding line follows this format:
// "#endfile"
//
// Only one import narrative is allowed per line, and no code is allowed to be placed in the same
// line with an import narrative.
//
// Note that Import narratives should be nest-able. (An import narrative is allowed to include
// other import narratives inside of it)

// Import the `opnImportFile` function and its related functions
#include "./files.c"

// Import all the comments-related functions
#include "./comments.c"

// Import all the quotes-related functions
#include "./quotes.c"

// Define a function that can be used recursively to process the file
void preprocR(FILE *inputFile, FILE *outputFile){

    // Get the first character in the file
    char currChar = fgetc(inputFile);

    // Keep track of the previous character
    char prvsChar = '\0';

    // You should watch out for quoted text, as quoted text may include valid statements, and we
    // should make sure to not process quoted text as normal statements!
    int inDoubleQuote = 0,
        inQuote = 0;

    // Keep track of comments, you don't want to accidentally process commented code!
    int inLinearComm = 0,
        inMultilinearComm = 0;

    // Watch out for the end of multi-linear comments! (It's important to never neglect whitespace
    // within multi-linear comments so the compiler won't lose track of the column count for any
    // code that may follow the comment)
    int multilinearCommEnd = 0,
        multilinearCommStart = 0;

    // Start a loop to look through all the characters within the input file
    // Only stop the loop when you reach the "end of file" character (EOF)
    //
    while (currChar != EOF){

        // Keep track of the text quoting status and the commenting status!

        // Check for quoting contexts
        checkForQuotes(&inQuote, &inDoubleQuote, currChar, prvsChar, inLinearComm, inMultilinearComm);

        // Check for and keep track of comment context
        checkForComments(&inputFile, &currChar, &inLinearComm, &inMultilinearComm, &multilinearCommStart, &multilinearCommEnd, inQuote, inDoubleQuote);

        // If you reach a new line character, make sure to reset the text quoting status
        // Even though this might be wrong syntax, you should
        if(currChar == '\n') {

            // New lines can end a quoting context
            inDoubleQuote = 0;
            inQuote = 0;

            // New lines are the end of a linear comment
            inLinearComm = 0;

        }

        // Notes:
        // inQuote & inDoubleQuote              A quoting context starts with the first quote and
        //                                      ends before the second quote.
        // inLinearComm                         A linear comment context starts with the first slash
        //                                      and ends before a new line character.
        // inMultilinearComm                    A multi-linear comment context starts with the first
        //                                      slash and ends with the last slash.

        // Check if you're in a context that can only include code that's intended to be ran
        if(!inQuote && !inDoubleQuote && !inLinearComm && !inMultilinearComm) {

            // Debug
            // consoleLog("%s", CONSOLE_COLOR_PURPLE);

            // The preprocessor is only responsible for filtering comments and importing files
            // The preprocessor is already filtering comments

            // Look for the "import" keyword
            // if(currChar == 'i'){
            //
            //     // ...
            //
            // }

        }else {

            // Debug
            // consoleLog("%s", CONSOLE_COLOR_RESET);

        }

        // Store the current character in the "prvsChar" variable
        prvsChar = currChar;

        // Check if you're not in a linear comment context
        if(!inLinearComm){

            // Check if you're in a multi-linear comment context
            if(inMultilinearComm){

                // Check if this is the end of a multi-linear comment
                if(multilinearCommEnd){

                    // Print two whitespaces
                    fprintf(outputFile, "  ");

                    // Update the status of the multi-linear comment context
                    inMultilinearComm = 0;
                    multilinearCommEnd = 0;

                }else if(multilinearCommStart){ // Check if this is the start of a multi-linear
                                                // comment

                    // Print two whitespaces
                    fprintf(outputFile, "  ");

                    // Update the multi-linear comment start variable
                    multilinearCommStart = 0;

                }else{

                    // Print whitespace so you won't lose track of the column number
                    // And allow line line characters to be printed normally so you won't lose track of
                    // line numbers
                    fprintf(outputFile, "%c", (currChar == '\n') ? '\n' : ' ');

                }

            }else{

                // Print the output (temp)
                // Replace this with a function that will write the output content into the output file
                // pointer
                fprintf(outputFile, "%c", currChar);

            }

        }

        // Get the next character
        currChar = fgetc(inputFile);

    }

    // Close the file stream
    fclose(inputFile);

}

// Define a function that triggers the preprocessor
void preproc(char *inputPth, char *tempDir, char *inputDir, char *outputFileName){

    // You are not allowed to modify any of this function's arguments

    // Open a file stream in read-only mode to read the content of the input file
    FILE *inputFile = fopen(inputPth, "r");

    // Check if the file stream wasn't opened successfully
    if(inputFile == NULL){

        // Tell the user that the input file is inaccessible
        consoleError("Couldn't access the input file!");

    }

    // Get the path of the temporary "mega file"
    char *outputFileDir = calloc(strlen(tempDir) + 1 + strlen(outputFileName) + 1 + strlen(STRIING_IO_PREPROCESSOR_OUTPUT_EXT) + 1, sizeof(char));
    sprintf(outputFileDir, "%s/%s.%s", tempDir, outputFileName, STRIING_IO_PREPROCESSOR_OUTPUT_EXT);

    // Create the temporary "mega file"
    FILE* outputFile = fopen(outputFileDir, "w");

    // Free the memory used by the "outputFileDir" variable
    free(outputFileDir);

    // Call the recursive function
    preprocR(inputFile, outputFile);

    // Close the output file stream
    fclose(outputFile);

}