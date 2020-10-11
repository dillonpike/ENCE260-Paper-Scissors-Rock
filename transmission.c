/** @file   transmission.c
    @author Bailey Lissington, Dillon Pike
    @date   11 Oct 2020
    @brief  Functions to send and receive paper, scissors, rock choices.
*/


#include "ir_uart.h"
#include "tinygl.h"
#include "pacer.h"
#include "game_constants.h"


/** Empties the IR receiver buffer.  */
static void empty_buffer (void)
{
    while(ir_uart_read_ready_p ())
    {
        ir_uart_getc ();
    }
}


/** Sends choice and updates display.
    @param choice char that represents the player's choice.  */
void send_choice (char choice)
{
    empty_buffer ();
    ir_uart_putc(choice);
}


/** Waits until a valid choice has been received.
    @return character that the other player chose.  */
char receive_choice (void)
{
    char received_char = '\0';
    while ((received_char != ROCK) && (received_char != PAPER) && (received_char != SCISSORS))
    {
        pacer_wait ();
        tinygl_update ();

        if(ir_uart_read_ready_p ()) {
            received_char = ir_uart_getc ();
        }
    }
    return received_char;
}
