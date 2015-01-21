/* author: Julian Martinez del Campo
 * class : CMPT 464
 * date  : October 17, 2014
 *
 * This file provides functions for manipulating and checking characters
 * recieved from the UART.
 */
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <stdint.h>

/* Copy a character (for use with attributes/queue)
 */
void * character_copy( const void * );

/* Free a character (for use with attributes/queue)
 */
void character_free( void * );

/* Check if a character is a control character
 */
int8_t character_is_control( uint8_t );

/* Check if a character is valid
 */
int8_t character_is_valid( uint8_t );

#endif /* _CHARACTER_H_ */
