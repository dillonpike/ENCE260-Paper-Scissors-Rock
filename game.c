#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "intro.h"
#include "choice.h"

#define DISPLAY_TASK_RATE 250
#define PACER_RATE 250
#define MESSAGE_SPEED 15
#define INTRO_MESSAGE "Push to start"

static void display_task_init (void)
{
    tinygl_init (DISPLAY_TASK_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_SPEED);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}

static void initialise_game(int pacer_rate)
{
    system_init();
    display_task_init();
    navswitch_init();
    pacer_init(pacer_rate);
    pio_config_set(LED1_PIO, PIO_OUTPUT_LOW);
}

int main (void)
{
    initialise_game(PACER_RATE);
    char* choices[3] = {"P", "S", "R"};

    run_intro (INTRO_MESSAGE);
    tinygl_text_speed_set (75);
    
    
    
    //choice_index++;
    
    while (1)
    {
        //pio_output_low(LED1_PIO);
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
        int choice_index = choice_cycle(choices, 3);
        pio_output_high(LED1_PIO);
        ir_uart_putc(choices[choice_index]);

    }
}
