/**
 *
 *  Get info about the current operating system
 *
**/


// Get the operating system
#ifdef _WIN32

    // This device is using the Windows operating system

    // Check if this is a 64 or 32 bit version of Windows
    #ifdef _WIN64

        #define OPERATING_SYSTEM_MESSAGE_NAME "Windows 64 bit"

    #else 

        #define OPERATING_SYSTEM_MESSAGE_NAME "Windows 32 bit"

    #endif

#elif __APPLE__

    #include "TargetConditionals.h"

    // Check the name of this Apple OS

    #if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR

        #define OPERATING_SYSTEM_MESSAGE_NAME "iPhone stimulator"

    #elif TARGET_OS_IPHONE

        #define OPERATING_SYSTEM_MESSAGE_NAME "iPhone"

    #elif TARGET_OS_MAC

        #define OPERATING_SYSTEM_MESSAGE_NAME "MacOS"

    #else

        // This is an unknown Apple OS!

        #define OPERATING_SYSTEM_MESSAGE_NAME "an Apple OS"

    #endif

#elif __linux__

    // This is a Linux-based operating system
    #define OPERATING_SYSTEM_MESSAGE_NAME "Linux"

#elif __unix__

    // This is a unix operating system
    #define OPERATING_SYSTEM_MESSAGE_NAME "a unix OS"

#else

    // This is an unidentified/unknown operating system
    #define OPERATING_SYSTEM_MESSAGE_NAME "an unidentified OS"

#endif
