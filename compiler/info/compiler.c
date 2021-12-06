/** 
 *
 *  Get info about the c compiler that's compiling this compiler
 *
**/


// Get the compiler type
#ifdef __GNUC__

    // This is a GNU compiler!
    #define COMPILER_NAME "GNU"

#else

    // This is an unknown compiler!
    #define COMPILER_NAME "UNKNOWN C COMPILER"

#endif
