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

// Define a function that triggers the initial part of compiling
int initialComp(struct GlobalIO globalIO){

    // Trigger the preprocessor
    int filesCount = preproc(globalIO.input.fullPth, globalIO.tempDir, globalIO.input.dirPth,
                                globalIO.output.fileName, globalIO.libDir);

    // Now, you have a ".input" file that only includes the code used by the user. Basically, the
    // ".input" file includes all the code from the main input file, built-in libraries, and other
    // user-imported files)!
    //
    // All the file contexts are separated by the "\f" escape character, and the "\e" escape
    // character. Inside each file context, you have the file's basic info, and the file's content.
    // The file content is between the "\v" escape character and the "\e" escape character!
    // (read the comments in the `preproc/preproc.c` file for more info)
    //
    // In addition to file contexts, there are "intermediate" contexts! "Intermediate" contexts are
    // separated from the file that contains them with the "\a" escape character and the "\e" escape
    // character. They contain a code that's written in the intermediate compiling language that the
    // compiler uses. (Pure C code)

    // Now, with all this organised data in this one file, you can start analysing the user's code
    // to create a lexical index!

    // Trigger the lexer
    lexer();

    // Return the files count
    return filesCount;

}
