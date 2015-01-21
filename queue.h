/* author: Julian Martinez del Campo
 * class : CMPT 464
 * date  : October 17, 2014
 *
 * Provides a queue abstract data type.
 */
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>

#include "attributes.h"

typedef struct _queue_type queue_t;

/* Create a new queue, if attr is NULL then use the default attributes. Returns
 * a new queue on success, else returns NULL.
 */
queue_t * queue_create( const attr_t * attr, int capacity );

/* Destroy a queue. Returns 0 on success, else returns -1.
 */
int queue_destroy( queue_t ** queue );

/* Resize a queue. Returns 0 on success, else returns -1.
 */
int queue_reserve( queue_t ** queue, int capacity );

/* Remove all items from a queue. Returns 0 on success, else returns -1.
 */
int queue_clear( queue_t ** queue );

/* Get data at the front of the queue. Returns the data at the front of the
 * queue, returns NULL if queue is empty or if an error ocurred.
 */
void * queue_peek( const queue_t * queue );

/* Check if the queue contains data. Returns 1 if the data is in the queue, 0
 * if the data is not in the queue, else returns -1.
 */
int queue_contains( const queue_t * queue, const void * data );

/* Insert data into the queue. Returns 0 on success, else returns -1.
 */
int queue_insert( queue_t ** queue, void * data );

/* Push data onto the queue. This function is an alias for queue_insert().
 * Returns 0 on success, else return -1.
 */
int queue_push( queue_t ** queue, void * data );

/* Remove items from the queue. Returns 0 on success, else returns -1.
 */
int queue_remove( queue_t ** queue );

/* Pop items off the queue. This function is an alias for queue_remove().
 * Returns 0 on success, else returns -1.
 */
int queue_pop( queue_t ** queue );

/* Remove a specific item from the queue. Returns 0 on success, else returns
 * -1.
 */
int queue_remove_item( queue_t ** queue, void * data );

#ifndef EMBEDDED
/* Print the contents of the queue and queue information. Returns the number of
 * characters printed to the screen, else returns -1 on error.
 */
int queue_print( const queue_t * queue, FILE * fp );
#endif /* EMBEDDED */

/* Get the memory usage of the queue. Returns the size (in bytes) of the queue,
 * else returns -1 on error.
 */
int queue_memory( const queue_t * queue );

/* Get the number of items in the queue. Returns the number of items in the
 * queue, else returns -1 on error.
 */
int queue_count( const queue_t * queue );

/* Get the capacity of the queue. Returns the capacity, else returns -1 on
 * error.
 */
int queue_capacity( const queue_t * queue );

#endif /* _QUEUE_H_ */
