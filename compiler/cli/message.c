/**
 *
 *  Prepare and print the compiler start message
 *
**/


// Include the files that contain info that is related to the start message
#include "./../info/compiler.h"
#include "./../info/system.h"
#include "./../info/language.h"

// Define the function that prints the compiler start message
void printCmplrMsg(){

    // Print any important compiler info
    consoleLog(

    // You must not add any whitespace at the start of this line...
    // If you do, additional lines will appear on small screens!
"\n%s%s%s V%s (Compiler version %s | %s channel)%s\nUsing the [%s] compiler on %s\n\n\
%s    This is an incomplete experimental project. Development\
\n    on this project is still in its very early stages and\
\n    it could stop at any given time and for no valid reason.\n\
\n    For help, re-run this command with the \"--help\" flag or\
\n    the flag \"-h\"... \n\
\n    Please, consider helping us with this project! %s<3%s\n\n\
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

// Define a function that prints the exit message
void printExtMsg(int didFail, int compiledFiles){

    // Calculate the time it took the compiler to get to this point
    clock_t endTime = clock();
    double timeSpent = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    // Print into the console
    consoleLog(((FLAG_CONSOLE_DEBUG_MESSAGES && consoleAllowDebug) ?
        "\n%s%s%s in %.4fs %s(%d files compiled)%s\n%s%d%s log(s), %s%d%s warning(s), %s%d%s error(s), %s%d%s debug log(s)\n\n" :
        "\n%s%s%s in %.4fs %s(%d files compiled)%s\n%s%d%s log(s), %s%d%s warning(s), %s%d%s error(s)\n\n"),

    // Colour the status word with its appropriate colour
    ((consoleColors) ? 
        ((didFail) ? CONSOLE_COLOR_RED : 
            ((warnCount == 0) ? CONSOLE_COLOR_GREEN : CONSOLE_COLOR_YELLOW)
        ): ""),

    // Pass the status of the compiler to the print function
    (didFail) ? "FAILED" : "FINISHED",

    // Reset the text colour
    ((consoleColors) ? CONSOLE_COLOR_RESET : ""),

    // Pass the `timeSpent` variable to the print function
    timeSpent,

    // Pass the number of the compiled files
    (consoleNoGray) ? "" : CONSOLE_COLOR_GRAY,
    compiledFiles,
    (consoleNoGray) ? "" : CONSOLE_COLOR_RESET,

    // Colour the logs count with green
    ((consoleColors) ? CONSOLE_COLOR_GREEN : ""),
    logCount,
    ((consoleColors) ? CONSOLE_COLOR_RESET : ""),

    // Colour the warnings count with yellow
    ((consoleColors) ? CONSOLE_COLOR_YELLOW : ""),
    warnCount,
    ((consoleColors) ? CONSOLE_COLOR_RESET : ""),

    // Colour the errors count with red
    ((consoleColors) ? CONSOLE_COLOR_RED : ""),
    errorCount,
    ((consoleColors) ? CONSOLE_COLOR_RESET : ""),
    
    // Colour the debug count with cyan
    ((consoleColors) ? CONSOLE_COLOR_CYAN : ""),
    debugCount,
    ((consoleColors) ? CONSOLE_COLOR_RESET : ""));

}
