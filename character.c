/* author: Julian Martinez del Campo
 * class : CMPT 464
 * date  : October 17, 2014
 *
 * Implements character.h
 */
#include <stdlib.h>
#include "character.h"
#include "morse_code.h"

void * character_copy( const void * c )
{
    uint8_t * character = NULL;

    character = (uint8_t *)malloc( sizeof( uint8_t ) );
    if( character == NULL )
        return NULL;

    *character = *(uint8_t *)c;     /* copy character */

    return character;
}

void character_free( void * c )
{
    free( c );
    c = NULL;
}

int8_t character_is_control( uint8_t c )
{
    if( c == '<' || c == '>' )
        return 1;

    return 0;
}

int8_t character_is_valid( uint8_t c )
{
    if( morse_code_get( c ) )
        return 1;

    return 0;
}
