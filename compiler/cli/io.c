/**
 *
 *  Manage input and output paths
 *
**/


// Include the `unistd.h` library
// It's used to access functions that can help in dealing with paths and files!
#include <unistd.h>

// Include the `stat.h` library
// It's used to get stats of files and directories
#include <sys/stat.h>

// Include the `dirent.h` library
// It's used to access functions that can help in dealing with directories!
#include <dirent.h>

/// Include the `errno.h` library
// You need this library to keep track of any errors made by file streams and directory streams
#include <errno.h>

// Get the input and output strings
#include "./../strings/io.h"

// Get the `getTempDir` function
#include "./temp.c"

// Define an interface that includes all the needed input info
struct GlobalInput {

    // The full path
    char *fullPth;

    // The file directory
    char *dirPth;

};

// Define an interface that includes all the needed output info
struct GlobalOutput {

    // The full path
    char *fullPth;

    // The output file name
    char *fileName;

};

// Define an interface that combines the `GlobalInput` and `GlobalOutput` interfaces
struct GlobalIO {

    // The current working directory
    char *wrkDir;

    // The system's temporary directory
    char *tempDir;

    // The compiler's main directory
    char *cmpDir;

    // The root directory of Stark's libraries
    char *libDir;

    // The input and output interface
    struct GlobalOutput output;
    struct GlobalInput input;

};

// Define a global interface variable
struct GlobalIO globalIO;

// Define the function that will recieve the input and output paths
// This function receives the variables as references to insure that the final value of the global
// `cmplrInputFilePth` variable and `cmplrOutputFilePth` variable will change according to the
// changes applied to the `inputPth` and `outputPth` variables
int processIO(char **inputPth, char **outputPth, char **outputName, char *pathArg){

    // Note that you need to dereference the `inputPth`, `outputName`, and the `outputPth` variables

    // Update the `globalIO` object
    globalIO.cmpDir = NULL;
    globalIO.libDir = NULL;
    globalIO.wrkDir = NULL;
    globalIO.tempDir = NULL;
    globalIO.input.fullPth = NULL;
    globalIO.input.dirPth = NULL;
    globalIO.output.fullPth = NULL;
    globalIO.output.fileName = NULL;

    // Get the path of the compiler's main directory
    globalIO.cmpDir = getCompilerDir(pathArg);
    globalIO.libDir = joinDirFile(globalIO.cmpDir, "libraries");

    // Print all the paths that are related to the compiler (debug)
    consoleDebug("Main compiler directory: %s", globalIO.cmpDir);
    consoleDebug("Libraries directory: %s", globalIO.libDir);

    // Check if the user did pass an input path
    if(*inputPth != NULL){

        // Check if the passed value is a valid path
        if(access(*inputPth, F_OK) == 0){

            // Check if this is a path for a file
            struct stat path_stat;
            stat(*inputPth, &path_stat);

            if(S_ISREG(path_stat.st_mode)) {

                // Contain this block of code so the `buffer` variable would get deleted after
                // getting copied to the global working directory variable (globalIO.wrkDir)
                {

                    // Create a temporary buffer to receive the current working directory
                    // Not using a char array buffer could result in the `getcwd` function not
                    // working properly
                    char buffer[PATH_MAX + 1];

                    // Get the current working directory
                    getcwd(buffer, sizeof(buffer));

                    if(strlen(buffer) == 0){

                        // Inform the user about this error
                        consoleError("Couldn't get the current working directory!", 1);

                    }else{

                        // Copy the buffer to the global working directory variable
                        globalIO.wrkDir = calloc(strlen(buffer) + 1, sizeof(char));
                        strcpy(globalIO.wrkDir, buffer);

                        // Print the current working directory (Debug)
                        consoleDebug("Current working directory: %s", globalIO.wrkDir);

                    }

                }

                // Get the absolute path of the input path
                globalIO.input.fullPth = absPth(*inputPth);

                // Print the full input path (Debug)
                consoleDebug("Input path: %s", globalIO.input.fullPth);

                // Get the absolute path of the input file's directory
                globalIO.input.dirPth = getFileDir(globalIO.input.fullPth);

                // Print the full input directory (Debug)
                consoleDebug("Input directory: %s", globalIO.input.dirPth);

                // Check the file extension
                // The file extension doesn't really affect the compiler, it's just better to always
                // use the same extension for the same type of files.
                {

                    // Here's the source of this piece of code:
                    // https://stackoverflow.com/questions/5309471/getting-file-extension-in-c

                    // Get the file extension
                    const char *dot = strrchr(globalIO.input.fullPth, '.');

                    // Check if the file doesn't have the "stark" extension or any extension at all
                    if(!dot || dot == globalIO.input.fullPth ||
                        strcmp(dot + 1, __STARK_EXTENSION__) != 0){

                        consoleWarn("The input file doesn't have the \"%s\" extension in its name!",
                        __STARK_EXTENSION__);

                    }

                }

                // Check if the output path variable has a value
                if(*outputPth != NULL){

                    // Open a directory stream
                    DIR* dir = opendir(*outputPth);

                    // Check if the passed value is a valid directory
                    if (dir) {

                        // This is a valid directory

                        // Close the directory stream
                        closedir(dir);

                        // Get the absolute path of the output directory
                        globalIO.output.fullPth = absPth(*outputPth);

                        // Free the memory used by the output path variable
                        free(*outputPth);
                        *outputPth = NULL;

                    } else if (ENOENT == errno) {

                        // The passed output directory doesn't exist
                        consoleError("The passed output path is invalid! (You must pass a valid directory path)"
                                        , 1);

                    } else {

                        // The `opendir` function failed for some other reason.
                        consoleError("Couldn't check the output directory!", 1);

                    }

                }else{

                    // Set the output directory to be the same as the input file's directory

                    // Copy the input `dirPth` variable
                    globalIO.output.fullPth = calloc(strlen(globalIO.input.dirPth)
                                                        + 1, sizeof(char));
                    strcpy(globalIO.output.fullPth, globalIO.input.dirPth);

                }

            }else{

                // This is not a valid path
                consoleError("You can't pass a directory path as an input file path! (You must pass a valid file path)"
                                , 1);

            }

        }else{

            // This is not a valid path
            consoleError("The passed input path is invalid! (You must pass a valid file path)", 1);

        }

        // Print the full output path/directory (Debug)
        consoleDebug("Output directory: %s", globalIO.output.fullPth);

        // Check if the user passed an output file name
        if(*outputName != NULL){

            // Copy the `outputName` variable
            globalIO.output.fileName = calloc(strlen(*outputName) + 1, sizeof(char));
            strcpy(globalIO.output.fileName, *outputName);

            // Free up the memory used by the `outputName` variable
            free(*outputName);

        }else{

            // Set the output file name to the default one
            globalIO.output.fileName = calloc(strlen(STRING_IO_OUTPUT_NAME_DEFAULT)
                                                + 1, sizeof(char));
            strcpy(globalIO.output.fileName, STRING_IO_OUTPUT_NAME_DEFAULT);

        }

        // Print the output file name (Debug)
        consoleDebug("Output file name: %s", globalIO.output.fileName);

        // Free the memory used by the input path variable
        free(*inputPth);
        *inputPth = NULL;

    }else{

        consoleError("No input file path was passed!", 1);

    }

    // Create a temporary directory for the compiler to work in (%{Temp}/StarkScript-XXXXXXXXXXXX/)
    {

        // Generate a 12 characters long random string
        char randStr[13];
        randNumStr(randStr, 12);

        // Get the system's temporary directory
        char *sysTempDir = getTempDir();

        // Get the final temporary directory
        char *tempDir = calloc(strlen(sysTempDir) + 1 + strlen(__STARK_NAME__) + 1 + 12
                                    + 1, sizeof(char));
        sprintf(tempDir, "%s%c%s-%s", sysTempDir,
        #ifdef _WIN32
            '\\'
        #else
            '/'
        #endif
        , __STARK_NAME__, randStr);

        // Copy the temporary directory to the `globalIO` object/interface
        globalIO.tempDir = calloc(strlen(tempDir) + 1, sizeof(char));
        strcpy(globalIO.tempDir, tempDir);

        // Free up the memory used by the "sysTempDir" variable and the "tempDir" variable
        free(tempDir);
        free(sysTempDir);

        // Check if such a directory exists
        // (The chance of such a directory being in there is not really that high, but it's better
        // to be safe that sorry)
        if(access(globalIO.tempDir, F_OK) == 0){

            // You need to stop this process!
            // This is an already-existing directory!
            consoleError("It seems like the randomly generated temporary directory is already in use! (This is a rare thing to happen, try to re-run the compiler)"
                            , 1);

        }

        // Create the temporary folder
        #ifdef _WIN32

            mkdir(globalIO.tempDir);

        #else

            mkdir(globalIO.tempDir, 0700);

        #endif

        // Check if the directory was created successfully
        if(access(globalIO.tempDir, F_OK) != 0){

            // Failed to create a temporary directory!
            consoleError("Couldn't create a temporary directory!%s", 1, STRING_CONSOLE_GITHUB_REPORT);

        }

    }

    // Print the temporary directory path (Debug)
    consoleDebug("Temporary directory: %s", globalIO.tempDir);

}
