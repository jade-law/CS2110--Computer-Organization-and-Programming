// DO NOT MODIFY THIS FILE

/**
 * @brief Header file for global macros, stuctures and fields to be used by the hw7 program.
 */
#ifndef HW7_H
#define HW7_H

#include <stddef.h>

#define UNUSED_PARAM(x) ((void) x) // This macro is only used for turning off compiler errors initially
#define UNUSED_FUNC(x) ((void) x)  // This macro is only used for turning off compiler errors initially

#define DEBUG_FLAG "-d"

#define MIN_EXPRESSION_LENGTH 1     // Without the NULL terminator (including the arithmetic signs & hex notation)
#define MAX_EXPRESSION_LENGTH 25    // Without the NULL terminator (including the arithmetic signs & hex notation)
#define MAX_NUMBER_OF_EXPRESSIONS 5 // Size of the global struct array

struct expression
{
    char buffer[MAX_EXPRESSION_LENGTH + 1];
    int result;
    unsigned int errorCode;
};

// Array of struct expressions
extern struct expression arr[MAX_NUMBER_OF_EXPRESSIONS];

// Wrapper function for the real main function in main.c
int my_main(int argc, char const *argv[]);

// Function prototypes for my_string.c
size_t my_strlen(const char *s);
int my_strncmp(const char *s1, const char *s2, size_t n);
char *my_strncpy(char *dest, const char *src, size_t n);

#endif
