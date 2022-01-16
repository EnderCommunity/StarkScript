/**
 *
 *  Manage the lexer
 *
**/


// The lexer will make a file that includes a list of lexemes that is generated from the content of
// the ".input" file!
//
// Each line contains a lexeme. And the general format of a lexeme is as follows:
//   ___________________________________________
//  |                                           |
//  | TYPE LINE COLUMN <...>                    |
//  |___________________________________________|
// 
// There are lots of types of lexemes:
// 
// [ ] KEYWORD                            A symbol/word that is used/reserved by the language
// 
// [ ] DEFINITIONAL-KEYWORD               A symbol/word that is used/reserved by the language for a
//                                        definitional purpose
// 
// [ ] CONDITIONAL-KEYWORD                A keyword that is related to conditions
//
// [ ] TYPE-KEYWORD                       A symbol/word that is used/reserved by the language for a
//                                        built-in type
// 
// [ ] IDENTIFIER                         A symbol/word that has no pre-specified use
// 
// [ ] BOOLEAN                            A boolean (true/false)
// 
// [ ] DECIMAL                            A number in decimal form
// 
// [ ] FULL-DECIMAL                       A number in decimal form that includes fractions
// 
// [ ] HEXADECIMAL                        A number in hexadecimal form
// 
// [ ] QUOTE                              A quote (')
// 
// [ ] DOUBLE-QUOTE                       A double quote (")
// 
// [ ] STRING-LITERAL                     A group of symbols and characters inside a double quote
// 
// [ ] STRING-PLACEHOLDER                 A placeholder for an identifier within a string
// 
// [ ] RELATIONAL-OPERATOR                An operator that is used to compare two parties
// 
// [ ] MATH-OPERATOR                      A maths-related operator
//
// [ ] ASSIGNNENT-OPERATOR                An operator that is used to change the value of a variable
// 
// [ ] END-OPERATOR                       The ";" operator
// 
// [ ] TYPE-OPERATOR                      The ":" operator
// 
// [ ] OPEN-TYPE-OPERATOR                 The "<" operator
// 
// [ ] CLOSE-TYPE-OPERATOR                The ">" operator
// 
// [ ] OPEN-BRACKET                       The "(" operator
// 
// [ ] CLOSE-BRACKET                      The ")" operator
// 
// [ ] COMMA                              The "," operator
// 
// [ ] OPEN-CURLY-BRACKET                 The "{" operator
// 
// [ ] CLOSE-CURLY-BRACKET                The "}" operator
// 
// [ ] OPEN-LIST-OPERATOR                 The "[" operator
// 
// [ ] CLOSE-LIST-OPERATOR                The "]" operator
// 
// Note that the maximum allowed length for a type is 24 characters! This is done so the final lexer
// output file would be more readable for the user!
// 
// The way the lines are going be written is as follows:
//   __________________________________________________________________
//  |                                                                  |
//  |  XXXXXXXXXXXXXXXXXXXXXXXX   0x0000000000 0x0000000000      ...   |
//  |  XXXXXXXXXXXXXXXXXXXXXXXX   0x0000000000 0x0000000000      ...   |
//  |  XXXXXXXXXXXXXXXXXXXXXXXX   0x0000000000 0x0000000000      ...   |
//  |__________________________________________________________________|
// 
// And, to make it possible for the other parts of the compiler to track down the source of a lexeme,
// a source-path will be passed in each line it changes:
//   __________________________________________________________________
//  |                                                                  |
//  |  !main.stark                                                     |
//  |  ?/path/to/main.stark                                            |
//  |  XXXXXXXXXXXXXXXXXXXXXXXX   0x0000000000 0x0000000000      ...   |
//  |  XXXXXXXXXXXXXXXXXXXXXXXX   0x0000000000 0x0000000000      ...   |
//  |  !file.stark@main.stark:0;0                                      |
//  |  ?/path/to/file.stark@/path/to/main.stark                        |
//  |  XXXXXXXXXXXXXXXXXXXXXXXX   0x0000000000 0x0000000000      ...   |
//  |  XXXXXXXXXXXXXXXXXXXXXXXX   0x0000000000 0x0000000000      ...   |
//  |  XXXXXXXXXXXXXXXXXXXXXXXX   0x0000000000 0x0000000000      ...   |
//  |  !main.stark                                                     |
//  |  ?/path/to/main.stark                                            |
//  |  XXXXXXXXXXXXXXXXXXXXXXXX   0x0000000000 0x0000000000      ...   |
//  |__________________________________________________________________|
// 
// The source-path's format is as follows:
//   _____________________________________________________________
//  |                                                             |
//  |  !<path_4>@<path_3>:L;C@<path_2>:L;C@<path_1>:L;C           |
//  |  ?<full_path_4>@<full_path_3>@<full_path_2>@<full_path_1>   |
//  |_____________________________________________________________|
// 
// So an example of a lexer output file would be:
//   __________________________________________________________________
//  |                                                                  |
//  |  !main.stark                                                     |
//  |  ?/path/to/main.stark                                            |
//  |  KEYWORD                    0x0000000001 0x0000000001      exit  |
//  |  DECIMAL                    0x0000000001 0x0000000007      0     |
//  |  END-OPERATOR               0x0000000001 0x0000000008            |
//  |__________________________________________________________________|
// 
// Note that the maximum number of allowed lines within a file and the maximum length of a line is
// 1,099,511,627,776! This is because the hexadecimal value for the line and column numbers can't
// hold and bigger values!
// 
// The line and column numbers are saved in a hexadecimal format just so the compiler does not have
// to do any lookups for the data that comes after these two values in each lexeme line.

// Include the <wctype> library
#include <wctype.h>

// Define a function to handle lexer errors
void lexerError(FILE **input, FILE **output, const char *msg, const char *codePath,
                    const char *filePath, int line, int column, int length, int height){

    // The `preprocError` function will do nicely for now!
    preprocError(*input, *output, msg, codePath, filePath, line, column, length, height);

}

// Define a function to handle lexer warnings
void lexerWarn(const char *msg, const char *codePath, const char *filePath, int line, int column,
                    int length){

    // The `preprocWarn` function will do nicely for now!
    preprocWarn(msg, codePath, filePath, line, column, length, 0);

}

// Get all the input-related functions
#include "./input.c"

// Get all the output-related functions
#include "./output.c"

// Get the lexer strings
#include "./../../strings/lexer.h"

// Define a recursive function for the lexer
void lexerR(FILE **input, FILE **output, char endChar){

    // Get the current character
    char currChar = fgetc(*input);

    // Keep track of the last character
    char prvsChar = '\0';

    // Keep track of the column and line values
    int line = 1, column = 1;

    // Keep track of the quotes' status
    int inQuote = 0,
        inDoubleQuote = 0,
        inQuoteInjection = 0;

    // Keep track of the lexeme's basic info
    int lexemeLine = 0,
        lexemeColumn = 0;

    // You will need to print all sorts of lexemes in one shared format
    // For that, you can use the "writeLexeme" function!
    //  _________________________________________________________
    // |                                                         |
    // |  writeLexeme(OUTPUT, TYPE, LINE, COLUMN, FORMAT, ...);  |
    // |_________________________________________________________|
    //
    // You will need to pass the output file pointer, the lexeme's type, the source line,
    // and the source column!
    //
    // In addition to that, you need to pass a string that describes the additional information that
    // the lexeme will include. If you leave it empty, it indicates that the lexeme does not use any
    // additional data.
    //
    // Each format character indicates an additional lexeme value. And the supported types for the
    // lexeme's values are:
    // "d"                      **  int
    // "f"                      **  double/float
    // "c"                      **  char
    // "s"                      **  string/char*
    //
    // A valid use of the writeLexeme would be as follows:
    //  _________________________________________________________________________
    // |                                                                         |
    // |  writeLexeme(output, "TEST", 1, 1, "dfcs", 255, 25.25, 'A', "Hello!");  |
    // |  writeLexeme(output, "TEST-TWO", 1, 1, "");                             |
    // |_________________________________________________________________________|

    // Go through all the characters within the input file
    while(currChar != endChar){

        // Remember that you still have access to the `lookUpKeyword` function, you can also use it
        // here!

        // Start looking for quotes first so you couldn't confuse any of the quotes' content to
        // other normal code!
        if(!inQuote && currChar == '"' && (!inDoubleQuote || prvsChar != '\\')){

            // Update the quote status
            inDoubleQuote = !inDoubleQuote;

        }else if(!inDoubleQuote && currChar == '\''){

            inQuote = !inQuote;

        }

        // Check if you're in a quote injection context
        // "blah blah blah {myStr} blah blah blah" => (myStr: "noooo")
        // "blah blah blah noooo blah blah blah"
        // Note that quote injection is not "nest-able"!
        if(inDoubleQuote && !inQuoteInjection && (currChar == '{' && prvsChar != '\\')){

            inQuoteInjection = 1;
            inDoubleQuote = 0;

        } else if(inQuoteInjection && !isspace(currChar)){ // Check if this is the quote injection
                                                        // part

            if(0/*?foundQuoteInjectionStart*/){

                // Look for the start of an identifier
                if(isalpha(currChar) || currChar == '_'){

                    //

                }

            }else{

                //

            }

        }

        // Look for lexemes that are not related to strings or characters
        if(!inQuoteInjection && !inQuote && !inDoubleQuote){

            // All keywords in Stark start with a lower case character!
            if(isalpha(currChar) && islower(currChar)){

                // Define a variable that can store the current lexeme's type
                const char *result;

                // First, look for keywords
                if(lookUpKeywords(&result, input, prvsChar, &currChar, &column,
                        LEXER_KEYWORD_EXIT_PROGRAM,
                        LEXER_KEYWORD_SET_MAIN_FUNCTION,
                        LEXER_KEYWORD_DEFINE_FREE_CONSTANT,
                        LEXER_KEYWORD_MAKE_NEW,
                        LEXER_KEYWORD_DELETE_VARIABLE,
                        LEXER_KEYWORD_RETURN_VALUE,
                    KEYWORDS_LIST_END)){

                    // Add this lexeme
                    writeLexeme(output, "KEYWORD", line, column - strlen(result) + 1, "s", result);

                }else if(lookUpKeywords(&result, input, prvsChar, &currChar, &column,
                        LEXER_DEFINITIONAL_KEYWORD_DEFINE_VARIABLE,
                        LEXER_DEFINITIONAL_KEYWORD_DEFINE_CONSTANT,
                        LEXER_DEFINITIONAL_KEYWORD_DEFINE_FUNCTION,
                    KEYWORDS_LIST_END)){

                    // Add this lexeme
                    writeLexeme(output, "DEFINITIONAL-KEYWORD", line, column - strlen(result) + 1, "s", result);

                }else if(lookUpKeywords(&result, input, prvsChar, &currChar, &column,
                        LEXER_KEYWORD_CONDITIONAL_IF,
                        LEXER_KEYWORD_CONDITIONAL_ELSE,
                    KEYWORDS_LIST_END)){

                    // Add this lexeme
                    writeLexeme(output, "CONDITIONAL-KEYWORD", line, column - strlen(result) + 1, "s", result);

                }else if(lookUpKeywords(&result, input, prvsChar, &currChar, &column,
                        LEXER_TYPE_KEYWORD_BOOL,
                        LEXER_TYPE_KEYWORD_INT,
                        LEXER_TYPE_KEYWORD_FLOAT,
                        LEXER_TYPE_KEYWORD_DOUBLE,
                        LEXER_TYPE_KEYWORD_CHAR,
                        LEXER_TYPE_KEYWORD_STRING,
                        LEXER_TYPE_KEYWORD_SHORT,
                        LEXER_TYPE_KEYWORD_LONG,
                        LEXER_TYPE_KEYWORD_VOID,
                        LEXER_TYPE_KEYWORD_SIGNED,
                        LEXER_TYPE_KEYWORD_UNSIGNED,
                    KEYWORDS_LIST_END)){

                    // Add this lexeme
                    writeLexeme(output, "TYPE-KEYWORD", line, column - strlen(result) + 1, "s", result);

                }
            
                // Look for type-specific data
                else if(lookUpKeywords(&result, input, prvsChar, &currChar, &column,
                        LEXER_BOOLEAN_TRUE,
                        LEXER_BOOLEAN_FALSE,
                    KEYWORDS_LIST_END)){

                    // Add this lexeme
                    writeLexeme(output, "BOOLEAN", line, column - strlen(result) + 1, "s", result);

                }

            }else if(isdigit(currChar)){

                // Keep track of the number and its value
                int size = 1,
                    startColumn = column;
                char *number = calloc(size, sizeof(char));

                // Get all the number
                while(currChar != endChar && isdigit(currChar)){

                    // Save the current digit
                    number = realloc(number, (++size)*(sizeof(char)));
                    number[size - 2] = currChar;

                    // Get the next character
                    getNextChar(input, &currChar, &column);

                }
                number[size - 1] = '\0';

                if(size == 2 && number[0] == '0' && currChar == 'x'){

                    // Reduce the size of memory by one so you can replace the zero
                    size--;

                    // Get the next character
                    getNextChar(input, &currChar, &column);

                    // Get all the hex value
                    while(currChar != endChar && (isdigit(currChar) || iswxdigit(currChar))){

                        // Save the current digit
                        number = realloc(number, (++size)*(sizeof(char)));
                        number[size - 2] = currChar;

                        // Get the next character
                        getNextChar(input, &currChar, &column);

                    }
                    number[size - 1] = '\0';

                    if(size == 1){

                        // Go back, and save this token as a normal number
                        getPrvChar(input, &currChar, &column);

                        // Add this lexeme
                        writeLexeme(output, "DECIMAL", line, startColumn, "s", number);

                    }else{

                        // Add this lexeme
                        writeLexeme(output, "HEXADECIMAL", line, startColumn, "s", number);

                    }

                }else if(currChar == '.'){

                    // Keep track of the number's fractional value
                    int fSize = 1;
                    char *fraction = calloc(fSize, sizeof(char));

                    // Get the next character
                    getNextChar(input, &currChar, &column);

                    // Get all the fraction
                    while(currChar != endChar && isdigit(currChar)){

                        // Save the current digit
                        fraction = realloc(fraction, (++fSize)*(sizeof(char)));
                        fraction[fSize - 2] = currChar;

                        // Get the next character
                        getNextChar(input, &currChar, &column);

                    }
                    if(strlen(fraction) == 0){

                        // Add a zero
                        fraction = realloc(fraction, (++fSize)*(sizeof(char)));
                        fraction[fSize - 2] = '0';

                    }
                    fraction[fSize - 1] = '\0';

                    // Add this lexeme
                    writeLexeme(output, "FULL-DECIMAL", line, startColumn, "ss", number, fraction);

                    // Free up the memory used by the "fraction" variable
                    free(fraction);

                }else{

                    // Add this lexeme
                    writeLexeme(output, "DECIMAL", line, startColumn, "s", number);

                    // Move the *inputFile pointer one character to the back
                    getPrvChar(input, &currChar, &column);

                }

                // Free up the memory used by the "number" variable
                free(number);

            }

            // Note to myself: add a "lookupSequence" function and a "lookupSequences" function so
            // you can sort symbols and special characters!

            // ...

        }

        // Update the column and line values
        if(currChar == '\n'){

            line++;
            column = 1;

        }else{

            column++;

        }

        // Update the `prvsChar` variable
        prvsChar = currChar;

        // Get the current character
        currChar = fgetc(*input);

    }

}

// Define a function that triggers the lexer
void lexer(const char *tmpDir, const char *outputFileName){

    // Open a file stream to the ".input" file
    FILE *input = openTmpInput(tmpDir, outputFileName);

    // Create a lexer ouput file
    FILE *output = createLexerFile(tmpDir, outputFileName);

    // Call the recursive function
    lexerR(&input, &output, EOF);

    // ...

    // Close the output file stream
    fclose(output);

    // Close the input file stream
    fclose(input);

}
