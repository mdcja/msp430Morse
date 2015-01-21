/* author: Julian Martinez del Campo
 * class : CMPT 464
 * date  : October 17, 2014
 *
 * Implements leds.h
 */
#include <msp430.h>
#include "leds.h"

void leds_initialize( void )
{
    P4DIR = 0x0E;
    P4OUT = 0x0E;
}

void leds_on( uint8_t leds )
{
    P4OUT &= ~leds;
}

void leds_off( uint8_t leds )
{
    P4OUT |= leds;
}
