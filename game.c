/** @file   game.c
    @author Bailey Lissington, Dillon Pike
    @date   11 Oct 2020
    @brief  Two player paper scissors rock game.
*/


#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "button.h"
#include "intro.h"
#include "choice.h"
#include "ledmat.h"
#include "icons.h"
#include "transmission.h"
#include "result.h"
#include "message.h"
#include "game_constants.h"
#include "hardware.h"


/** High pacer rate to stop flicker.  */
#define DISPLAY_RATE 2000
#define PACER_RATE 2000
#define MESSAGE_SPEED 20
#define INTRO_MESSAGE1 "Push to advance."
#define INTRO_MESSAGE2 "Navswitch up/down to choose."
#define WAIT_MESSAGE "Waiting..."


/** Waits until the user has pushed the navswitch.  */
static void wait_for_push (void)
{
    /** Updates navswitch initially in case the navswitch was pushed
        to trigger the previous event.  */
    navswitch_update();
    while (!navswitch_pushed ())
    {
        pacer_wait();
        tinygl_update();
        navswitch_update();
    }
}


/** Initialises the LED matrix, sets the font, text speed, and mode.  */
static void led_display_init (void)
{
    tinygl_init (DISPLAY_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_SPEED);
}


/** Initialises the components of the game.  */
static void game_init (void)
{
    system_init ();
    button_init();
    ledmat_init ();
    ir_uart_init ();
    led_display_init ();
    navswitch_init ();
    pacer_init (PACER_RATE);
    pio_config_set (LED1_PIO, PIO_OUTPUT_LOW);
}


int main (void)
{
    game_init ();
    char choice_array[CHOICE_NUM] = {PAPER, SCISSORS, ROCK};
    icon_t icons_array[CHOICE_NUM] = {PAPER_ICON, SCISSORS_ICON, ROCK_ICON};
    run_intro (INTRO_MESSAGE1);
    run_intro (INTRO_MESSAGE2);

    int choice_index = 0;
    char choice = '\0';
    char opponent_choice =  '\0';

    while (1)
    {
        pacer_wait ();
        navswitch_update ();
        reset_bitmap ();

        choice_index = choice_cycle (choice_array, CHOICE_NUM, icons_array);
        choice = choice_array[choice_index];

        led_on ();
        send_choice (choice);
        display_message (WAIT_MESSAGE);
        opponent_choice = receive_choice ();
        led_off ();

        /** Send a second time to ensure other player receives it.  */
        send_choice (choice);

        calc_result (choice, opponent_choice);
        wait_for_push ();
        display_results ();
        wait_for_push ();
    }
}
