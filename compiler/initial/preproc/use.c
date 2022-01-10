/**
 *
 *  Manage functions that are related to the "use" context
 *
**/


// Define a function that can get the path of a library
char* procLibPath(char *libCall, const char *libsDir){

    // Prepare the dir path variable
    char *libCallDir = calloc(strlen(libCall) + 1, sizeof(char));

    // Replace all the dots with slashes
    for(int i = 0; i <= strlen(libCall); i++){

        if(libCall[i] == '.'){

            #ifdef _WIN32

                libCallDir[i] = '\\';

            #else

                libCallDir[i] = '/';

            #endif

        }else{

            libCallDir[i] = libCall[i];

        }

    }

    //Prepare the return string
    char *fnlPth = joinDirFileExt(libsDir, libCallDir, "stark");

    // Free the memory used by the `libCallDir` variable
    free(libCallDir);

    // Return the library's path
    return fnlPth;

}

// Define a function that will return the output of a use narrative
void outputUse(FILE **inputFile, FILE **outputFile, char *currChar, char prvsChar,
                    int *injectionWhitespace, int line, int *column, const char *codePath,
                    const char *filePath, int *processedFiles, const char *libsDir,
                    char **latestLibPath, int *latestLibPathSize, int *useContextStartColumn,
                    int *useContextStart){

    // Check if you've reached the end of the "use" context
    if((*currChar) == ';'){

        // Add the missing whitespace for the "use" keyword
        (*injectionWhitespace) += strlen(PREPROC_KEYWORD_INCLUDE_LIBRARY);

        // Close the latestLibPath string
        (*latestLibPath)[(*latestLibPathSize) - 1] = '\0';

        // Get the library's path
        char* libPath = procLibPath((*latestLibPath), libsDir);

        // Debug
        consoleDebug("Found library path (%s): %s", (*latestLibPath), libPath);

        // Inject the content of the library
        injectFile(*inputFile, *outputFile, processedFiles, codePath, filePath, line,
                    *useContextStartColumn, (*latestLibPath), libPath, libsDir);

        // Free the memory used by the `libPath` variable
        free(libPath);

        // Reset the `latestLibPath` variable
        free((*latestLibPath));
        (*latestLibPathSize) = 1;
        (*latestLibPath) = calloc((*latestLibPathSize), sizeof(char));

        // Get out of the "use" context
        (*useContextStart) = 0;
        (*useContextStartColumn) = 0;

        // Print an escape character to confirm the end of the imported section
        (*currChar) = CHAR_SPECIAL_ESCAPE[0];

    }else if((*currChar) == '\n' || (*currChar) == '\r'){ // Check if you're in a new line now

        // You are not allowed to go to new lines within a use context, report this to the user!
        preprocError(*inputFile, *outputFile, STR_ERROR_000005, codePath, filePath, line,
                        *column, 1, 1);

    }else if(isalpha((*currChar)) && prvsChar == ' ' && (
                    (*latestLibPathSize) - 2 >= 0 &&
                    (*latestLibPath)[(*latestLibPathSize) - 2] != '.'
                )){

        // Invalid syntax!
        preprocError(*inputFile, *outputFile, STR_ERROR_000010, codePath, filePath, line,
                        (*column) - 1, 2, 0);

    }else if((*currChar) == '.' && (*latestLibPathSize) - 2 >= 0 &&
                            (*latestLibPath)[(*latestLibPathSize) - 2] == '.'){

        // A dot may only be followed by a character
        preprocError(*inputFile, *outputFile, STR_ERROR_000009, codePath, filePath, line, *column,
                        2, 0);

    }else if(!isalpha((*currChar)) && (
                isdigit((*currChar)) &&
                    ((*latestLibPathSize) - 2 < 0 ||
                    !isalpha((*latestLibPath)[(*latestLibPathSize) - 2]))
            )){ // Only allow characters, numbers, and dots (numbers at the start of symbols are
                // not allowed)

        // Library paths may only start with an alphabetical character and contain normal
        // characters and numbers
        preprocError(*inputFile, *outputFile, STR_ERROR_000006, codePath, filePath, line, *column,
                        1, 0);

    }else{

        // Save the current character in the `latestLibPath` variable
        (*latestLibPath) = realloc((*latestLibPath), (++(*latestLibPathSize))*sizeof(char));
        (*latestLibPath)[(*latestLibPathSize) - 2] = (*currChar);

    }

}
