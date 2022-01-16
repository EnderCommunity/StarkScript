/**
 *
 *  Manage all the functions that are used to read data from the ".input" file!
 *
**/


// Define a function that can open a file stream to the ".input" file
FILE* openTmpInput(const char *tmpDir, const char *outputFileName){

    // Get the path of the ".input" file
    char *inputTmpFile = joinDirFileExt(tmpDir, outputFileName, STRING_IO_PREPROCESSOR_OUTPUT_EXT);

    // Open a file stream in read-only mode
    FILE *input = fopen(inputTmpFile, "r");

    // Free up the memory used by the "inputTmpFile" variable
    free(inputTmpFile);

    // Check if the file stream wasn't opened successfully
    if(input == NULL){

        consoleError("Can't access the \".%s\" temporary file!", 1, STRING_IO_PREPROCESSOR_OUTPUT_EXT);

    }

    // Return the file pointer
    return input;

}

// Define another version of the "lookUpKeyword" function that can look for more than one keyword
// at the same time
#define KEYWORDS_LIST_END "\0"
int lookUpKeywords(const char **result, FILE **input, char prvsChar, char *currChar, int *column, ...){

    // Reset the final keyword's value
    (*result) = NULL;

    // Create a `__builtin_va_list` list
    __builtin_va_list keywords;
    __builtin_va_start(keywords, column);

    // Loop through the va_list
    const char* currKeyword = __builtin_va_arg(keywords, const char*);
    while(currKeyword[0] != '\0'){

        if(lookUpKeyword(currKeyword, input, prvsChar, currChar, column)){

            // Update the final keyword variable
            (*result) = currKeyword;

            // Close the opened `__builtin_va_list` list
            __builtin_va_end(keywords);

            return 1;

        }

        // Update the current keyword
        currKeyword = __builtin_va_arg(keywords, const char*);

    }

    // Close the opened `__builtin_va_list` list
    __builtin_va_end(keywords);

    return 0;

}

// Define a function that can get the next character in the file
int getNextChar(FILE **input, char *currChar, int *column){

    // Get the next character
    (*currChar) = fgetc(*input);

    // Update the column value
    (*column)++;

    // Check if this is not the end of the file
    return ((*currChar) != EOF);

}

// Define a function that can get the previous character in the file
void getPrvChar(FILE **input, char *currChar, int *column){

    // Go two characters to the back
    fseek(*input, -2L, SEEK_CUR);
    (*column) -= 2;

    // Get the next character
    (*currChar) = getNextChar(input, currChar, column);

}