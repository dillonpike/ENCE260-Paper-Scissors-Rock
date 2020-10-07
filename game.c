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
#define MESSAGE_SPEED 30
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
    char choices[3] = {'P', 'S', 'R'};
    int choice_index = 0;
    run_intro (INTRO_MESSAGE);

    while (1)
    {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();

        choice_index = choice_cycle(choices, 3);

        ir_uart_putc(choices[choice_index]);
        pio_output_high(LED1_PIO);
        tinygl_text("sending...");
        while (ir_uart_read_ready_p() == 0) {
            pacer_wait();
            tinygl_update();
        }
        pio_output_low(LED1_PIO);
        char received_char = ir_uart_getc();
        if (received_char == choices[choice_index]) {
            tinygl_text("tie");
        }

    }
}
