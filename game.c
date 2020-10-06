#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

#define DISPLAY_TASK_RATE 250
#define PACER_RATE 500
#define MESSAGE_SPEED 25

static void display_task_init (void)
{
    tinygl_init (DISPLAY_TASK_RATE);
    tinygl_font_set (&font5x7_1);
}

static void display_message (char* message)
{
    tinygl_text_speed_set (MESSAGE_SPEED);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text (message);
}

static void run_start_screen (void)
{
    display_message("Push to Start");
    // Displays message until navswitch has been pushed
    while (!navswitch_push_event_p (NAVSWITCH_PUSH))
    {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
    }

}

// Changes value of current_char depending on which way navswitch
// has been pushed.
int change_character (int current_char)
{
    if (navswitch_push_event_p (NAVSWITCH_NORTH))
    {
        // Increments current_char and keeps it from 0 to 2
        current_char = (current_char + 1) % 3;

    } else if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {

        // Decrements current_char and keeps it from -2 to 2
        current_char = (current_char - 1) % 3;

        // Adds 3 to current_char if it's negative
        if (current_char < 0) {
            current_char += 3;
        }
    }

    return current_char;
}

int main (void)
{
    system_init ();
    display_task_init ();
    navswitch_init ();
    pacer_init (PACER_RATE);

    char* characters[3] = {"P", "S", "R"};
    int current_char = 0;
    run_start_screen ();
    //tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);

    while (1)
    {
        tinygl_update ();
        navswitch_update ();

        current_char = change_character (current_char);
        tinygl_text (characters[current_char]);
        pacer_wait ();
    }
}
