/* author: Julian Martinez del Campo
 * class : CMPT 464
 * date  : October 17, 2014
 *
 * Provides error checking routines for use with abstract data types.
 */
#ifndef _ERROR_H_
#define _ERROR_H_

#include <stdio.h>

typedef enum Errors {
    ERROR_NO_ERROR = 0,
    ERROR_UNKNOWN = 1,
    ERROR_MEMORY_ALLOCATION_FAILED,
    ERROR_NULL_PARAMETER,
    ERROR_NOT_FOUND,
    ERROR_INVALID_CAPACITY,
    ERROR_NOT_IMPLEMENTED,
    ERROR_OVERFLOW,
    ERROR_UNDERFLOW
} error_t;

/* The error that was currently generated
 */
error_t error_code;

#ifndef EMBEDDED
/* Get an error message based on the type of error that occured. Retuns a
 * string containing the error message.
 */
char * error_get_message( int error );

/* Print an error message, containg the error that occurred as well as a custom
 * message. Returns the number of characters printed.
 */
int error_print( const char * msg );

/* Print an error message containing a custom message. Returns the number of
 * characters printed.
 */
int error_print_message( FILE * fp, char * msg );
#endif /* EMBEDDED */

#endif /* _ERROR_H_ */
