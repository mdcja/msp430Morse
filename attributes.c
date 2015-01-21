/* author: Julian Martinez del Campo
 * class : CMPT 464
 * date  : October 17, 2014
 *
 * This file provides an implementation of attributes.h
 */
#include <stdlib.h>
#include <stdio.h>

#ifndef EMBEDDED
#include <string.h>
#endif /* EMBEDDED */

#include "attributes.h"
#include "error.h"

/* The default comparator compares pointer values
 */
static int default_compare( const void * data1, const void * data2 )
{
    if( data1 == data2 )
    {
        return 0;
    }
    else if( data1 < data2 )
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

#ifndef EMBEDDED
/* The default print function prints the pointer address to the object
 */
static int default_print( const void * data, FILE * fp )
{
    return fprintf( fp, "%p", data );
}

#endif /* EMBEDDED */

/* The default copy function returns the object, it does not allocate memory.
 */
static void * default_copy( const void * data )
{
    return (void *)data;
}

/* The default free function does nothing.
 */
static void default_free( void * data )
{
    return;
}

/* The default hash function uses a CRC variant, and hashes the pointer to an
 * object.  
 * see: http://www.cs.hmc.edu/~geoff/classes/hmc.cs070.200101/homework10/hashfuncs.html
 */
static unsigned long default_hash( const void * key )
{
    unsigned long hash = *(int*)key;
    unsigned long high_order = 0;

    high_order = hash & 0xf8000000;
    hash = hash << 5;
    hash = hash ^ ( high_order >> 27 );
    hash = hash ^ 1; /* n */

    return hash;
}

int attr_init( attr_t * attr )
{
    if( attr == NULL )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "attr_init: attr" );
#endif /* EMBEDDED */

        return -1;
    }

    attr->compare = default_compare;
#ifndef EMBEDDED
    attr->print = default_print;
#endif /* EMBEDDED */
    attr->copy = default_copy;
    attr->free = default_free;
    attr->hash = default_hash;
            
    return 0;
}

int attr_set_compare( attr_t * attr, int (*data_compare)( const void *, const void *) )
{
    if( attr == NULL )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "attr_set_compare: attr" );
#endif /* EMBEDDED */

        return -1;
    }

    if( data_compare == NULL )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "attr_set_compare: data_compare" );
#endif /* EMBEDDED */

        return -1;
    }

    attr->compare = data_compare;

    return 0;
}

#ifndef EMBEDDED

int attr_set_print( attr_t * attr, int (*data_print)( const void *, FILE * ) )
{
    if( attr == NULL )
    {
        error_code = ERROR_NULL_PARAMETER;
        error_print( "attr_set_print: attr" );
        
        return -1;
    }

    if( data_print == NULL )
    {
        error_code = ERROR_NULL_PARAMETER;
        error_print( "attr_set_print: data_print" );

        return -1;
    }

    attr->print = data_print;

    return 0;
}

#endif /* EMBEDDED */

int attr_set_copy( attr_t * attr, void * (*data_copy)( const void * ) )
{
    if( attr == NULL )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "attr_set_copy: attr" );
#endif /* EMBEDDED */

        return -1;
    }

    if( data_copy == NULL )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "attr_set_copy: data_copy" );
#endif /* EMBEDDED */

        return -1;
    }

    attr->copy = data_copy;

    return 0;
}

int attr_set_free( attr_t * attr, void (*data_free)( void * ) )
{
    if( attr == NULL )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "attr_set_free: attr" );
#endif /* EMBEDDED */

        return -1;
    }

    if( data_free == NULL )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "attr_set_free: data_free" );
#endif /* EMBEDDED */

        return -1;
    }

    attr->free = data_free;

    return 0;
}

int attr_set_hash( attr_t * attr, unsigned long (*data_hash)(const void *) )
{
    if( attr == NULL )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "attr_set_hash: attr" );
#endif /* EMBEDDED */

        return -1;
    }

    if( data_hash == NULL )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "attr_set_hash: data_hash" );
#endif /* EMBEDDED */

        return -1;
    }

    attr->hash = data_hash;

    return 0;
}
