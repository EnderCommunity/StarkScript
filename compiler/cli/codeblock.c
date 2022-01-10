/**
 *
 *  Manage all the functions that generate the code block preview for the console report
 *
**/


// Define a function that can underline text
#define UNDERLINE_BOLD_LENGTH 4 + 4
void underlineCodeBlock(int *size, char **codeBlock, int *l){

    //
    // Allocate the needed memory for the current colour string
    *size += UNDERLINE_BOLD_LENGTH;
    *codeBlock = realloc(*codeBlock, (*size)*(sizeof(char)));

    // For more info about these escape characters, visit:
    // https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797#colors--graphics-mode

    // Underline the text!
    (*codeBlock)[(*l)++] = '\e';
    (*codeBlock)[(*l)++] = '[';
    (*codeBlock)[(*l)++] = '4';
    (*codeBlock)[(*l)++] = 'm';

    // Make the text more bold!
    (*codeBlock)[(*l)++] = '\e';
    (*codeBlock)[(*l)++] = '[';
    (*codeBlock)[(*l)++] = '1';
    (*codeBlock)[(*l)++] = 'm';

}

// Define a function that can undo the underline style in the code-block
#define UNDO_UNDERLINE_BOLD_LENGTH 5 + 5
void undoUnderlineCodeBLock(int *size, char **codeBlock, int *l){

    //
    // Allocate the needed memory for the current colour string
    *size += UNDO_UNDERLINE_BOLD_LENGTH;
    *codeBlock = realloc(*codeBlock, (*size)*(sizeof(char)));

    // For more info about these escape characters, visit:
    // https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797#colors--graphics-mode

    // Un-underline the text!
    (*codeBlock)[(*l)++] = '\e';
    (*codeBlock)[(*l)++] = '[';
    (*codeBlock)[(*l)++] = '2';
    (*codeBlock)[(*l)++] = '4';
    (*codeBlock)[(*l)++] = 'm';

    // Remove the bold text style
    (*codeBlock)[(*l)++] = '\e';
    (*codeBlock)[(*l)++] = '[';
    (*codeBlock)[(*l)++] = '2';
    (*codeBlock)[(*l)++] = '2';
    (*codeBlock)[(*l)++] = 'm';

}

// Define a function that can add the line number prefix into a code block string
void codeBlockPrefix(int *size, char **codeBlock, int *l, int line, const char *linePrefixColor,
                        const char *lineColor, const int fixUnderline){

    // Check if you're allowed to print coloured console messages
    if(consoleColors){

        // Check if this line should be underline-fixed
        if(fixUnderline){

            // Reset the underline style in the code-block
            undoUnderlineCodeBLock(size, codeBlock, l);

        }

        // Allocate the needed memory for the colour string
        (*size) += strlen(linePrefixColor);
        *codeBlock = realloc(*codeBlock, (*size)*(sizeof(char)));

        // Copy the colour string
        for(int i = 0; i < strlen(linePrefixColor); i++){

            (*codeBlock)[(*l)++] = linePrefixColor[i];

        }

    }

    // Allocate the needed memory for the line number
    (*size) += 7;
    *codeBlock = realloc(*codeBlock, (*size)*(sizeof(char)));

    // Get the length of the number that's going to be converted
    // Source: https://stackoverflow.com/questions/8257714/how-to-convert-an-int-to-string-in-c
    int numLength = (int)(ceil(log10(line))) + (line % 10 == 0);
                                            //  ^ This seems to solve a bug that occures when a
                                            //    number ends with a zero... 

    // Get the current line in a string form
    char *currLineStr;
    if(line > 1){

        currLineStr = calloc(numLength + 1, sizeof(char));
        sprintf(currLineStr, "%d", line);

    }else{

        // For some reason, this method breaks when you try to get the number 1 as a string. So, 
        // for the time being, it is better to check for the number one separately.
        numLength = 1;
        currLineStr = calloc(1 + 1, sizeof(char));
        sprintf(currLineStr, "1");

    }

    // Copy the line number
    (*codeBlock)[(*l)++] = (consoleColors) ? ' ' : '=';
    if(numLength > 4){

        // Only add the first digit and add three dots to indicate that the number is long...
        (*codeBlock)[(*l)++] = currLineStr[0];
        (*codeBlock)[(*l)++] = '.';
        (*codeBlock)[(*l)++] = '.';
        (*codeBlock)[(*l)++] = '.';

    }else{

        // Go though the max four line digits
        for(int i = 0; i < 4; i++){

            // Check if the current character actually contains a digit
            if(i < numLength){

                // Copy the current digit from the number string
                (*codeBlock)[(*l)++] = currLineStr[i];

            }else{

                // Replace the current character with whitespace
                (*codeBlock)[(*l)++] = ' ';

            }

        }

    }
    (*codeBlock)[(*l)++] = (consoleColors) ? ' ' : '=';

    // Check if you're allowed to print coloured console messages
    if(consoleColors){

        // Allocate the needed memory for the content colour string
        (*size) += strlen(lineColor);
        *codeBlock = realloc(*codeBlock, (*size)*(sizeof(char)));

        // Copy the colour string
        for(int i = 0; i < strlen(lineColor); i++){

            (*codeBlock)[(*l)++] = lineColor[i];

        }

    }

    (*codeBlock)[(*l)++] = ' ';

    // Free up the memory used by the `currLineStr` variable
    free(currLineStr);

    // Check if the content in this line should be underlined!
    if(consoleColors && fixUnderline){

        // Start underline-ing the code-block
        underlineCodeBlock(size, codeBlock, l);

    }

}

// Re-cure the final code-block string
char* evenLinesCodeBlock(char *codeBlock, int maxColumn, int prefixLength, int specialPrefixLength,
                            int triggerLineStart, int triggerLineEnd, int lastLine){

    // maxColumn + prefixLength                 This should be the length of normal lines
    //
    // UNDERLINE_BOLD_LENGTH                    This string should be accounted for in the first
    //                                          trigger line
    //
    // UNDO_UNDERLINE_BOLD_LENGTH               This string should be accounted for in the last
    //                                          trigger line
    //
    // maxColumn + specialPrefixLength +        This should be the length of trigger lines (not the
    // UNDERLINE_BOLD_LENGTH                    first and the last!)
    //
    // triggerLineStart                         The first trigger line relative number
    //
    // triggerLineEnd                           The last trigger line relative number

    // Define the return variable
    int size = 0, l = 0;
    char *finalCodeBlock = calloc(size, sizeof(char));

    // Keep track of the relative line number and the lines' length
    int line = 1, length = 0;

    // Start going through the `codeBlock` variable!
    int i = -1, keepLoop = 1;
    while(codeBlock[((!keepLoop) ? i : ++i)] != '\0' || keepLoop){

        // Do this so the loop will also check for the last line and even it with the rest of the
        // lines
        if(codeBlock[i] == '\0'){

            keepLoop = 0;

        }

        // Check if this is a new line/the last line
        if(codeBlock[i] == '\n' || codeBlock[i] == '\0'){

            // Allocate memory for the current character
            size += 1 + 4;
            finalCodeBlock = realloc(finalCodeBlock, (size)*sizeof(char));

            // Even all the lines
            {

                // Note: Yeah, I pretty much forgot to add comments to why each condition exits here. If
                // something breaks, just keep changing the values randomly until a valid output appears on
                // the screen...

                // Get the "real" length of the current line 
                // (Get the length of the characters that WILL appear on the screen)
                int charLength = 0;
                if(line < triggerLineStart){
                 
                    charLength = length - prefixLength;

                }else if(line > triggerLineEnd){

                    charLength = length - prefixLength;

                }else if(line == triggerLineStart){

                    // Check if this is the only trigger line
                    if(line == triggerLineEnd){

                        charLength = length - specialPrefixLength  - (UNDERLINE_BOLD_LENGTH +
                                        UNDO_UNDERLINE_BOLD_LENGTH);

                    }else{

                        charLength = length - specialPrefixLength  - (UNDERLINE_BOLD_LENGTH);

                    }

                }else{

                    // Check if this the last trigger line
                    if(line == triggerLineEnd){

                        charLength = length - specialPrefixLength - (UNDO_UNDERLINE_BOLD_LENGTH +
                                        UNDERLINE_BOLD_LENGTH);

                        if(lastLine != line){

                            charLength -= UNDO_UNDERLINE_BOLD_LENGTH;

                        }

                    }else{

                        charLength = length - specialPrefixLength - (UNDO_UNDERLINE_BOLD_LENGTH +
                                        UNDERLINE_BOLD_LENGTH);

                    }

                }

                // Allocate memory for the whitespace character
                size++;
                finalCodeBlock = realloc(finalCodeBlock, (size)*sizeof(char));

                // Copy a whitespace character
                finalCodeBlock[l++] = ' '; // This represents the new line character ("\n")

                // Remove any potentially-existing lightlighting
                undoUnderlineCodeBLock(&size, &finalCodeBlock, &l);

                // Add more whitespace
                int delta = maxColumn - charLength;
                while(delta-- > 0){

                    // Allocate memory for the whitespace character
                    size++;
                    finalCodeBlock = realloc(finalCodeBlock, (size)*sizeof(char));

                    // Copy the whitespace character
                    finalCodeBlock[l++] = ' ';

                }

            }

            // Add some whitespace at the end of the line
            finalCodeBlock[l++] = ' ';

            // Reset the style of the current line
            finalCodeBlock[l++] = '\e';
            finalCodeBlock[l++] = '[';
            finalCodeBlock[l++] = '0';
            finalCodeBlock[l++] = 'm';

            // Update the relative line number
            line++;

            // Update the line length
            length = -1;

        }

        // Allocate memory for the current character
        size++;
        finalCodeBlock = realloc(finalCodeBlock, (size)*sizeof(char));

        // Copy the current character
        finalCodeBlock[l++] = codeBlock[i];

        // Update the line length
        length++;

    }

    // Return the final value
    return finalCodeBlock;

}

// Define a function that will return a code block from the file that's causing the error/warning
// as a sample for the user
#define REPORT_ERROR 0
#define REPORT_WARN 1
char* reportCodeBlock(char *filePth, int line, int column, int height, int endColumn, int type){

    // Allocate memory for the return string
    int size = 1, l = 0;
    char *codeBlock = calloc(size, sizeof(char));

    // Open a file stream in read-only mode
    FILE *file = fopen(filePth, "r");

    // Check if the file stream was opened successfully
    if(file == NULL){

        // Free up the memory used by the `codeBlock` variable
        free(codeBlock);

        // Tell the user that the input file is inaccessible
        consoleError("Couldn't access a file while generating a report!", 1);

    }

    // Keep track of the lines and columns in this file
    int currLine = 1, currColumn = 1;

    // Get the line colours
    const char *linePrefixColor = (CONSOLE_CODE_BLOCK_LINE),
                *lineColor = (CONSOLE_CODE_BLOCK),
                *linePrefixColorSpecial = (type == REPORT_ERROR) ?
                                            CONSOLE_CODE_BLOCK_LINE_ERROR :
                                            CONSOLE_CODE_BLOCK_LINE_WARN,
                *lineColorSpecial = (type == REPORT_ERROR) ?
                                        CONSOLE_CODE_BLOCK_ERROR :
                                        CONSOLE_CODE_BLOCK_WARN;

    // Get the shared line prefix characters length
    // You need to do this so you can organise the lines and make theme all even in length!
    // Of course, this is not a very good approach to print out the code block, but it's going to
    // have to do for now!
    int prefixLength = 7, specialPrefixLength = prefixLength;
    if(consoleColors){

        prefixLength += strlen(linePrefixColor) + strlen(lineColor);
        specialPrefixLength += strlen(linePrefixColorSpecial) + strlen(lineColorSpecial);

    }

    // Add the start prefix line
    if(line - 2 > 1){

        // Check if you're allowed to print coloured console messages
        if(consoleColors){

            // Allocate the needed memory for the colour string
            size += strlen(linePrefixColor);
            codeBlock = realloc(codeBlock, (size)*sizeof(char));

            // Copy the colour string
            for(int i = 0; i < strlen(linePrefixColor); i++){

                codeBlock[l++] = linePrefixColor[i];

            }

        }

        // Allocate the needed memory for the start prefix
        size += 6;
        size += 5;
        codeBlock = realloc(codeBlock, (size)*sizeof(char));

        // Copy the start prefix
        for(int i = 0; i < 6; i++){

            codeBlock[l++] = ' ';

        }
        if(consoleColors){

            // Allocate the needed memory for the content colour string
            size += strlen(lineColor);
            codeBlock = realloc(codeBlock, (size)*sizeof(char));

            // Copy the colour string
            for(int i = 0; i < strlen(lineColor); i++){

                codeBlock[l++] = lineColor[i];

            }

        }
        codeBlock[l++] = ' ';
        codeBlock[l++] = '.';
        codeBlock[l++] = '.';
        codeBlock[l++] = '.';
        codeBlock[l++] = '\n';

    }else{

        // Check if this is a line that triggered this report
        int isSpecial = (currLine >= line) && (currLine + 1 <= line + height);

        // Add the new line prefix
        codeBlockPrefix(&size, &codeBlock, &l, 1, (isSpecial) ?
                                                                linePrefixColorSpecial :
                                                                linePrefixColor,
                        (isSpecial) ?
                            lineColorSpecial :
                            lineColor,
                        (currLine + 1 > line && isSpecial));


    }
    // Keep track of the max column length
    int maxColumn = 1;

    // Keep track of the trigger lines start and end (relative to the final `codeBlock` string)
    int triggerLineStart = -1,
        triggerLineEnd = -1,
        relativeLine = 1;


    // Get the first character in the file
    char currChar = fgetc(file);
    while(currChar != EOF){

        // Allow the lines that contain the error/warning to printed, with a two-lines-offset print!
        // (Print the lines starting from two lines before the first line that triggered the
        // error/warning and ending in the second line after the last line that triggered the
        // error/warning)
        //  ____________________________________________________________________________
        // |                                                                            |
        // |  <normal_code>                                                             |
        // |  <normal_code>                                                             |
        // |----------------------------------------------------------------------------|
        // |  <normal_code>                                                             |
        // |  <normal_code>                                                             |
        // |  <trigger>                                                                 |
        // |  <trigger>                                                                 |
        // |  <trigger>                                                                 |
        // |  <normal_code>                                                             |
        // |  <normal_code>                                                             |
        // |----------------------------------------------------------------------------|
        // |  <normal_code>                                                             |
        // |____________________________________________________________________________|
        // Note: Ignore the '\r' special character to make the process of evening the lines easier
        if((currLine >= (line - 2) && currLine <= (line + height + 2)) && currChar != '\r'){

            // Allocate the needed memory for the current character
            size++;
            codeBlock = realloc(codeBlock, (size)*sizeof(char));

            // Copy the current character into the output string
            codeBlock[l++] = currChar;

            // Check if the console supports using colours
            if(consoleColors){

                // Check if this is the column that the trigger starts at
                if((currColumn == column) && (currLine == line)){

                    // Start underline-ing the code-block
                    underlineCodeBlock(&size, &codeBlock, &l);

                    // Update the status of the relative trigger lines values
                    triggerLineStart = relativeLine;

                }

                // Check if this is the column that the trigger ends at
                if((currColumn == endColumn + 1) && (currLine == line + height)){

                    // Reset the underline style in the code-block
                    undoUnderlineCodeBLock(&size, &codeBlock, &l);

                    triggerLineEnd = relativeLine;

                }

            }

        }
        if(currLine >= (line - 3) && currLine <= (line + height + 1)){

            // Check if this is a new line
            if(currChar == '\n'){

                // Check if this is a line that triggered this report
                int isSpecial = (currLine + 1 >= line) && (currLine + 1 <= line + height);

                // Add the new line prefix
                codeBlockPrefix(&size, &codeBlock, &l, currLine + 1, (isSpecial) ?
                                                                        linePrefixColorSpecial :
                                                                        linePrefixColor,
                                (isSpecial) ?
                                    lineColorSpecial :
                                    lineColor,
                                (currLine + 1 > line && isSpecial));

                relativeLine++;

            }

        }

        // Check if this is a new line
        if(currChar == '\n'){

            // Keep track of the max column length
            if(currColumn > maxColumn){

                // Update the max column value
                maxColumn = currColumn;

            }

            // Update the current line and column
            currLine++;
            currColumn = 1;

        }

        currChar = fgetc(file);
        currColumn++;

    }

    // Check if the file finished with a trigger line
    if(triggerLineEnd == -1){

        // Correct the value of `triggerLineEnd`
        triggerLineEnd = relativeLine;

    }

    // Add the end line
    if(currLine > line + height + 2){

        // Check if you're allowed to print coloured console messages
        if(consoleColors){

            // Allocate the needed memory for the colour string
            size += strlen(linePrefixColor);
            codeBlock = realloc(codeBlock, (size)*sizeof(char));

            // Copy the colour string
            for(int i = 0; i < strlen(linePrefixColor); i++){

                codeBlock[l++] = linePrefixColor[i];

            }

        }

        // Allocate the needed memory for the "end" line
        size += 6;
        size += 4;
        codeBlock = realloc(codeBlock, (size)*sizeof(char));

        // Copy the "end" line
        for(int i = 0; i < 6; i++){

            codeBlock[l++] = ' ';

        }
        if(consoleColors){

            // Allocate the needed memory for the content colour string
            size += strlen(lineColor);
            codeBlock = realloc(codeBlock, (size)*sizeof(char));

            // Copy the colour string
            for(int i = 0; i < strlen(lineColor); i++){

                codeBlock[l++] = lineColor[i];

            }

        }
        codeBlock[l++] = ' ';
        codeBlock[l++] = '.';
        codeBlock[l++] = '.';
        codeBlock[l++] = '.';

    }

    // Close the string
    codeBlock[l] = '\0';

    // Close the file stream
    fclose(file);

    // Check if you can output coloured text
    if(consoleColors){

        // Make all the lines in the codeBlock equal in length
        char *finalCodeBlock = evenLinesCodeBlock(codeBlock, maxColumn, prefixLength,
                                                    specialPrefixLength, triggerLineStart,
                                                    triggerLineEnd, relativeLine);

        // Free up the memory used by the `codeBlock` variable
        free(codeBlock);

        // Return the code block string
        return finalCodeBlock;

    }else{

        // Return the code block string
        return codeBlock;

    }

}
