/* author: Julian Martinez del Campo
 * class : CMPT 464
 * date  : October 17, 2014
 *
 * This file provides functions for controlling morse code characters.
 */
#ifndef _MORSE_CODE_H_
#define _MORSE_CODE_H_

#include <stdint.h>

#define DOT 0
#define DASH 1

/* Makes up a morse code character
 */
typedef struct _morse_code {
    uint8_t character;      /* Holds the character encoded in binary */
    uint8_t length;         /* Holds the length of the character sequence */
} morse_code_t;

/* Get the value of the nth position of the morse code character
 */
int8_t morse_code_get_value( const morse_code_t * , uint8_t );

/* Get the morse code character corresponding to the input character
 */
const morse_code_t * morse_code_get( uint8_t );

#endif /* _MORSE_CODE_H_ */
