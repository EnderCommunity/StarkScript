/**
 *
 *  Manage the lexer
 *
**/


// The lexer will make a file that includes a list of lexies that is generated from the content of
// the ".input" file!
//
// Each line contains a lexie. And the general format of a lexie is as follows:
//   ___________________________________________
//  |                                           |
//  | TYPE LINE COLUMN <...>                    |
//  |___________________________________________|
// 
// There are lots of types of lexies:
// 
//     KEYWORD                            A symbol/word that is used/reserved by the language
// 
//     DEFINITIONAL-KEYWORD               A symbol/word that is used/reserved by the language for a
//                                        definitional purpose
// 
//     TYPE-KEYWORD                       A symbol/word that is used/reserved by the language for a
//                                        built-in type
// 
//     IDENTIFIER                         A symbol/word that has no pre-specified use
// 
//     BOOLEAN                            A boolean (true/false)
// 
//     DECIMAL                            A number in decimal form
// 
//     FULL-DECIMAL                       A number in decimal form that includes fractions
// 
//     HEX                                A number in hexadecimal form
// 
//     QUOTE                              A quote (')
// 
//     DOUBLE-QUOTE                       A double quote (")
// 
//     STRING-LITERAL                     A group of symbols and characters inside a double quote
// 
//     STRING-PLACEHOLDER                 A placeholder for an identifier within a string
// 
//     RELATIONAL-OPERATOR                An operator that is used to compare two parties
// 
//     MATH-OPERATOR                      A maths-related operator
//
//     ASSIGNNENT-OPERATOR                An operator that is used to change the value of a variable
// 
//     END-OPERATOR                       The ";" operator
// 
//     TYPE-OPERATOR                      The ":" operator
// 
//     OPEN-TYPE-OPERATOR                 The "<" operator
// 
//     CLOSE-TYPE-OPERATOR                The ">" operator
// 
//     OPEN-BRACKET                       The "(" operator
// 
//     CLOSE-BRACKET                      The ")" operator
// 
//     COMMA                              The "," operator
// 
//     OPEN-CURLY-BRACKET                 The "{" operator
// 
//     CLOSE-CURLY-BRACKET                The "}" operator
// 
//     OPEN-LIST-OPERATOR                 The "[" operator
// 
//     CLOSE-LIST-OPERATOR                The "]" operator
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
// And, to make it possible for the other parts of the compiler to track down the source of a lexie,
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
// to do any lookups for the data that comes after these two values in each lexie line.

// Define a function that triggers the lexer
void lexer(){

    // ...

}
