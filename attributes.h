/* author: Julian Martinez del Campo
 * class : CMPT 464
 * date  : October 17, 2014
 *
 * This file provides attributes for abstract data types
 */
#ifndef _ATTRIBUTES_H_
#define _ATTRIBUTES_H_

#ifndef EMBEDDED
#include <stdio.h>
#endif /* EMBEDDED */

/* Contains function pointers to basic operations
 */
typedef struct _data_attributes_type {
    /* The comparator. Takes in two objects to compare, then returns -1 if the
     * first value is smaller than the second, 0 if they are equal, and 1 if
     * the first value is greater than the second value.
     */
    int (*compare)( const void *, const void * );

#ifndef EMBEDDED
    /* Print an object. Takes in an object to print, and a filepointer to print
     * to. It returns the number of characters printed.
     */
    int (*print)( const void *, FILE * );
#endif /* EMBEDDED */

    /* Copy an object. Takes in an object to copy, creates a copy of it, then
     * returns the copied value.
     */
    void * (*copy)( const void * );

    /* Free an object. Destroy an object in memory.
     */
    void (*free)( void * );
    
    /* Hash an object. Creates a unique, but reproducible hash based on the
     * object and returns the hash.
     */
    unsigned long (*hash)( const void * );
} attr_t;

/* Initialize attributes to default settings. Assigns generic pointer functions
 * to handle operations, making it safe for use.
 */
int attr_init( attr_t * attr );

/* Set the compare pointer function. Returns 0 on success, else returns -1.
 */
int attr_set_compare( attr_t * attr, int (*data_compare)( const void *, const void * ) );

#ifndef EMBEDDED
/* Set the print function. Returns 0 on success, else returns -1.
 */
int attr_set_print( attr_t * attr, int (*data_print)( const void *, FILE * ) );
#endif /* EMBEDDED */

/* Set the copy function. Returns 0 on success, else returns -1.
 */
int attr_set_copy( attr_t * attr, void * (*data_copy)( const void * ) );

/* Set the free function. Returns 0 on success, else returns -1.
 */
int attr_set_free( attr_t * attr, void (*data_free)( void * ) );

/* Set the hash function. Returns 0 on success, else returns -1.
 */
int attr_set_hash( attr_t * attr, unsigned long (*data_hash)( const void * ) );

#endif /* _ATTRIBUTES_H_ */
