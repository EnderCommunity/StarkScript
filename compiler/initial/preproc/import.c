/**
 *
 *  Manage functions that are related to the "import" context
 *
**/


// Define some special characters that are used by import-related functions
// For more info, read: https://en.wikipedia.org/wiki/Escape_sequences_in_C
#define CHAR_SPECIAL_FILE_SEPARATOR "\f"
#define CHAR_SPECIAL_ESCAPE "\e"
#define CHAR_SPECIAL_VERTICAL_TAB "\v"

// Define a function that can inject a file's content into the "mega" input file
void injectFile(FILE *inputFile, FILE *outputFile, int *processedFiles, const char *codePath,
                        const char *filePath, int line, int column, char *importPath,
                        char *absImportPath, const char *libsDir){

    // Inject the file info
    fprintf(outputFile, "%s<%s>%s", importPath, absImportPath, CHAR_SPECIAL_VERTICAL_TAB);

    // Get the codePath for this file
    char *importCodePath = createCodePath(codePath, filePath, line, column);

    // Open the imported file
    FILE *importFile = fopen(absImportPath, "r");

    // Check if the file stream wasn't opened successfully
    if(importFile == NULL){

        // Free the memory used by the `importCodePath` variable
        free(importCodePath);

        // Report this error to the user
        preprocError(inputFile, outputFile, STR_ERROR_000008, codePath, filePath, line, column,
                        1, 0);

    }else{

        // Start injecting the content of the import file
        preprocR(importFile, outputFile, processedFiles, importCodePath, importPath, libsDir);

        // Close the opened stream to the imported file
        fclose(importFile);

        // Free the memory used by the `importCodePath` variable
        free(importCodePath);

    }

}

// Define a function that will return the output of an import narrative
void outputImport(FILE **inputFile, FILE **outputFile, char *currChar, int *injectionWhitespace,
                    int line, int *column, const char *codePath, const char *filePath, int inQuote,
                    int *inDoubleQuote, int *importContextStart, int *processedFiles, const char *libsDir){

    // Print a white space character for each character you deal with to keep the column value
    // intact
    (*injectionWhitespace) += strlen(PREPROC_KEYWORD_INCLUDE_FILE);

    // Check if you're in a new line now
    if(*currChar == '\n' || *currChar == '\r'){

        // Temp
        preprocError(*inputFile, *outputFile, STR_ERROR_000002, codePath, filePath, line, *column,
                        1, 1);

    }else if(inQuote){ // Check if you're in a quoting context

        // Temp
        preprocError(*inputFile, *outputFile, STR_ERROR_000003, codePath, filePath, line, *column,
                        1, 0);

    }else if(*inDoubleQuote){ // Check if you're in a double-quoting context

        // Keep track of the import start column value for reports
        int startColumn = *column;

        // Get the first character in the quoting context
        (*injectionWhitespace)++;
        *currChar = fgetc(*inputFile);
        (*column)++;

        // Skip whitespace
        while(*currChar == ' '){

            // Get the next character
            (*injectionWhitespace)++;
            *currChar = fgetc(*inputFile);
            (*column)++;

        }

        // Prepare the path string
        int importPathSize = 1;
        char *importPath = calloc(importPathSize, sizeof(char));

        // Get the import path
        while(*currChar != '"'){

            // Check if this is a new line!
            if(*currChar == '\r' || *currChar == '\n'){

                preprocError(*inputFile, *outputFile, STR_ERROR_000007, codePath, filePath, line,
                                (*column) - 1, 1, 1);

            }

            // Copy the current character
            importPath = realloc(importPath, (++importPathSize)*sizeof(char));
            importPath[importPathSize - 2] = *currChar;

            // Get the next character
            (*injectionWhitespace)++;
            *currChar = fgetc(*inputFile);
            (*column)++;

        }
        importPath[importPathSize - 1] = '\0';

        // Get the next character
        (*inDoubleQuote) = 0;
        (*injectionWhitespace)++;
        *currChar = fgetc(*inputFile);
        (*column)++;

        // Skip whitespace
        while(*currChar == ' '){

            // Get the next character
            (*injectionWhitespace)++;
            *currChar = fgetc(*inputFile);
            (*column)++;

        }

        if(*currChar != ';'){

            preprocError(*inputFile, *outputFile, STR_ERROR_000004, codePath,
                            filePath, line, *column, 1, 0);

        }else{

            consoleDebug("Import path detected: %s", importPath);

            // Get the absolute path of the import file
            char *absoluteImportPath = absPth(importPath);

            // Inject the import file content
            injectFile(*inputFile, *outputFile, processedFiles, codePath, filePath, line,
                                startColumn, importPath, absoluteImportPath, libsDir);

            // Free up the memory used by the `absoluteImportPath` and `importPath` variables
            free(absoluteImportPath);
            free(importPath);

            // Set the import context status to "false"
            (*importContextStart) = 0;

            // Replace the current character with an espace character
            *currChar = CHAR_SPECIAL_ESCAPE[0];

        }

    }else if(*currChar != ' '){

        // Temp
        preprocError(*inputFile, *outputFile, STR_ERROR_000004, codePath, filePath, line, *column,
                        1, 0);

    }

}