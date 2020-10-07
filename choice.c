#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"


static void display_choice (char* choices, int choice)
{
    char buffer[2] = {0};
    buffer[0] = choices[choice];
    buffer[1] = '\0';
    tinygl_text (buffer);
}


/** Updates value of choice depending on which way navswitch
    has been pushed.  */
static int update_choice (int choice, int length)
{
    if (navswitch_push_event_p (NAVSWITCH_NORTH))
    {
        /** Increments choice and keeps it from 0 to 2. */
        choice = (choice + 1) % length;

    } else if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {

        /** Decrements current_char and keeps it from -2 to 2. */
        choice = (choice - 1) % length;

        /** Adds 3 to current_char if it's negative. */
        if (choice < 0) {
            choice += length;
        }
    }

    return choice;
}


/** Loops through checking to see if the player has updated their
    choice and displaying their current choice.  */
int choice_cycle (char* choices, int length)
{
    int current_choice = 0;

    while (!navswitch_push_event_p(NAVSWITCH_PUSH))
    {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();

        current_choice = update_choice (current_choice, length);

        display_choice(choices, current_choice);
    }
    return current_choice;
}
