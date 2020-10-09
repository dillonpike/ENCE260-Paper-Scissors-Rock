/** @file   choice.c
    @author Bailey Lissington, Dillon Pike
    @date   08 Nov 2020
    @brief  Code corresponding to the choosing of rock, paper, scissors objects.
*/


#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"
#include "icons.h"
#include "button.h"

static void display_choice(char *choices, int choice, icon_t icon_array[])
{
    display_bitmap(icon_array[choice]);
    //choices = choices;
    // char buffer[2] = {0};
    // buffer[0] = choices[choice];
    // buffer[1] = '\0';
    // tinygl_text (buffer);

}


/** Updates value of choice depending on which way navswitch
    has been pushed.  */
static int update_choice (int choice, int length, char* choices, icon_t icon_array[])
{
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        /** Increments choice and keeps it from 0 to 2. */
        choice = (choice + 1) % length;
        display_choice(choices, choice, icon_array);

    } else if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        /** Decrements current_char and keeps it from -2 to 2. */
        choice = (choice - 1) % length;

        /** Adds 3 to current_char if it's negative. */
        if (choice < 0) {
            choice += length;
        }
        display_choice(choices, choice, icon_array);
    }

    return choice;
}


/** Loops through checking to see if the player has updated their
    choice and displaying their current choice.  */
int choice_cycle (char* choices, int length, icon_t icon_array[])
{
    int current_choice = 0;

    while (!navswitch_push_event_p(NAVSWITCH_PUSH))
    {
        pacer_wait ();
        // tinygl_update ();
        navswitch_update ();
        update_bitmap();
        current_choice = update_choice (current_choice, length, choices, icon_array);

    }
    return current_choice;
}
