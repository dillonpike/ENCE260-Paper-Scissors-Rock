/** @file   game.c
    @author Bailey Lissington, Dillon Pike
    @date   08 Nov 2020
    @brief  Code for a multiplayer Paper, Scissors, Rock game
*/

#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "intro.h"
#include "choice.h"
#include "ledmat.h"
#include "icons.h"
#include "button.h"

#define DISPLAY_TASK_RATE 250
#define PACER_RATE 250
#define MESSAGE_SPEED 20
#define INTRO_MESSAGE "Push to start"




static void display_task_init (void)
{
    tinygl_init (DISPLAY_TASK_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_SPEED);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}

/** Initialise the game.
    @param pacer_rate rate of pacer in Hz  */
static void initialise_game(int pacer_rate)
{
    button_init();
    ledmat_init();
    ir_uart_init();
    system_init();
    display_task_init();
    navswitch_init();
    pacer_init(pacer_rate);
    pio_config_set(LED1_PIO, PIO_OUTPUT_LOW);
}

int main (void)
{
    initialise_game(PACER_RATE);
    //display_bitmap(paper);
    char choices[3] = {'P', 'S', 'R'};
    icon_t icons_array[3] = {PAPER_ICON, SCISSORS_ICON, ROCK_ICON};
    int choice_index = 0;
    run_intro (INTRO_MESSAGE);

    while (1)
    {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();

        choice_index = choice_cycle(choices, 3, icons_array);

        ir_uart_putc(choices[choice_index]);
        while(ir_uart_read_ready_p()) { //reads echoed bytes
            ir_uart_getc();
        }
        pio_output_high(LED1_PIO);
        tinygl_text("sending...");
        char current_char = '\0';
        while ((current_char != 'R') && (current_char != 'P') && (current_char != 'S'))
        {
            pacer_wait();
            tinygl_update();
            if(ir_uart_read_ready_p()) {
                current_char = ir_uart_getc();
            }
            
        }
        navswitch_update();
        pio_output_low(LED1_PIO);
        ir_uart_putc(choices[choice_index]);
        if (current_char == choices[choice_index]) {
            tinygl_text("tie");
            
        } else if (((choices[choice_index] == 'R') && (current_char == 'S')) || ((choices[choice_index] == 'P') && (current_char == 'R')) || ((choices[choice_index] == 'S') && (current_char == 'P'))) {
            tinygl_text("you win");
        } else if (((choices[choice_index] == 'R') && (current_char == 'P')) || ((choices[choice_index] == 'P') && (current_char == 'S')) || ((choices[choice_index] == 'S') && (current_char == 'D'))) {
            tinygl_text("you lose");
        }
            while (!navswitch_push_event_p(NAVSWITCH_PUSH))
            {
                pacer_wait();
                tinygl_update();
                navswitch_update();
            }
    }
}
