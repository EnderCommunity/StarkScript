/**
 *
 *  Manage the initial part of the compiling process
 *
**/


// The initial part of the compiling process consists of the preprocessor, and the lexer!

// The preprocessor is the part of the compiler that takes care of removing meaningless text within
// the language files, and it also combines all the used language files into one big file. We will
// be calling this file the "mega input file"...
#include "./preproc/preproc.c"

// The lexer is the part of the compiler that takes care of listing, identifying, and assigning
// types to every word and character within the "mega input file"...
#include "./lexer/lexer.c"
