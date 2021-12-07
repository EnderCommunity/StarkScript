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
    consoleInfo(

    // You must not add any whitespace at the start of this line...
    // If you do, additional lines will appear on small screens!
"\n%s%s%s V%s (Compiler version %s | %s channel)%s\nUsing the [%s] compiler on %s\n\n\
%s    This is an incomplete experimental project. Development\
\n    on this project is still in its very early stages and\
\n    it could stop at any given time and for no valid reason.\n\
\n    Please, consider helping us! %s<3%s\n\n\
\n        * For more information, visit: %s%s\n\n\n",

    // Make the language name blue
    CONSOLE_COLOR_BLUE,

    // Get te language name
    __STARK_NAME__,

    // Make the version info purple
    CONSOLE_COLOR_PURPLE,

    // Get the version info
    __STARK_VERSION__, __STARK_COMPILER_VERSION__, __STARK_RELEASE_STATE__,

    // Make the additional info gray
    CONSOLE_COLOR_GRAY,

    // Get the additional info
    COMPILER_NAME, OPERATING_SYSTEM_MESSAGE_NAME,

    // Make the warning text yellow
    CONSOLE_COLOR_YELLOW,

    // Make a red heart (<3, but red...)
    CONSOLE_COLOR_RED,

    //  Switch the text colour back to yellow for the warning
    CONSOLE_COLOR_YELLOW,

    // Get the website URL so the user can look for additional info
    __STARK_WEBSITE_URL__,

    // Reset the text colour
    CONSOLE_COLOR_RESET);

}