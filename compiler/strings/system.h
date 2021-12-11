/**
 *
 *  Manage all the system-related strings
 *
**/


// Define the command that can be used to remove full folders
#ifdef _WIN32

    // For more info about the "rmdir" for Windows, visit:
    // https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/rmdir
    #define SYSTEM_COMMAND_REMOVE_FULL_DIR "rmdir /s /q "

#else

    #define SYSTEM_COMMAND_REMOVE_FULL_DIR "rm -rf "

#endif