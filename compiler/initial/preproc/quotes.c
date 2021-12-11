/**
 *
 *  Manage the preprocessor quote-related code blocks
 *
**/


//
void checkForQuotes(int *inQuote, int *inDoubleQuote, char currChar, char prvsChar, int inLinearComm, int inMultilinearComm){

    // Check if you're not in a comment context
    if(!inLinearComm && !inMultilinearComm){

        // Check for the start and the end of a quoting context
        if(!*inQuote && currChar == '"'){

            // Don't forget about the escape character (\)!
            // The escape can be used to prevent a quoting context from being closed by a quote:
            //  ______________________________________________________________________________
            // |                                                                              |
            // |   "This is a double quote: \""; // This is a valid quoting context           |
            // |______________________________________________________________________________|
            if((*inDoubleQuote && prvsChar != '\\') || !*inDoubleQuote){

                *inDoubleQuote = !*inDoubleQuote;

            }

        }else if(!*inDoubleQuote && currChar == '\''){

            // Don't forget about the escape character (\)!
            // The escape can be used to prevent a quoting context from being closed by a quote:
            //  ______________________________________________________________________________
            // |                                                                              |
            // |   '\''; // This is a valid quoting context                                   |
            // |______________________________________________________________________________|
            if((*inQuote && prvsChar != '\\') || !*inQuote){

                *inQuote = !*inQuote;

            }

        }

    }

}