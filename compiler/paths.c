/**
 *
 *  Manage paths-related functions
 *
**/


// Include the `limits.h` library
// It's used to access the max length of certain values (files names, paths, etc)
#include <limits.h>

// Define a function that can join a directory's path with a file name and an extension
// ${dir}(/|\\)${fileName}.${ext}
char* joinDirFileExt(const char *dir, const char *fileName, const char *ext){

    // Allocate memory for the return string
    char *fullPth = calloc(strlen(dir) + 1 + strlen(fileName) + 1 + strlen(ext) + 1, sizeof(char));

    // Combine the path values
    sprintf(fullPth, "%s%c%s.%s", dir,
    #ifdef _WIN32
        '\\'
    #else
        '/'
    #endif
    , fileName, ext);

    // Return the full path
    return fullPth;

}

// Define a function that can join a directory's path with a file name
// ${dir}(/|\\)${fileName}
// Note that you can use this function with folders too!
char* joinDirFile(char *dir, char *fileName){

    // Allocate memory for the return string
    char *fullPth = calloc(strlen(dir) + 1 + strlen(fileName) + 1, sizeof(char));

    // Combine the path values
    sprintf(fullPth, "%s%c%s", dir,
    #ifdef _WIN32
        '\\'
    #else
        '/'
    #endif
    , fileName);

    // Return the full path
    return fullPth;

}

// Define a function that can get the absolute path of any given path
char* absPth(char *pth){

    char *absolutePth = calloc(PATH_MAX + 1, sizeof(char));

    // To get the full path of the input path, you will need to use the dedicated native function
    // for that!
    #ifdef _WIN32

        // To get the full path of a file on Windows, you will need to use the `_fullpath`
        // function. You can read more about the `_fullpath` function here:
        // https://docs.microsoft.com/cpp/c-runtime-library/reference/fullpath-wfullpath

        // Store the valid path to the global IO interface
        _fullpath(absolutePth, pth, PATH_MAX);

    #elif __linux__

        // To get the full path of a file on Linux, you will need to use the `realpath`
        // function. You can read more about the `realpath` function here:
        // https://man7.org/linux/man-pages/man3/realpath.3.html

        // Store the valid path to the global IO interface
        realpath(pth, absolutePth);

    #else

        // You can't really know the native function for an operating system that you don't
        // know, so return an error to the user to tell them about this.
        consoleError("Your operating system is not supported by the compiler!%s", 1,
                STRING_CONSOLE_GITHUB_REPORT);

    #endif

    return absolutePth;

}

// Define a function that can get the folder's path of a file
char* getFileDir(char *filePth){

    // Get the absolute path of the input file's directory/folder

    // Get the last occurence of the "/" character or the "\\" character
    char *lastOccr;
    #ifdef _WIN32

        lastOccr = strrchr(filePth, '\\');

    #else

        lastOccr = strrchr(filePth, '/');

    #endif
    int position = lastOccr - filePth;

    // Get the absolute path of the input file directory
    char* dirPth = calloc(position + 1, sizeof(char));

    // Copy the directory of the input file (without the file name)
    for(int i = 0; i < position; i++){
                 
        dirPth[i] = filePth[i];

    }

    // Add the string end character
    dirPth[position] = '\0';

    // Return the path
    return dirPth;

}

// Define a function that can get the directory of the compiler
// For more info, read:
// https://stackoverflow.com/questions/933850/how-do-i-find-the-location-of-the-executable-in-c
char* getCompilerDir(char *pathArg){

    // Prepare the executable path variable
    char *execPath;

    // Get the executable path
    if(pathArg[0] == '/' || pathArg[0] == '\\'){

        // This path is an absolute path!

        // Allocate memory for the path
        execPath = calloc(strlen(pathArg) + 1, sizeof(char));

        // Copy this path!
        strcpy(execPath, pathArg);

    }else if(pathArg[0] == '.' || (
        (int)((strchr(pathArg, '/')) - pathArg) > 0 ||
        (int)((strchr(pathArg, '\\')) - pathArg) > 0
    )){

        // This is a relative path!

        // Get the absolute path of the compiler
        execPath = absPth(pathArg);

    }else{

        // Oh oh, this is going to be harder than expected...

        // Return an error for now...
        consoleError("Failed to get the directory of the compiler...this is a temporary error message!", 1);

    }

    // Get the folder of the exectuable
    char* execDirPath = getFileDir(execPath);

    // Get the main directory of the compiler
    char* mainPathR = calloc(strlen(execDirPath) + 3 + 1, sizeof(char)),
        slash;
    #ifdef _WIN32

        slash = '\\';

    #else

        slash = '/';

    #endif
    sprintf(mainPathR, "%s%c..", execDirPath, slash);
    char* mainPath = absPth(mainPathR);

    // Free all the memory used by the paths that are not going to be returned
    free(execPath);
    free(mainPathR);
    free(execDirPath);

    // Return the main path
    return mainPath;

}