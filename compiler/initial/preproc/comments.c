/**
 *
 *  Manage the preprocessor comments code blocks
 *
**/


// Define the preprocessor comments end and start detector
void checkForComments(FILE **inputFile, char *currChar, int *inLinearComm, int *inMultilinearComm, int *multilinearCommStart, int *multilinearCommEnd, int inQuote, int inDoubleQuote){

    // Check if the text is currently free of any quoting or commenting contexts
    if(!*inLinearComm && !*inMultilinearComm && !inQuote && !inDoubleQuote){

        // Check if this could be the start of a comment
        if(*currChar == '/'){

            // Note that there is no need to update the previous character variable in this context

            // Get the next character
            *currChar = fgetc(*inputFile);

            // Check if this is a linear comment
            if(*currChar == '/'){

                // This is the start of a linear comment!
                *inLinearComm = 1;

            }else if(*currChar == '*'){ // Check if this is a multi-linear comment

                // This is the start of a multi-linear comment
                *inMultilinearComm = 1;

                // Update the multi-linear comment start variable
                *multilinearCommStart = 1;

            }else{

                // This is not the start of a linear comment!

                // Make sure you didn't reach the end of the file
                // You need to do this to prevent the compiler from looping non-stop when it
                // reaches the end of the file with the last character being a slash (/)
                if(*currChar != EOF){

                    // Move the inputFile pointer one character backwards
                    fseek(*inputFile, -1L, SEEK_CUR);

                }

                // Reset the value of the "currChar" variable
                *currChar = '/';

            }

        }

    }else if(*inMultilinearComm){

        // Check if this is the start of the end of a multi-linear comment!
        if(*currChar == '*'){

            // Get the next character
            *currChar = fgetc(*inputFile);

            // Check if this is really the end of a multi-linear comment
            if(*currChar == '/'){

                // Update the multi-linear comment end variable
                *multilinearCommEnd = 1;

            }else{

                // Move the inputFile pointer one character backwards
                fseek(*inputFile, -1L, SEEK_CUR);

                // Reset the value of the "currChar" variable
                *currChar = '*';

            }

        }

    }

}