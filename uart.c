/* author: Julian Martinez del Campo
 * class : CMPT 464
 * date  : October 17, 2014
 *
 * Implements uart.h
 */
#include <msp430.h>
#include "uart.h"

/* Code adapted from an example by Nickolas Boers 
 */
void uart_configure( uart_speed_t speed )
{
    P3SEL |= 0x30;      /* Select peripheral mode */
    U0CTL |= SWRST;     /* enable software reset */
    U0CTL |= CHAR;      /* enable 8 bit characters */

    switch( speed )
    {
        case UART_2400: /* fall through */
        default:
            /* initialize all USART registers */
            U0TCTL |= 0x10;    /* 32 kHz clock */
            
            /* set speed to 2400 baud */
            UBR00 = 0x0D;
            UBR10 = 0x00;
            UMCTL0 = 0x6D;

            break;
    }

    ME1 |= UTXE0 | URXE0;   /* enable USART module */
    U0CTL &= ~SWRST;        /* clear software reset */
    IE1 |= URXIE0;          /* enable RX interrupt */
}
