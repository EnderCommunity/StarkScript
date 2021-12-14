/**
 *
 *  Manage all the console messages
 *
**/


// Include the `stdarg` library (which is used to allow functions to receive an indefinite number
// of arguments)
#include <stdarg.h>

// Get the console's strings
#include "./../strings/console.h"

// Keep track of the number of logs, warnings, and errors!
int logCount = 0,
    warnCount = 0,
    errorCount = 0,
    debugCount = 0;

// Define a variable to control the colour gray
int consoleNoGray = 0;

// Define a variable to control the cat messages
int consoleCat = 0;

// Define a variable to control console text colours
int consoleColors = 1;

// Define a variable to control console debug messages
int consoleAllowDebug = 0;

// Define a function similar to the `____printf` function that will add a prefix to the console
// output...
int ____printf_prefix(const char *__format, __builtin_va_list __local_argv, const char *prefix,
                        int grayTxt){

    if(consoleNoGray){

        grayTxt = 0;

    }

    // Create a new format string with the prefix included in it
    char *prefixedFormat = calloc(strlen(__format) + strlen(prefix) +
                                ((consoleColors) ? (2 * strlen(CONSOLE_COLOR_RESET)) : 0) + // Two colour resets are used to
                                                        // ensure that no colouring mistakes will
                                                        // ruin any of the console messages!
                                1 + // New line
                                ((grayTxt && consoleColors) ? strlen(CONSOLE_COLOR_GRAY) : 0) +
                                1, sizeof(char));
    sprintf(prefixedFormat, "%s%s%s%s%s\n",

        // Reset the text colour
        ((consoleColors) ? CONSOLE_COLOR_RESET : ""),

        // Get the prefix and the console message
        prefix, ((grayTxt && consoleColors) ? CONSOLE_COLOR_GRAY : ""), __format,

        // Reset the text colour again
        ((consoleColors) ? CONSOLE_COLOR_RESET : ""));

    // Print the console message
    int result = vfprintf(stdout, prefixedFormat, __local_argv);

    // Free the allocated memory for the `prefixedFormat` variable
    free(prefixedFormat);

    // Return the return value of the `vfprintf` function
    return result;

}

// Define a function that will print info into the console (basicly the `printf` function)
int consoleLog(const char *format, ...){

    // Create a `__builtin_va_list` from the ellipsis arguments
    __builtin_va_list __local_argv;
    __builtin_va_start(__local_argv, format);

    // Print all the message using the `vfprintf` function
    // It receives the ellipsis arguments as a `__builtin_va_list` list
    int result = vfprintf(stdout, format, __local_argv);

    // Close the opened `__builtin_va_list` list
    __builtin_va_end(__local_argv);

    // Return the int value that the `printf` function would've returned
    return result;

}

// Define a function that will print informative messages into the console
int consoleInfo(const char *format, ...){

    // Check if informative messages are enabled
    if(FLAG_CONSOLE_INFO_MESSAGES){

        // Create a `__builtin_va_list` list
        __builtin_va_list __local_argv;
        __builtin_va_start(__local_argv, format);

        // Print a prefixed console message
        int result = ____printf_prefix(format, __local_argv, ((consoleCat) ? ((consoleColors) ? ((consoleNoGray) ? STRING_CONSOLE_CAT_INFO_MESSAGE_NO_GRAY : STRING_CONSOLE_CAT_INFO_MESSAGE) : STRING_CONSOLE_CAT_INFO_MESSAGE_COLORLESS): ((consoleColors) ? ((consoleNoGray) ? STRING_CONSOLE_INFO_MESSAGE_NO_GRAY : STRING_CONSOLE_INFO_MESSAGE) : STRING_CONSOLE_INFO_MESSAGE_COLORLESS)), 0);

        // Close the opened `__builtin_va_list` list
        __builtin_va_end(__local_argv);

        // Record this log
        logCount++;

        // Return the int value that the `printf` function would've returned
        return result;

    }else{

        // Don't show the informative message
        return 0;

    }

}

// Define a function that will print debug messages into the console
int consoleDebug(const char *format, ...){

    // Check if debug mode is enabled
    if(FLAG_CONSOLE_DEBUG_MESSAGES && consoleAllowDebug){

        // Create a `__builtin_va_list` list
        __builtin_va_list __local_argv;
        __builtin_va_start(__local_argv, format);

        // Print a prefixed console message
        int result = ____printf_prefix(format, __local_argv, ((consoleCat) ? ((consoleColors) ? ((consoleNoGray) ? STRING_CONSOLE_CAT_DEBUG_MESSAGE_NO_GRAY : STRING_CONSOLE_CAT_DEBUG_MESSAGE) : STRING_CONSOLE_CAT_DEBUG_MESSAGE_COLORLESS) : ((consoleColors) ? ((consoleNoGray) ? STRING_CONSOLE_DEBUG_MESSAGE_NO_GRAY : STRING_CONSOLE_DEBUG_MESSAGE) : STRING_CONSOLE_DEBUG_MESSAGE_COLORLESS)), 1);

        // Close the opened `__builtin_va_list` list
        __builtin_va_end(__local_argv);

        // Record this debug log
        debugCount++;

        // Return the int value that the `printf` function would've returned
        return result;

    }else{

        // Don't show the debug message
        return 0;

    }

}

// Define a function that will print warnings into the console
int consoleWarn(const char *format, ...){

    // Check if warning messages are enabled
    if(FLAG_CONSOLE_WARNING_MESSAGES){

        // Create a `__builtin_va_list` list
        __builtin_va_list __local_argv;
        __builtin_va_start(__local_argv, format);

        // Print a prefixed console message
        int result = ____printf_prefix(format, __local_argv, ((consoleCat) ? ((consoleColors) ? ((consoleNoGray) ? STRING_CONSOLE_CAT_WARNING_MESSAGE_NO_GRAY : STRING_CONSOLE_CAT_WARNING_MESSAGE) : STRING_CONSOLE_CAT_WARNING_MESSAGE_COLORLESS) : ((consoleColors) ? ((consoleNoGray) ? STRING_CONSOLE_WARNING_MESSAGE_NO_GRAY : STRING_CONSOLE_WARNING_MESSAGE) : STRING_CONSOLE_WARNING_MESSAGE_COLORLESS)), 0);

        // Close the opened `__builtin_va_list` list
        __builtin_va_end(__local_argv);

        // Record this warning
        warnCount++;

        // Return the int value that the `printf` function would've returned
        return result;

    }else{

        // Don't show the warning message
        return 0;

    }

}

// Define a function that will print warnings into the console
int consoleError(const char *format, ...){

    // Check if error messages are enabled
    if(FLAG_CONSOLE_ERROR_MESSAGES){

        // Create a `__builtin_va_list` list
        __builtin_va_list __local_argv;
        __builtin_va_start(__local_argv, format);

        // Print a prefixed console message
        int result = ____printf_prefix(format, __local_argv, ((consoleCat) ? ((consoleColors) ? ((consoleNoGray) ? STRING_CONSOLE_CAT_ERROR_MESSAGE_NO_GRAY : STRING_CONSOLE_CAT_ERROR_MESSAGE) : STRING_CONSOLE_CAT_ERROR_MESSAGE_COLORLESS) : ((consoleColors) ? ((consoleNoGray) ? STRING_CONSOLE_ERROR_MESSAGE_NO_GRAY : STRING_CONSOLE_ERROR_MESSAGE) : STRING_CONSOLE_ERROR_MESSAGE_COLORLESS)), 0);

        // Close the opened `__builtin_va_list` list
        __builtin_va_end(__local_argv);

        // Record this error
        errorCount++;

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
