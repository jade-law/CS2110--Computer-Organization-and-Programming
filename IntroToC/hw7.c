/**
 * @file hw7.c
 * @author YOUR NAME HERE
 * @brief Command-line argument & expression parsing logic
 * @date 2020-03-xx
 */

// DO NOT MODIFY THE INCLUDE(s) LIST
#include <stdio.h>
#include "hw7.h"
#include "errcodes.h"

#define FALSE 0
#define TRUE 1

// One-time defined global array of expressions
struct expression arr[MAX_NUMBER_OF_EXPRESSIONS];

/**
 * @brief Convert a string containing ASCII characters (in decimal) to an int.
 * 
 * @param str A null-terminated C string
 * @return int the corresponding decimal value of the passed in str
 */
int decimalStringToInt(const char *str)
{
    UNUSED_PARAM(str);
    size_t len = my_strlen(str) - 1;
    int value = 0;
    int placeValue = 1;
    for (int i = len; i >= 0; i--) {
        char asciinum = str[i];
        int num;
        if (asciinum >= 48 && asciinum <= 57) {
            num = asciinum - 48;
        } else {
            value = ERR_MALFORMED_HEX_FOUND;
            return value;
        }
        value = value + (num * placeValue);
        placeValue = placeValue * 10;
    }
    return value;
}

/**
 * @brief Convert a string containing ASCII characters (in hex) to an int.
 * 
 * @param str A null-terminated C string
 * @return int the corresponding decimal value of the passed in hexadecimal str
 */
int hexStringToInt(const char *str)
{
    UNUSED_PARAM(str);
    size_t len = my_strlen(str) - 1;
    int value = 0;
    int placeValue = 1;
    for (int i = len; i >= 0; i--) {
        char asciinum = str[i];
        int num = 0;
        if (asciinum > 64 && asciinum < 71) {
            num = asciinum - 55;
        } else if (asciinum > 47 && asciinum < 58) {
            num = asciinum - 48;
        } else {        //move to parseExpression
            value = ERR_MALFORMED_HEX_FOUND;
            return value;
        }
        value = value + (num * placeValue);
        placeValue = placeValue * 16;
    }
    return value;
}

/**
 * @brief Parser algorithm for determining the result of a basic math expression.
 * 
 * @param expression A null terminated expression retrieved as a command line arg
 * @param index Indicating the corresponding struct in the global struct array (for this expression) to be populated
 */
void parseExpression(char *expression, int index)
{
    UNUSED_PARAM(expression);
    UNUSED_PARAM(index);

    // TODO: Iterate through the string, parsing each sum term and adding them to a result

    if (my_strncmp(expression, DEBUG_FLAG, 2) == 0) {
        my_strncpy(arr[index].buffer, ERROR_MSG, 6);
        arr[index].result = 0;
        arr[index].errorCode = ERR_MALFORMED_HEX_FOUND;
        return;
    }
    int value = 0;
    size_t len = my_strlen(expression) - 1;
    if (len < MIN_EXPRESSION_LENGTH) {
        my_strncpy(arr[index].buffer, ERROR_MSG, 5);
        arr[index].result = value;
        arr[index].errorCode = ERR_EXPRESSION_TOO_SMALL;
        return;
    } else if (len >= MAX_EXPRESSION_LENGTH) {
        my_strncpy(arr[index].buffer, ERROR_MSG, 5);
        arr[index].result = value;
        arr[index].errorCode = ERR_EXPRESSION_TOO_LONG;
        return;
    }
    int newExp = 0;
    size_t count = 0;
    int plus = '+';
    int minus = '-';
    while (count < len + 1) {
        int c = expression[count];
        if (c == plus || c == minus) {
            break;
        }
        count = count + 1;
    }
    char numStr[count];
    my_strncpy(numStr, expression, count);
    numStr[count] = '\0';
    int num;
    if (numStr[0] == '0' && numStr[1] == 'x') {
        char hexStr[count - 2];
        my_strncpy(hexStr, &numStr[2], count - 2);
        hexStr[count - 2] = '\0';
        num = hexStringToInt(hexStr);
        if (num == ERR_MALFORMED_HEX_FOUND) {
            my_strncpy(arr[index].buffer, ERROR_MSG, 6);
            arr[index].result = 0;
            arr[index].errorCode = ERR_MALFORMED_HEX_FOUND;
            return;
        }
    } else {
        num = decimalStringToInt(numStr);
        if (num == ERR_MALFORMED_HEX_FOUND) {
            my_strncpy(arr[index].buffer, ERROR_MSG, 6);
            arr[index].result = 0;
            arr[index].errorCode = ERR_MALFORMED_HEX_FOUND;
            return;
        }
    }
    value = num;
    newExp = count;
    while (expression[newExp] != '\0') {
        int sign = expression[newExp];
        count = 0;
        newExp = newExp + 1;
        while (expression[newExp + count] != '\0') {
            int c = expression[newExp + count];
            char ch = expression[newExp + count];
            if (c == plus || c == minus || ch == '\0') {
                break;
            }
            count = count + 1;
        }
        char numSt[count];
        my_strncpy(numSt, &expression[newExp], count);
        numSt[count] = '\0';
        int v;
        if (numSt[0] == '0' && numSt[1] == 'x') {
            char hexStr[count - 2];
            my_strncpy(hexStr, &numSt[2], count - 2);
            hexStr[count - 2] = '\0';
            int num = hexStringToInt(hexStr);
            if (num == ERR_MALFORMED_HEX_FOUND) {
                my_strncpy(arr[index].buffer, ERROR_MSG, 5);
                arr[index].buffer[5] = '\0';
                arr[index].result = 0;
                arr[index].errorCode = ERR_MALFORMED_HEX_FOUND;
                return;
            }
            v = num;
        } else {
            v = decimalStringToInt(numSt);
            if (num == ERR_MALFORMED_HEX_FOUND) {
            my_strncpy(arr[index].buffer, ERROR_MSG, 6);
            arr[index].result = 0;
            arr[index].errorCode = ERR_MALFORMED_HEX_FOUND;
            return;
        }
        }
        if (sign == plus) {
            value = value + v;
        } else {
            value = value - v;
        }
        newExp = newExp + count;
    }
    my_strncpy(arr[index].buffer, expression, len + 1);
    arr[index].result = value;
    arr[index].errorCode = NO_ERROR;
    // TODO: Initialize the struct info for this expression and write it to the struct
}

/**
 * @brief Helper method for printing out the global array struct info
 * DO NOT MODIFY THIS METHOD AS IT IS USED FOR THE LAST STEP (PIPE).
 */
void printArrayDebug(void)
{
    // Safety check
    if (sizeof(arr) / sizeof(arr[0]) != MAX_NUMBER_OF_EXPRESSIONS)
    {
        printf("ERROR: MISMATCH ARRAY LENGTH WITH MACRO: MAX_NUMBER_OF_EXPRESSIONS.\n");
        return;
    }

    for (int i = 0; i < MAX_NUMBER_OF_EXPRESSIONS; i++)
    {
        printf("\nStruct info at index %d:\n", i);
        printf("Expression: %s\n", arr[i].buffer);
        printf("Result: %d\n", arr[i].result);
        printf("ErrorCode: %u\n", arr[i].errorCode);
        printf("---------------------\n");
    }
}

/**
 * @brief Main method, responsible for parsing command line argument and populating expression structs in the global arr
 * 
 * @param argc argument count
 * @param argv argument vector (it's an array of strings)
 * @return int status code of the program termination
 */
int my_main(int argc, char const *argv[])
{
    // UNUSED_FUNC(hexStringToInt);
    // UNUSED_FUNC(parseExpression);
    // UNUSED_FUNC(printArrayDebug);
    // UNUSED_FUNC(decimalStringToInt);
    // UNUSED_PARAM(argv);
    
    // Initial check: We need at least 1 math expression passed in
    // ( Yes argc can possibly be zero! But we don't worry about that too much in this hw :) )
    

    if (argc < 2)
    {
        printf("USAGE:   ./hw7 [-d] \"basic math expressions separated by quotation marks\"\n");
        printf("EXAMPLE: ./hw7 \"3+0x40-7+5\" \"0xA6+5000-45\"\n");
        printf("EXAMPLE FOR PRINTING OUT DEBUG INFO: ./hw7 -d \"3+0x40-7+5\" \"0xA6+5000-45\"\n");
        return 1; // Exit failure (value is implementation defined)
    }

    int start = 1;
    int debugCmp = my_strncmp(argv[1], DEBUG_FLAG, 2);
    if (debugCmp == 0) {
        start = 2;
        if (argc == 2) {
            printf("PROGRAM ERROR: No expression specified!\n");
            return 1;
        }
    }

    if (argc - start > MAX_NUMBER_OF_EXPRESSIONS) {
        printf("PROGRAM ERROR: Too many expressions specified!\n");
        return 1;
    }

    
    // Note 1: If debug flag is presented in any other location besides argv[1], it should be treated as a bad HEX value
    
    for (int i = start; i < argc; i++) {
        size_t len = my_strlen(argv[i]);
        if (len > 0) {
            char c[len]; 
            my_strncpy(c, argv[i], len);
            c[len] = '\0';
            parseExpression(c, i - start);
        } else {
            my_strncpy(arr[i - start].buffer, ERROR_MSG, 5);
            arr[i - start].result = 0;
            arr[i - start].errorCode = ERR_EXPRESSION_TOO_SMALL;
        }
    }
    if (debugCmp == 0) {
        printArrayDebug();
    }
    // Note 2: In order to protect our struct array from overflow and undefined behavior,
    // we need to make sure we don't pass in more command-line arguments than necessary.
    // Later on in the course you will learn how to dynamically allocate space for situations like this!

    return 0; // EXIT_SUCCESS
}
