
#include <stdio.h>
#include <check.h>
#include <stddef.h>
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define RETURN_ERROR_VALUE -100

// Suites
extern Suite *hw7_suite(void);
extern Suite *my_string_suite(void);

#define tcase_hack(suite, setup_fixture, teardown_fixture, func)        \
    {                                                                   \
        TCase *tc = tcase_create(STRINGIFY(func));                      \
        tcase_add_checked_fixture(tc, setup_fixture, teardown_fixture); \
        tcase_add_test(tc, func);                                       \
        suite_add_tcase(s, tc);                                         \
    }

/******************************************************************************/
/**************************** hw7 Header Info *********************************/
/******************************************************************************/

#define UNUSED_PARAM(x) ((void)x) // This macro is only used for turning off compiler errors initially
#define UNUSED_FUNC(x) ((void)x)  // This macro is only used for turning off compiler errors initially

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

// Function prototypes for hw7.c  -- diff from student header
int decimalStringToInt(const char *str);
int hexStringToInt(const char *str);
void parseExpression(char *expression, int index);
int my_main(int argc, char const *argv[]);

// Function prototypes for my_string.c
size_t my_strlen(const char *s);
int my_strncmp(const char *s1, const char *s2, size_t n);
char *my_strncpy(char *dest, const char *src, size_t n);
