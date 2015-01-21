/* author: Julian Martinez del Campo
 * class : CMPT 464
 * date  : October 17, 2014
 *
 * Provides functions for configuring and controlling the UART.
 */
#ifndef _UART_H_
#define _UART_H_

typedef enum {
    UART_2400
} uart_speed_t;

/* Configure the UART to a specified speed 
 */
void uart_configure( uart_speed_t speed );

#endif /* _UART_H_ */
