/**
 *
 *  Manage functions that are related to the "import" context
 *
**/


// Check for any potential importing context
int importContext(FILE **inputFile, char *prvsChar, char *currChar){

    // Check if this is the start of a new word
    if(!isalpha(*prvsChar) && !isdigit(*prvsChar) && *prvsChar != '_'){

        // Look for the "import" keyword
        if(*currChar == 'i'){

            // Get the next character
            *currChar = fgetc(*inputFile);

            if(*currChar == 'm'){

                // Get the next character
                *currChar = fgetc(*inputFile);

                if(*currChar == 'p'){

                    // Get the next character
                    *currChar = fgetc(*inputFile);

                    if(*currChar == 'o'){

                        // Get the next character
                        *currChar = fgetc(*inputFile);

                        if(*currChar == 'r'){

                            // Get the next character
                            *currChar = fgetc(*inputFile);

                            if(*currChar == 't'){

                                // Get the next character
                                *currChar = fgetc(*inputFile);

                                // Check if this "import" string is not a part of a variable/function name
                                if(!isalpha(*currChar) && !isdigit(*currChar) && *currChar != '_'){

                                    // Move the *inputFile pointer one character to the back
                                    fseek(*inputFile, -1L, SEEK_CUR);

                                    // Restore the original value of the "current character" to "t"
                                    *currChar = 't';

                                    // Found an import context
                                    return 1;

                                }else{

                                    // Move the *inputFile pointer six characters to the back
                                    fseek(*inputFile, -6L, SEEK_CUR);

                                    // Restore the original value of the "current character"
                                    *currChar = 'i';

                                }

                            }else{

                                // Move the *inputFile pointer five characters to the back
                                fseek(*inputFile, -5L, SEEK_CUR);

                                // Restore the original value of the "current character"
                                *currChar = 'i';

                            }

                        }else{

                            // Move the *inputFile pointer four characters to the back
                            fseek(*inputFile, -4L, SEEK_CUR);

                            // Restore the original value of the "current character"
                            *currChar = 'i';

                        }

                    }else{

                        // Move the *inputFile pointer three characters to the back
                        fseek(*inputFile, -3L, SEEK_CUR);

                        // Restore the original value of the "current character"
                        *currChar = 'i';

                    }

                }else{

                    // Move the *inputFile pointer two characters to the back
                    fseek(*inputFile, -2L, SEEK_CUR);

                    // Restore the original value of the "current character"
                    *currChar = 'i';

                }

            }else{

                // Move the *inputFile pointer one character backwards
                fseek(*inputFile, -1L, SEEK_CUR);

                // Restore the original value of the "current character"
                *currChar = 'i';

            }

        }

    }

    // Didn't find a valid "import" context
    return 0;

}