#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

#define DISPLAY_TASK_RATE 250

static void display_task_init(void)
{
    tinygl_init(DISPLAY_TASK_RATE);
    tinygl_font_set(&font5x7_1);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
}

// Changes value of current_char depending on which way navswitch
// has been pushed.
int change_character (int current_char, char** characters)
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
    display_task_init();
    navswitch_init ();

    char* characters[3] = {"P", "S", "R"};
    int current_char = 0;
    while (1)
    {
        tinygl_update();
        navswitch_update();

        current_char = change_character (current_char, characters);
        tinygl_text (character);

    }
}
