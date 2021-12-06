/**
 *
 *  Prepare and print the compiler start message
 *
**/


// Include the files that contain info that is related to the start message
#include "./info/compiler.c"
#include "./info/system.c"
#include "./info/language.c"

// Define the function that prints the compiler start message
void printCmplrMsg(){

    // Print any important compiler info
    consoleInfo("\nStarkScript V%s (Compiler version %s | %s channel )\nUsing the [%s] compiler on %s\n\n\
    * For more information, visit: %s\n\n\n",
    __STARK_VERSION__, __STARK_COMPILER_VERSION__, __STARK_RELEASE_STATE__, COMPILER_NAME,
    OPERATING_SYSTEM_MESSAGE_NAME, __STARK_WEBSITE_URL__);

}