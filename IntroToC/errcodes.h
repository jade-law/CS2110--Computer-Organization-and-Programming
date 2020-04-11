// DO NOT MODIFY THIS FILE

/**
 * @brief Header file for global predefined error codes for usage of the hw7 program.
 */
#ifndef ERRCODES_H
#define ERRCODES_H

#define ERROR_MSG "ERROR"               /* Buffer's error message */

#define NO_ERROR 2110                   /* 21ten is awesome! */

#define ERR_EXPRESSION_TOO_SMALL 300    /* @see hw7.h for expression length requirement */
#define ERR_EXPRESSION_TOO_LONG  301    /* @see hw7.h for expression length requirement */
#define ERR_MALFORMED_HEX_FOUND  302    /* Bad hex number found in expression! */

// EXTRA INFO/Side-Note: error values start at (arbitrary value) 301 to avoid confusion with the possible values for 
// the errno macro within the errno.h library and also HTTP and socket programming error codes

#endif
