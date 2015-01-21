/* author: Julian Martinez del Campo
 * class : CMPT 464
 * date  : October 17, 2014
 *
 * This file provides the possible states in the morse code machine.
 */
#ifndef _STATE_H_
#define _STATE_H_

#include <stdint.h>
#include "morse_code.h"

typedef enum _states {
    S_CHECK_BUF,        /* check buffer */
    S_PRINT,            /* print character */
    S_SPACE,            /* space for a dot */
    S_DONE,             /* finished printing character */
    S_SPACE_WORDS,      /* space between words */
    S_SPACE_LETTERS     /* space between letters */
} states_t;

/* The state of the the morse code printing 
 */
typedef struct _state {
    uint8_t position;           /* current position in the character being printed */
    states_t state;             /* current state */
    const morse_code_t * character;   /* current character being printed */
} state_t;

#endif /* _STATE_H_ */
