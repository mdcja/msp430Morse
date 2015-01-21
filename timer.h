/* author: Julian Martinez del Campo
 * class : CMPT 464
 * date  : October 17, 2014
 *
 * This file provides functions for controlling the timing of morse code
 * sequences.
 */
#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>

/* Possible speeds allowed by the morse code printer
 */
typedef enum {
    T_24MS = 98,     /* ~50 WPM */
    T_48MS = 196,    /* ~25 WPM */
    T_120MS = 491,   /* ~10 WPM */
    T_240MS = 983,   /* ~5 WPM */
    T_480MS = 1966,  /* ~2.5 WPM */
    T_1200MS = 4915  /* ~1 WPM */
} timer_speed_t;

/* Configure the timer for use
 */
void timer_configure( void );

/* Adjust the timers speed depending on the control character
 */
void timer_adjust( timer_speed_t *, uint8_t );

#endif /* _TIMER_H_ */
