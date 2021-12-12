/**
 *
 *  Manage system-related functions
 *
**/


// Get the system-related strings (like console commands)
#include "./strings/system.h"

// Define a function that works like the `system` function and the `sprintf` function
int systemf(const char *format, int length, ...){

    // Create a `__builtin_va_list` list
    __builtin_va_list __local_argv;
    __builtin_va_start(__local_argv, length);

    // Create a temporary command string
    char *command = calloc(length, sizeof(char));

    // Print a prefixed console message
    vsprintf(command, format, __local_argv);

    // Close the opened `__builtin_va_list` list
    __builtin_va_end(__local_argv);

    // Gray-out the command output text on Windows
    if(!consoleNoGray){

        consoleLog("%s", CONSOLE_COLOR_GRAY);

    }

    // Execute the system command
    int result = system(command);

    // Reset the console text colour
    consoleLog("%s", CONSOLE_COLOR_RESET);

    // Free the memory used by the "str" variable
    free(command);

    // Return the int value that the `systen` function would've returned
    return result;

}
