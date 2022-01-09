/**
 *
 *  Manage functions that are related to the "use" context
 *
**/


// Check for any potential "use" context
int useContext(FILE **inputFile, char *prvsChar, char *currChar, int *column){

    // Check if this is the start of a new word
    if(!isalpha(*prvsChar) && !isdigit(*prvsChar) && *prvsChar != '_'){

        // Look for the "use" keyword
        if(*currChar == 'u'){

            // Get the next character
            *currChar = fgetc(*inputFile);
            (*column)++;

            if(*currChar == 's'){

                // Get the next character
                *currChar = fgetc(*inputFile);
                (*column)++;

                if(*currChar == 'e'){

                    // Get the next character
                    *currChar = fgetc(*inputFile);
                    (*column)++;

                    // Check if this "use" string is not a part of a variable/function name
                    if(!isalpha(*currChar) && !isdigit(*currChar) && *currChar != '_'){

                        // Move the *inputFile pointer one character to the back
                        fseek(*inputFile, -1L, SEEK_CUR);
                        (*column)--;

                        // Restore the original value of the "current character" to "e"
                        *currChar = 'e';

                        // Found a "use" context
                        return 1;

                    }else{

                        // Move the *inputFile pointer six characters to the back
                        fseek(*inputFile, -3L, SEEK_CUR);
                        (*column) -= 3;

                        // Restore the original value of the "current character"
                        *currChar = 'u';

                    }

                }else{

                    // Move the *inputFile pointer two characters to the back
                    fseek(*inputFile, -2L, SEEK_CUR);
                    (*column) -= 2;

                    // Restore the original value of the "current character"
                    *currChar = 'u';

                }

            }else{

                // Move the *inputFile pointer one character backwards
                fseek(*inputFile, -1L, SEEK_CUR);
                (*column)--;

                // Restore the original value of the "current character"
                *currChar = 'u';

            }

        }

    }

    // Didn't find a valid "use" context
    return 0;

}