/** @file   choice.c
    @author Bailey Lissington, Dillon Pike
    @date   08 Oct 2020
    @brief  Code corresponding to the choosing of rock, paper, scissors objects.
*/


#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"
#include "icons.h"
#include "button.h"
#include "message.h"


static int button_pressed = 0;


static void display_choice (int choice_index, char* choice_array, icon_t icon_array[])
{
    if (button_pressed) {
        display_bitmap(icon_array[choice_index]);
    } else {
        char buffer[2] = {0};
        buffer[0] = choice_array[choice_index];
        buffer[1] = '\0';
        display_message (buffer);
    }
}


/** Updates value of choice depending on which way navswitch
    has been pushed.
    @param
    @param
    @param .*/
static int update_choice (int choice_index, int length, char* choice_array, icon_t icon_array[])
{
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        /** Increments choice and keeps it from 0 to 2. */
        choice_index = (choice_index + 1) % length;
        display_choice(choice_index, choice_array, icon_array);

    } else if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        /** Decrements current_char and keeps it from -2 to 2. */
        choice_index = (choice_index - 1) % length;

        /** Gets the positive remainder if the previous modulo
            operation gave a negative remainder.  */
        if (choice_index < 0) {
            choice_index += length;
        }
        display_choice(choice_index, choice_array, icon_array);
    }
    return choice_index;
}


/** Loops through checking to see if the player has updated their
    choice and displaying their current choice.  */
int choice_cycle (char* choice_array, int length, icon_t icon_array[])
{
    int choice_index = 0;
    display_choice(choice_index, choice_array, icon_array);

    while (!navswitch_push_event_p(NAVSWITCH_PUSH))
    {
        pacer_wait ();
        navswitch_update ();
        button_update ();

        if (button_pressed) {
            update_bitmap ();
            if (button_push_event_p (BUTTON1)) {
                button_pressed = 0;
            }
        } else {
            tinygl_update ();
            if (button_push_event_p (BUTTON1)) {
                button_pressed = 1;
            }
        }
        choice_index = update_choice (choice_index, length, choice_array, icon_array);
    }
    return choice_index;
}
