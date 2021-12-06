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

// Define a function similar to the `printf` function that will accept a `va_list` instead of an
// ellipsis!
int ____printf(const char *__format, __builtin_va_list __local_argv){

    // Note: This is some of the source code of the print function

    // Define a variable that will hole the return value
    int __retval;

    // Print all the message using the `__builtin_vfprintf` function
    // It receives the ellipsis arguments as a `__builtin_va_list` list
    __retval = __builtin_vfprintf(stdout, __format, __local_argv);

    // Close the opened `__builtin_va_list` list
    __builtin_va_end(__local_argv);

    // Return the code that value that the `printf` function would've returned
    return __retval;

}

// Define a function similar to the `____printf` function that will add a prefix to the console
// output...
int ____printf_prefix(const char *__format, __builtin_va_list __local_argv, const char *prefix){

    // Create a new format string with the prefix included in it
    char *prefixedFormat = calloc(strlen(__format) + strlen(prefix) + 1,
                                sizeof(char));
    strcpy(prefixedFormat, prefix);
    strcat(prefixedFormat, __format);

    // Print the console message
    int result = ____printf(prefixedFormat, __local_argv);

    // Free the allocated memory for the `prefixedFormat` variable
    free(prefixedFormat);

    return result;

}

// Define a function that will print info into the console (basicly the `printf` function)
int consoleInfo(const char *format, ...){

    // Create a `__builtin_va_list` from the ellipsis arguments
    __builtin_va_list __local_argv;
    __builtin_va_start(__local_argv, format);

    // Print the console message and return the int value that the `printf` function would've
    // returned
    return ____printf(format, __local_argv);

}

// Define a function that will print debug messages into the console
int consoleDebug(const char *format, ...){

    // Check if debug mode is enabled
    if(FLAG_CONSOLE_DEBUG_MESSAGES){

        // Create a `__builtin_va_list` list
        __builtin_va_list __local_argv;
        __builtin_va_start(__local_argv, format);

        // Print a prefixed console message
        int result = ____printf_prefix(format, __local_argv, STRING_CONSOLE_DEBUG_MESSAGE);

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
        int result = ____printf_prefix(format, __local_argv, STRING_CONSOLE_WARNING_MESSAGE);

        return result;

    }else{

        // Don't show the debug message
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
        int result = ____printf_prefix(format, __local_argv, STRING_CONSOLE_ERROR_MESSAGE);

        // Check if the error message is allowed to terminate this process
        if(FLAG_CONSOLE_ERROR_MESSAGES_EXIT) {

            // Exit with a FAILURE state
            exit(EXIT_FAILURE);

        }

        return result;

    }else{

        // Don't show the debug message
        return 0;

    }

}