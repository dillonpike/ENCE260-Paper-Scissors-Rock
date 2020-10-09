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
#include "transmission.h"
#include "result.h"

#define DISPLAY_TASK_RATE 250
#define PACER_RATE 250
#define MESSAGE_SPEED 20
#define INTRO_MESSAGE "Push to start"

#define PAPER 'P'
#define SCISSORS 'S'
#define ROCK 'R'
#define CHOICE_NUM 3


/** Waits until the user has pushed the navswitch.  */
static void wait_for_push (void)
{
    while (!navswitch_push_event_p(NAVSWITCH_PUSH))
    {
        pacer_wait();
        tinygl_update();
        navswitch_update();
    }
}


/** Initialises the LED matrix, sets the font, text speed, and mode.  */
static void display_task_init (void)
{
    tinygl_init (DISPLAY_TASK_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_SPEED);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}


/** Initialise the game.
    @param pacer_rate rate of pacer in Hz  */
static void game_init (int pacer_rate)
{
    ledmat_init ();
    ir_uart_init ();
    system_init ();
    display_task_init ();
    navswitch_init ();
    pacer_init (pacer_rate);
    pio_config_set (LED1_PIO, PIO_OUTPUT_LOW);
}


int main (void)
{
    game_init (PACER_RATE);
    char choices[CHOICE_NUM] = {PAPER, SCISSORS, ROCK};
    icon_t icons_array[CHOICE_NUM] = {PAPER_ICON, SCISSORS_ICON, ROCK_ICON};
    int choice_index = 0;
    run_intro (INTRO_MESSAGE);

    while (1)
    {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();

        choice_index = choice_cycle(choices, CHOICE_NUM, icons_array);

        pio_output_high(LED1_PIO);
        send_choice (choices, choice_index);
        char received_char = receive_choice ();
        pio_output_low(LED1_PIO);

        navswitch_update();
        ir_uart_putc(choices[choice_index]);

        int result = get_result(choices[choice_index], received_char);
        wait_for_push();
        pio_output_high(LED1_PIO);
        pacer_wait();
        print_results();
        navswitch_update();
        wait_for_push();
        pio_output_low(LED1_PIO);
        tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
    }
}
