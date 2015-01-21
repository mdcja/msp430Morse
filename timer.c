/* author: Julian Martinez del Campo
 * class : CMPT 464
 * date  : October 17, 2014
 *
 * Implements timer.h
 */
#include <msp430.h>
#include "timer.h"

void timer_configure( void )
{
    /* Disable timer A before configuration */
    TACTL &= ~0x0030;

    /* Configure timer A */
    TACTL = TACLR;              /* reset clock */
    TACTL |= TASSEL_1 + ID_3;   /* 32 kHz ACLK; 32/8 = 4 kHz */
 
    /* Enable interrupts and set the initial count */
    TACCTL0 |= CCIE;
    TACCR0 = TAR + T_24MS;

    /* enable timer */
    TACTL |= MC_2;      /* set continuous mode */
}

void timer_increase_speed( timer_speed_t * t )
{
    switch( *t )
    {
        case T_24MS:
            *t = T_48MS;
            break;

        case T_48MS:
            *t = T_120MS;
            break;

        case T_120MS:
            *t = T_240MS;
            break;

        case T_240MS:
            *t = T_480MS;
            break;

        case T_480MS:
            *t = T_1200MS;
            break;

        case T_1200MS:
            *t = T_1200MS;
            break;

        default:
            *t = T_24MS;
            break;
    }
}

void timer_decrease_speed( timer_speed_t * t )
{
    switch( *t )
    {
        case T_24MS:
            *t = T_24MS;
            break;

        case T_48MS:
            *t = T_24MS;
            break;

        case T_120MS:
            *t = T_48MS;
            break;

        case T_240MS:
            *t = T_120MS;
            break;

        case T_480MS:
            *t = T_240MS;
            break;

        case T_1200MS:
            *t = T_480MS;
            break;

        default:
            *t = T_24MS;
            break;
    }
}

void timer_adjust( timer_speed_t * t, uint8_t character )
{
    if( character == '<' )
    {
        timer_increase_speed( t );
    }
    else /* character == '>' */
    {
        timer_decrease_speed( t );
    }
}
