/**
 *
 *  Manage the temporary directory
 *
**/


// Define a function that returns the system's temporary directory
char* getTempDir(){

    // Allocate the amount of memory that a path with the maximum length will take
    char *tempDir = calloc(PATH_MAX + 1, sizeof(char));

    // Go through all the system environment variables that may include the path of the temporary
    // directory
    if(getenv("TMP")){

        // Copy the "TMP" system environment variable
        strcpy(tempDir, getenv("TMP"));

    }else if(getenv("TEMP")){

        // Copy the "TEMP" system environment variable
        strcpy(tempDir, getenv("TEMP"));

    }else if(getenv("TMPDIR")){

        // Copy the "TMPDIR" system environment variable
        strcpy(tempDir, getenv("TMPDIR"));

    }else if(getenv("TEMPDIR")){

        // Copy the "TEMPDIR" system environment variable
        strcpy(tempDir, getenv("TEMPDIR"));

    }else{

        // Since you can't find the system's temporary directory, you're going to need to guess it
        // out!

        //
        #if __linux__

            // In most Linux distros and Linux-based systems, the temporary is "/tmp". So, check if
            // this directory does exist!

            // Open a directory stream
            DIR* dir = opendir("/tmp");

            // Check if this directory is accessible
            if (dir) {

                // This is a valid and accessible directory!

                // Close the directory stream
                closedir(dir);

                // Copy the temporary directory's path
                strcpy(tempDir, "/tmp");

            }else{

                // Inform the user about this error!
                consoleError("Couldn't find the system's temporary directory!%s",
                            STRING_CONSOLE_GITHUB_REPORT);

            }

        #else

            // Free the locally allocated memory
            free(tempDir);
            tempDir = NULL;

            // Inform the user about this error!
            consoleError("Couldn't find the system's temporary directory!%s",
                            STRING_CONSOLE_GITHUB_REPORT);

        #endif

    }

    return tempDir;

}