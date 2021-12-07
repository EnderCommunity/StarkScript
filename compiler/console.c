/**
 *
 *  Manage all the console messages
 *
**/


// Include the standard input and output library
#include <stdio.h>

// Include the standard library
#include <stdlib.h>

// Include the strings library (which included functions that are useful when dealing with strings)
#include <string.h>

// Include the `stdarg` library (which is used to allow functions to receive an indefinite number
// of arguments)
#include <stdarg.h>

// Get the console's strings
#include "./strings/console.c"

// Define a function similar to the `____printf` function that will add a prefix to the console
// output...
int ____printf_prefix(const char *__format, __builtin_va_list __local_argv, const char *prefix, const int grayTxt){

    // Create a new format string with the prefix included in it
    char *prefixedFormat = calloc(strlen(__format) + strlen(prefix) +
                                2 * strlen(CONSOLE_COLOR_RESET) + // Two colour resets are used to
                                                        // ensure that no colouring mistakes will
                                                        // ruin any of the console messages!
                                1 + // New line
                                ((grayTxt) ? strlen(CONSOLE_COLOR_GRAY) : 0) +
                                1, sizeof(char));
    sprintf(prefixedFormat, "%s%s%s%s%s\n",

        // Reset the text colour
        CONSOLE_COLOR_RESET,

        // Get the prefix and the console message
        prefix, ((grayTxt) ? CONSOLE_COLOR_GRAY : ""), __format,

        // Reset the text colour again
        CONSOLE_COLOR_RESET);

    // Print the console message
    int result = __builtin_vfprintf(stdout, prefixedFormat, __local_argv);

    // Free the allocated memory for the `prefixedFormat` variable
    free(prefixedFormat);

    // Return the return value of the `__builtin_vfprintf` function
    return result;

}

// Define a function that will print info into the console (basicly the `printf` function)
int consoleInfo(const char *format, ...){

    // Create a `__builtin_va_list` from the ellipsis arguments
    __builtin_va_list __local_argv;
    __builtin_va_start(__local_argv, format);

    // Print all the message using the `__builtin_vfprintf` function
    // It receives the ellipsis arguments as a `__builtin_va_list` list
    int result = __builtin_vfprintf(stdout, format, __local_argv);

    // Close the opened `__builtin_va_list` list
    __builtin_va_end(__local_argv);

    // Return the int value that the `printf` function would've returned
    return result;

}

// Define a function that will print debug messages into the console
int consoleDebug(const char *format, ...){

    // Check if debug mode is enabled
    if(FLAG_CONSOLE_DEBUG_MESSAGES){

        // Create a `__builtin_va_list` list
        __builtin_va_list __local_argv;
        __builtin_va_start(__local_argv, format);

        // Print a prefixed console message
        int result = ____printf_prefix(format, __local_argv, STRING_CONSOLE_DEBUG_MESSAGE, 1);

        // Close the opened `__builtin_va_list` list
        __builtin_va_end(__local_argv);

        // Return the int value that the `printf` function would've returned
        return result;

    }else{

        // Don't show the debug message
        return 0;

    }

}

// Define a function that will print warnings into the console
int consoleWarn(const char *format, ...){

    // Check if debug mode is enabled
    if(FLAG_CONSOLE_WARNING_MESSAGES){

        // Create a `__builtin_va_list` list
        __builtin_va_list __local_argv;
        __builtin_va_start(__local_argv, format);

        // Print a prefixed console message
        int result = ____printf_prefix(format, __local_argv, STRING_CONSOLE_WARNING_MESSAGE, 0);

        // Close the opened `__builtin_va_list` list
        __builtin_va_end(__local_argv);

        // Return the int value that the `printf` function would've returned
        return result;

    }else{

        // Don't show the warning message
        return 0;

    }

}

// Define a function that will print warnings into the console
int consoleError(const char *format, ...){

    // Check if debug mode is enabled
    if(FLAG_CONSOLE_ERROR_MESSAGES){

        // Create a `__builtin_va_list` list
        __builtin_va_list __local_argv;
        __builtin_va_start(__local_argv, format);

        // Print a prefixed console message
        int result = ____printf_prefix(format, __local_argv, STRING_CONSOLE_ERROR_MESSAGE, 0);

        // Close the opened `__builtin_va_list` list
        __builtin_va_end(__local_argv);

        // Check if the error message is allowed to terminate this process
        if(FLAG_CONSOLE_ERROR_MESSAGES_EXIT) {

            // Exit with a FAILURE state
            stopProcess(EXIT_FAILURE);

        }

        // Return the int value that the `printf` function would've returned
        return result;

    }else{

        // Don't show the error message
        return 0;

    }

}