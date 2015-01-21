/* author: Julian Martinez del Campo
 * class : CMPT 464
 * date  : October 17, 2014
 *
 * This file provides functions for controlling the LEDs.
 */
#ifndef _LEDS_H_
#define _LEDS_H_

#include <stdint.h>

/* Different LEDs available
 */
typedef enum {
    GREEN   = 0x02,
    YELLOW  = 0x08,
    RED     = 0x04
} led_t;

/* Configure ports for LED use
 */
void leds_initialize( void );

/* Turn on the specified LEDs
 */
void leds_on( uint8_t );

/* Turn off the specified LEDs
 */
void leds_off( uint8_t );

#endif /* _LEDS_H_ */
