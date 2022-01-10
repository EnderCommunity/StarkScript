/**
 *
 *  Manage functions that are related to the "intermediate" statement
 *
**/


// Define some special characters that are used by functions that are related to the "intermediate"
// statement
#define CHAR_SPECIAL_ALERT "\a"

// Define a function that can manage the "intermediate" context
void intermContext(FILE **inputFile, FILE **outputFile, const char *codePath, const char *filePath,
                    char *currChar, int *intrmContextBracketsCount, int *intrmContextStart,
                    int *intrmContextStartLine, int *intrmContextStartColumn, int line,
                    int column){

    // Look for the first character in the "intermediate" context
    if((*currChar) != ' ' && (*currChar) != '\t' && (*intrmContextBracketsCount) == -1){

        // Check if the first character is not an opening curly bracket
        if((*currChar) != '{'){

            // The "intermediate" keyword may only be followed by an opening curly bracket
            preprocError(*inputFile, *outputFile, STR_ERROR_000011, codePath, filePath,
                            (*intrmContextStartLine), (*intrmContextStartColumn), column,
                            (*intrmContextStartLine) - line - 1);

        }else{

            // Start counting the curly brackets
            (*intrmContextBracketsCount) = 1;

            // Print a whitespace character in place of the curly bracket
            fprintf(*outputFile, " ");

            // Add the start character
            (*currChar) = CHAR_SPECIAL_ALERT[0];

        }

    }else if((*currChar) == '{'){

        // Update the curly brackets count
        (*intrmContextBracketsCount)++;

    }else if((*currChar) == '}'){

        // Update the curly brackets count
        (*intrmContextBracketsCount)--;

    }

    // Check if this context is done
    if((*intrmContextBracketsCount) == 0){

        // Print the end of this section
        fprintf(*outputFile, "%s", CHAR_SPECIAL_ESCAPE);
        (*currChar) = ' ';

        // End this context
        (*intrmContextStart) = 0;
        (*intrmContextStartColumn) = 0;
        (*intrmContextStartLine) = 0;

    }

}