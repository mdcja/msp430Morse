/* author: Julian Martinez del Campo
 * class : CMPT 464
 * date  : October 17, 2014
 *
 * Implements queue.h
 *
 * The memory complexity of this queue is O(1).  This implementation provides
 * the following run time complexity for a queue with n elements:
 *
 * Operation    | Efficiency
 * -------------|-----------
 * create       | O(1)
 * destroy      | O(n)
 * contains     | O(n)
 * peek         | O(1)
 * insert/push  | O(1)
 * remove/pop   | O(1)
 * count        | O(1)
 * memory       | O(1)
 * capacity     | O(1)
 * print        | O(n)
 * clear        | O(n)
 * reserve      | O(n)
 * remove item  | O(n)
 */
#include <stdlib.h>
#include <stdio.h>

#ifndef EMBEDDED
#include <assert.h>
#endif /* EMBEDDED */

#include "queue.h"
#include "error.h"
#include "attributes.h"

/* A queue with a circular buffer data structure
 */
struct _queue_type {
    void ** queue;
    int head;
    int tail;
    int capacity;
    int count;
    int memory;
    attr_t attr;
};

/* Create a new queue.
 */
queue_t * queue_create( const attr_t * attr, int capacity )
{
    queue_t * new_queue = NULL;

    /* check */
    if( capacity < 1 )
    {
        error_code = ERROR_INVALID_CAPACITY;
#ifndef EMBEDDED
        error_print( "queue_create" );
#endif /* EMBEDDED */

        return NULL;
    }

    /* create */
#ifndef EMBEDDED
    new_queue = (queue_t *)calloc( 1, sizeof( queue_t ) );
    assert( new_queue );
#else
    new_queue = (queue_t *)malloc( sizeof( queue_t ) );
    /* initialization occurs below */
#endif /* EMBEDDED */
    if( !new_queue )
    {
        error_code = ERROR_MEMORY_ALLOCATION_FAILED;
#ifndef EMBEDDED
        error_print( "queue_create" );
#endif /* EMBEDDED */

        return NULL;
    }
    
#ifndef EMBEDDED
    new_queue->queue = (void **)calloc( capacity, sizeof( void * ) );
    assert( new_queue->queue );
#else
    new_queue->queue = (void **)malloc( capacity * sizeof( void * ) );
    /* intialization occurs below */
#endif /* EMBEDDED */
    if( !new_queue )
    {
        error_code = ERROR_MEMORY_ALLOCATION_FAILED;
#ifndef EMBEDDED
        error_print( "queue_create" );
#endif /* EMBEDDED */

        return NULL;
    }

    /* initialize */
    new_queue->head = 0;
    new_queue->tail = 0;
    new_queue->capacity = capacity;
    new_queue->count = 0;
    new_queue->memory = sizeof( queue_t ) + capacity * sizeof( void * );
    if( attr )
    {
        new_queue->attr = *attr;
    }
    else
    {
        attr_init( &new_queue->attr );
    }

#ifndef EMBEDDED
    assert( new_queue->attr.copy );
    assert( new_queue->attr.free );
    assert( new_queue->attr.compare );
    assert( new_queue->attr.print );
#endif /* EMBEDDED */

    return new_queue;
}

/**
 * Destroy a queue.
 *
 * Deallocate all items in the queue, then deallocate the queue itself.
 */
int queue_destroy( queue_t ** queue )
{
    /* check */
    if( !queue )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "queue_destroy" );
#endif /* EMBEDDED */

        return -1;
    }

    if( !*queue )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "queue_destroy" );
#endif /* EMBEDDED */

        return -1;
    }

    /* deallocate all items */
    if( queue_clear( queue ) != 0 )
    {
        return -1;
    }

    /* deallocate queue */
    free( (*queue)->queue );
    (*queue)->queue = NULL;

    free( *queue );
    *queue = NULL;

    return 0;
}

int queue_reserve( queue_t ** queue, int capacity )
{
    void ** new_queue = NULL;
    void ** old_queue = NULL;
    int i = 0;
    int j = 0;

    /* check */
    if( !queue )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "queue_reserve" );
#endif /* EMBEDDED */

        return -1;
    }

    if( !*queue )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "queue_reserve" );
#endif /* EMBEDDED */

        return -1;
    }

    if( capacity < (*queue)->count )
    {
        error_code = ERROR_INVALID_CAPACITY;
#ifndef EMBEDDED
        error_print( "queue_reserve" );
#endif /* EMBEDDED */

        return -1;
    }

    /* create */
#ifndef EMBEDDED
    new_queue = (void **)calloc( capacity, sizeof( void * ) );
    assert( new_queue );
#else
    new_queue = (void **)malloc( capacity * sizeof( void * ) );
    /* intialization occurs below */
#endif /* EMBEDDED */
    if( !new_queue )
    {
        error_code = ERROR_MEMORY_ALLOCATION_FAILED;
#ifndef EMBEDDED
        error_print( "queue_reserve" );
#endif /* EMBEDDED */

        return -1;
    }

    /* copy */
    for( i = (*queue)->head, j = 0; j < (*queue)->count; ++i, ++j )
    {
        new_queue[ j ] = (*queue)->queue[ i % (*queue)->capacity ];
    }

    /* replace */
    old_queue = (*queue)->queue;
    (*queue)->queue = new_queue;
    (*queue)->capacity = capacity;
    (*queue)->head = 0;
    (*queue)->tail = (*queue)->count - 1;
    (*queue)->memory = sizeof( queue_t ) + capacity * sizeof( void * );

    /* deallocate */
    free( old_queue );
    old_queue = NULL;

    return 0;
}

int queue_clear( queue_t ** queue )
{
    int i = 0;

    /* check */
    if( !queue )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "queue_clear" );
#endif /* EMBEDDED */

        return -1;
    }

    if( !*queue )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "queue_clear" );
#endif /* EMBEDDED */

        return -1;
    }

#ifndef EMBEDDED
    assert( (*queue)->attr.free );
#endif /* EMBEDDED */

    /* clear all items */
    for( i = (*queue)->head; (*queue)->count > 0; ++i )
    {
        (*queue)->attr.free( (*queue)->queue[ i % (*queue)->capacity ] );
        (*queue)->queue[ i % (*queue)->capacity ] = NULL;

        (*queue)->count--;
    }
    (*queue)->head = 0;
    (*queue)->tail = 0;

#ifndef EMBEDDED
    assert( (*queue)->count == 0 );
#endif /* EMBEDDED */

    return 0;
}

inline void * queue_peek( const queue_t * queue )
{
    /* check */
    if( !queue )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "queue_peek" );
#endif /* EMBEDDED */

        return NULL;
    }

    return queue->count ? queue->queue[ queue->head ] : NULL;
}

/* Go through all items in the queue and compare against given data.
 */
int queue_contains( const queue_t * queue, const void * data )
{
    int i = 0;
    int j = 0;

    /* check */
    if( !queue )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "queue_contains" );
#endif /* EMBEDDED */

        return -1;
    }

    if( !data )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "queue_contains" );
#endif /* EMBEDDED */

        return -1;
    }

#ifndef EMBEDDED
    assert( queue->attr.compare );
#endif /* EMBEDDED */

    /* look for data */
    for( i = queue->head, j = 0; j < queue->count; ++i, ++j )
    {
        if( queue->attr.compare( queue->queue[ i % queue->capacity ], data ) == 0 )
        {
            return 1;
        }
    }

    return 0;
}

int queue_insert( queue_t ** queue, void * data )
{
    /* check */
    if( !queue )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "queue_insert" );
#endif /* EMBEDDED */

        return -1;
    }

    if( !*queue )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "queue_insert" );
#endif /* EMBEDDED */

        return -1;
    }

    if( !data )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "queue_insert" );
#endif /* EMBEDDED */

        return -1;
    }

    if( (*queue)->count >= (*queue)->capacity )
    {
        error_code = ERROR_OVERFLOW;
#ifndef EMBEDDED
        error_print( "queue_insert" );
#endif /* EMBEDDED */

        return -1;
    }

#ifndef EMBEDDED
    assert( (*queue)->attr.copy );
#endif /* EMBEDDED */

    /* insert item */
    if( (*queue)->count == 0 )
    {
        (*queue)->queue[ (*queue)->head ] = (*queue)->attr.copy( data );
        (*queue)->tail = (*queue)->head;
    }
    else
    {
        (*queue)->queue[ ( (*queue)->tail + 1) % (*queue)->capacity ] = (*queue)->attr.copy( data );
        (*queue)->tail = ((*queue)->tail + 1) % (*queue)->capacity;
    }
    (*queue)->count++;

#ifndef EMBEDDED
    assert( (*queue)->count <= (*queue)->capacity );
#endif /* EMBEDDED */

    return 0;
}

/* This function is an alias for queue_insert.
 */
inline int queue_push( queue_t ** queue, void * data )
{
    return queue_insert( queue, data );
}

int queue_remove( queue_t ** queue )
{
    /* check */
    if( !queue )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "queue_remove" );
#endif /* EMBEDDED */

        return -1;
    }

    if( !*queue )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "queue_remove" );
#endif /* EMBEDDED */

        return -1;
    }

    if( (*queue)->count <= 0 )
    {
        error_code = ERROR_UNDERFLOW;
#ifndef EMBEDDED
        error_print( "queue_remove" );
#endif /* EMBEDDED */

        return -1;
    }

#ifndef EMBEDDED
    assert( (*queue)->attr.free );
#endif /* EMBEDDED */

    /* remove */
    (*queue)->attr.free( (*queue)->queue[ (*queue)->head ] );
    (*queue)->queue[ (*queue)->head ] = NULL;

    (*queue)->head = ((*queue)->head + 1) % (*queue)->capacity;
    (*queue)->count--;

#ifndef EMBEDDED
    assert( (*queue)->count >= 0 );
#endif /* EMBEDDED */

    return 0;
}

/* This function is an alias for queue_remove.
 */
inline int queue_pop( queue_t ** queue )
{
    return queue_remove( queue );
}

/* Look for the item in the queue and then deallocate it.
 */
int queue_remove_item( queue_t ** queue, void * data )
{
    int i = 0;
    int j = 0;

    /* check */
    if( !queue )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "queue_remove_item" );
#endif /* EMBEDDED */

        return -1;
    }

    if( !*queue )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "queue_remove_item" );
#endif /* EMBEDDED */

        return -1;
    }

    if( !data )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "queue_remove_item" );
#endif /* EMBEDDED */

        return -1;
    }

#ifndef EMBEDDED
    assert( (*queue)->attr.compare );
    assert( (*queue)->attr.free );
#endif /* EMBEDDED */

    /* look for data */
    for( i = (*queue)->head, j = 0; j < (*queue)->count; ++i, ++j )
    {
        if( (*queue)->attr.compare( (*queue)->queue[ i % (*queue)->capacity ], data ) == 0 )
        {
            (*queue)->attr.free( (*queue)->queue[ i % (*queue)->capacity ] );
            (*queue)->queue[ i % (*queue)->capacity ] = NULL;
            (*queue)->count--;

            /* shift */
            for( ; j < (*queue)->count; ++i, ++j )
            {
                (*queue)->queue[ i % (*queue)->capacity ] = (*queue)->queue[ (i + 1) % (*queue)->capacity ];
            }
            (*queue)->queue[ i ] = NULL;

            if( (*queue)->tail == 0 )
            {
                (*queue)->tail = (*queue)->capacity - 1;
            }
            else
            {
                (*queue)->tail--;
            }

#ifndef EMBEDDED
            assert( (*queue)->count >= 0 );
#endif /* EMBEDDED */

            return 0;
        }
    }

    error_code = ERROR_NOT_FOUND;
#ifndef EMBEDDED
    error_print( "queue_remove_item" );
#endif /* EMBEDDED */

    return -1;
}

#ifndef EMBEDDED

int queue_print( const queue_t * queue, FILE * fp )
{
    int i = 0;
    int j = 0;
    int nchr = 0;

    /* check */
    if( !queue )
    {
        error_code = ERROR_NULL_PARAMETER;
        error_print( "queue_print" );

        return -1;
    }

    if( !fp )
    {
        error_code = ERROR_NULL_PARAMETER;
        error_print( "queue_print" );

        return -1;
    }

    assert( queue->attr.print );

    /* print */
    nchr += fprintf( fp, "Queue (%p)\n", (void *)queue );
    nchr += fprintf( fp, " - capacity = %d\n", queue->capacity );
    nchr += fprintf( fp, " - count = %d\n", queue->count );
    nchr += fprintf( fp, " - memory = %d\n", queue->memory );

    for( i = queue->head; j < queue->count; ++i, ++j )
    {
        nchr += queue->attr.print( queue->queue[ i % queue->capacity ], fp );
        nchr += fprintf( fp, "\n" );
    }

    return nchr;
}

#endif /* EMBEDDED */

int queue_memory( const queue_t * queue )
{
    /* check */
    if( !queue )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "queue_memory" );
#endif /* EMBEDDED */

        return -1;
    }

#ifndef EMBEDDED
    assert( queue->memory > 0 );
#endif /* EMBEDDED */

    return queue->memory;
}

int queue_count( const queue_t * queue )
{
    /* check */
    if( !queue )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "queue_count" );
#endif /* EMBEDDED */

        return -1;
    }

#ifndef EMBEDDED
    assert( queue->count >= 0 );
#endif /* EMBEDDED */

    return queue->count;
}

int queue_capacity( const queue_t * queue )
{
    /* check */
    if( !queue )
    {
        error_code = ERROR_NULL_PARAMETER;
#ifndef EMBEDDED
        error_print( "queue_capacity" );
#endif /* EMBEDDED */

        return -1;
    }

#ifndef EMBEDDED
    assert( queue->capacity > 0 );
#endif /* EMBEDDED */

    return queue->capacity;
}
