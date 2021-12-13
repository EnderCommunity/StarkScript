/**
 *
 *  Manage paths-related functions
 *
**/


// Define a function that can join a directory's path with a file name and an extension
// ${dir}(/|\\)${fileName}.${ext}
char* joinDirFileExt(char *dir, char *fileName, char *ext){

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
