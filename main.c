/* author: Julian Martinez del Campo
 * class : CMPT 464
 * date  : October 17, 2014
 *
 * This program prints characters in morse code. It receives a byte using the
 * UART and then processes it and, if the input is valid, it displays the
 * character in morse code by flashing the red LEDs on the board. The UART is
 * configured to use 2400 baud data speeds, 8 bit characters, and no parity
 * bits. The timing is configurable ranging from 24ms to 1200ms. Timing can be
 * adjusted by using the control characters '<' and '>' to decrease and
 * increase the output speed. The default speed is 240ms. Characters can be
 * read faster than they can be output. By default 50 characters are buffered,
 * if the buffer reaches maximum capacity new characters are discarded.
 */
#include <msp430.h>
#include <stdlib.h>

#include "leds.h"
#include "uart.h"
#include "character.h"
#include "timer.h"
#include "state.h"
#include "morse_code.h"
#include "attributes.h"
#include "queue.h"

#define MAX_BUF 50      /* max size of the buffer */
#define DOT_LENGTH 1    /* the length of a morse code dot */
#define DASH_LENGTH 3   /* the length of a morse code dash */
#define SPACE_LENGTH 7  /* the length of a morse code space */
#define P3 0x08         /* port 3 */

queue_t * buffer;       /* the character buffer */
state_t state;          /* the state of the morse code */
timer_speed_t timer;    /* the timer */

/* Disable the watchdog
 */
void disable_watchdog( void )
{
    WDTCTL = WDTPW + WDTHOLD;
}

int main( void )
{
    attr_t attributes;

    disable_watchdog();
    leds_initialize();
    uart_configure( UART_2400 );    /* default speed is 2400 baud */
    timer_configure();
    timer = T_240MS;                /* default timer speed is 240 ms */
    P6DIR = P3;                     /* configure P6.3 */

    /* configure queue */
    attr_init( &attributes );
    attr_set_copy( &attributes, character_copy );
    attr_set_free( &attributes, character_free );

    buffer = queue_create( &attributes, MAX_BUF );
    if( buffer == NULL )
        exit( 1 );

    /* initialize state */
    state.state = S_CHECK_BUF;
    state.character = NULL;
    state.position = 0;

    /* enable interrupts and low power mode */
    _BIS_SR( GIE | LPM3_bits);
    
    while( 1 );

    queue_destroy( &buffer );

    return 0;
}

/* UART receiver interrupt service routine
 *
 * Receives characters over the UART and either changes the speed of the timer,
 * or adds a character to the buffer.
 */
#pragma vector=USART0RX_VECTOR
__interrupt void uart_rx_isr()
{
    uint8_t character = 0;
    static uint8_t prev_character = 0;
    
    character = U0RXBUF;    /* get character from UART */

    if( character_is_control( character ) )
    {
        timer_adjust( &timer, character ); 
    }

    if( character_is_valid( character ) )
    {
        /* ignore two or more spaces in a row */
        if( !( prev_character == ' ' && character == ' ' ) )
        {
            queue_insert( &buffer, (void *)&character );
        }
    }

    prev_character = character; /* update previous character */
}

/* Timer interrupt service routine
 *
 * Processes characters read from the UART, and displays the character in morse
 * code.
 */
#pragma vector=TIMERA0_VECTOR
__interrupt void timer_isr()
{
    static uint8_t acc = 0;     /* used for couting time intervals */
    int8_t value = 0;           /* used for getting bit values */
    uint8_t * character = NULL;

    TACCR0 += timer;            /* set up timer for next cycle */

    switch( state.state )
    {
        /* Check buffer for a character
         */
        case S_CHECK_BUF:

            character = (uint8_t *)queue_peek( buffer );
            if( character != NULL )
            {
                /* display current character being displayed */
                U0TXBUF = *character;   

                /* initialize the state */
                state.character = morse_code_get( *character );
                state.position = 0;
                if( *character == ' ' )
                {
                    state.state = S_SPACE_WORDS;
                }
                else
                {
                    state.state = S_PRINT;
                }
            }

            break;

        /* Print a morse code character
         */
        case S_PRINT:

            /* check if we are finished */
            if( state.position >= state.character->length )
            {
                state.state = S_DONE;
                break;
            }
            
            leds_on( RED );
            P6OUT |= P3;  /* turn on P6.3 */

            /* get the current morse code value to display */
            value = morse_code_get_value( state.character, state.position );
            
            if( value == DOT )
            {
                state.position += 1;    /* advance character */
                state.state = S_SPACE;
            }
            else
            {
                if( acc < DASH_LENGTH - 1 )
                {
                    acc++;
                }
                else
                {
                    acc = 0;
                    state.position += 1; /* advance character */
                    state.state = S_SPACE;
                }
            }

            break;

        /* Enter waiting state
         */
        case S_SPACE:
            leds_off( RED );
            P6OUT &= ~P3;     /* turn off P6.3 */

            state.state = S_PRINT;

            break;

        /* We are finished priting
         */
        case S_DONE:
            leds_off( RED );
            P6OUT &= ~P3;     /* turn off P6.3 */

            queue_remove( &buffer );

            state.state = S_SPACE_LETTERS;

            break;

        /* Spacing between words
         */
        case S_SPACE_WORDS:

            if( acc < SPACE_LENGTH - 1 )
            {
                acc++;
            }
            else
            {
                queue_remove( &buffer );

                /* reset state */
                acc = 0;
                state.position = 0;
                state.state = S_CHECK_BUF;
            }

            break;

        /* Spacing between letters
         */
        case S_SPACE_LETTERS:

            if( acc < DASH_LENGTH - 1 )
            {
                acc++;
            }
            else
            {
                /* reset state */
                acc = 0;
                state.position = 0;
                state.state = S_CHECK_BUF;
            }

        default:
            break;
    }
}
