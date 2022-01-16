/**
 *
 *  Manage all the functions that are used to write data into the ".lexicon" file!
 *
**/


// Define a function that takes care of making the lexer's output file
FILE* createLexerFile(const char *tmpDir, const char *fileName){

    // Get the path of the ".lexeme" file
    char *outputTmpFile = joinDirFileExt(tmpDir, fileName, STRING_IO_LEXER_OUTPUT_EXT);

    // Open a file stream in write-only mode
    FILE *output = fopen(outputTmpFile, "w");

    // Free up the memory used by the "outputTmpFile" variable
    free(outputTmpFile);

    // Check if the file stream wasn't opened successfully
    if(output == NULL){

        consoleError("Can't create the \".%s\" temporary file!", 1, STRING_IO_LEXER_OUTPUT_EXT);

    }

    // Return the file pointer
    return output;

}

// Define a function that can be used to write a lexer into the output file
void writeLexeme(FILE **output, const char *type, const int line, const int column,
                    const char *format, ...){

    // This is the general format of a lexeme line:
    //  ___________________________________________________________________________
    // |                                                                           |
    // | XXXXXXXXXXXXXXXXXXXXXXXX   0x0000000000 0x0000000000      ...             |
    // | ^^ type ^^                 ^^ line ^^   ^^ column ^^      ^^ extra data   |
    // |___________________________________________________________________________|
    //

    // Check the type's length
    if(strlen(type) > 24){

        // Inform the user about an illegal type name!
        consoleError("Illegal lexeme type name! (24 max length)", 1);

    }

    // Print the lexeme's type
    fprintf(*output, "%s", type);
    for(int i = 0, len = (24 - strlen(type)); i < len; i++){

        fprintf(*output, " ");

    }

    // Print the lexeme's source line number
    fprintf(*output, "\t0x%010X", line);

    // Print the lexeme's source column number
    fprintf(*output, " 0x%010X\t", column);

    // Create a `__builtin_va_list` list
    __builtin_va_list extraData;
    __builtin_va_start(extraData, format);

    // Loop through the va_list
    int readLen = 0;
    while(readLen != strlen(format)){

        // Check if this is an integer
        if(format[readLen] == 'd'){

            // Print the current value
            fprintf(*output, "%d\t", __builtin_va_arg(extraData, const int));


        }else if(format[readLen] == 'f'){ // Check if this is a float/double

            // Print the current value
            fprintf(*output, "%f\t", __builtin_va_arg(extraData, const double));

        }else if(format[readLen] == 'c'){ // Check if this is a char

            // Print the current value
            fprintf(*output, "%c\t", __builtin_va_arg(extraData, const int));

        }else if(format[readLen] == 's'){ // Check if this is a string

            // Print the current value
            fprintf(*output, "%s\t", __builtin_va_arg(extraData, const char*));

        }else{

            // Inform the user about this invalid type!
            consoleError("Invalid lexeme format type!", 1);

        }

        // Get the next value
        readLen++;

    }

    // ...

    // Print a new line
    fprintf(*output, "\n");

    // Close the opened `__builtin_va_list` list
    __builtin_va_end(extraData);

}
