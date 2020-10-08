/** @file   icons.c
    @author Bailey Lissington, Dillon Pike
    @date   08 Nov 2020
    @brief  Code containing functions to send and receive paper, scissors, rock choices.
*/


#include "ir_uart.h"
#include "tinygl.h"
#include "pacer.h"


/** Empties the IR receiver buffer.  */
static void empty_buffer (void)
{
    while(ir_uart_read_ready_p ())
    {
        ir_uart_getc ();
    }
}


/** Sends choice and updates display.
    @param array of chars that represent the choices.
    @param array index of the player's choice.  */
void send_choice (char* choices, int choice_index)
{
    empty_buffer ();
    ir_uart_putc(choices[choice_index]);
    tinygl_text("Sending...");
}


/** Waits until a valid choice has been received.
    @return character that the other player chose.  */
char receive_choice (void)
{
    char received_char = '\0';
    while ((received_char != 'R') && (received_char != 'P') && (received_char != 'S'))
    {
        pacer_wait ();
        tinygl_update ();

        if(ir_uart_read_ready_p ())
        {
            received_char = ir_uart_getc ();
        }

    }
    return received_char;
}
