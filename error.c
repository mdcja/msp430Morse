/* author: Julian Martinez del Campo
 * class : CMPT 464
 * date  : October 17, 2014
 *
 * This file provides error checking functions for use with attributes.h and
 * queue.h
 */
#include <stdio.h>
#include "error.h"

#ifndef EMBEDDED
#define STRING_LENGTH 256

/* Get the error name. This function returns a string containing the name of
 * the error that occured
 */
static char * error_name( error_t error )
{
    static char * error_names[ STRING_LENGTH ] = {
        "no error",
        "unknown",
        "memory allocation failed",
        "null parameter",
        "not found",
        "invalid capacity",
        "not implemented",
        "overflow",
        "underflow"
    };
        
    switch( error )
    {
    case ERROR_NO_ERROR:
        return error_names[ ERROR_NO_ERROR ];
    case ERROR_MEMORY_ALLOCATION_FAILED:
        return error_names[ ERROR_MEMORY_ALLOCATION_FAILED ];
    case ERROR_NULL_PARAMETER:
        return error_names[ ERROR_NULL_PARAMETER ];
    case ERROR_NOT_FOUND:
        return error_names[ ERROR_NOT_FOUND ];
    case ERROR_INVALID_CAPACITY:
        return error_names[ ERROR_INVALID_CAPACITY ];
    case ERROR_NOT_IMPLEMENTED:
        return error_names[ ERROR_NOT_IMPLEMENTED ];
    case ERROR_OVERFLOW:
        return error_names[ ERROR_OVERFLOW ];
    case ERROR_UNDERFLOW:
        return error_names[ ERROR_UNDERFLOW ];
    default:
        return error_names[ ERROR_UNKNOWN ];
    }
}

/* Initialize error code
 */
inline void error_initialize( void )
{
    error_code = ERROR_NO_ERROR;
}

/* Reset error code
 */
inline void error_reset( void )
{
    error_code = ERROR_NO_ERROR;
}

/* Get error message
 */
inline char * error_get_message( int error )
{
    if( ( error < ERROR_NO_ERROR ) || ( error > ERROR_UNDERFLOW ) )
    {
        error = ERROR_UNKNOWN;
    }
    
    return error_name( error );
}

/* Print the error that occured
 */
int error_print( const char * msg )
{
    int nchr = 0;

    if( msg == NULL )
    {
        error_code = ERROR_NULL_PARAMETER;
        return -1;
    }

#ifndef NERROR
        nchr += fprintf( stderr, "ERROR: (%d) %s : %s\n", error_code, error_name( error_code ), msg );
#endif /* NERROR */
    return nchr;
}

/* Print the error that occured with a message
 */
int error_print_message( FILE * fp, char * msg )
{
    if( fp == NULL )
    {
        error_code = ERROR_NULL_PARAMETER;
        return -1;
    }

    if( msg == NULL )
    {
        error_code = ERROR_NULL_PARAMETER;
        return -1;
    }

    int nchr = 0;
#ifndef NERROR
    nchr += fprintf( fp, "ERROR: (%d) %s : %s\n", error_code, error_name( error_code ), msg );
#endif /* NERROR */
    return nchr;
}

#endif /* EMBEDDED */
