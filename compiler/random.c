/**
 *
 *  Manage random functions
 *
**/


// Include the `assert.h` library
#include <assert.h>

// Prepare the `rand` function
void randInit(){

    srand((unsigned int)(time(NULL) * 50 - time(NULL) * 5) + 1);
    rand();
    rand();
    rand();

}

// Generate a random string
void randNumStr(char *dest, size_t length){

    // Source: https://stackoverflow.com/questions/15767691/whats-the-c-library-function-to-generate-random-string

    char charset[] = "0123456789";

    while (length-- > 0) {

        size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);

        *dest++ = charset[index];

    }

    *dest = '\0';

}