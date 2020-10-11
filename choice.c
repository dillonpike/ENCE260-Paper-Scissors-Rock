/** @file   choice.c
    @author Bailey Lissington, Dillon Pike
    @date   11 Oct 2020
    @brief  Functions that allow the player to choose from an array
            and display the choices.
*/


#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"
#include "icons.h"
#include "button.h"
#include "message.h"
#include "hardware.h"


static int button_toggle = 0;


/** Sets the led matrix to display a character from choice_array if
    button_toggle is false, otherwise an icon from icon_array.
    @param choice_index index of which item to get from the arrays.
    @param choice_array chars for the player to choose.
    @param icon_array icons representing chars from choice_array.  */
static void display_choice (int choice_index, char* choice_array, icon_t* icon_array)
{
    if (button_toggle) {
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
    @param  choice_index integer that will be updated.
    @param  length of choice_array from choice_cycle.
    @return choice_index incremented, decremented, or not changed.  */
static int update_choice (int choice_index, int length)
{
    if (navswitch_pushed_up ()) {
        /** Increments choice and keeps it from 0 to length. */
        choice_index = (choice_index + 1) % length;

    } else if (navswitch_pushed_down ()) {
        /** Decrements current_char and keeps it from -2 to . */
        choice_index = (choice_index - 1) % length;

        /** Gets the positive remainder if the previous modulo
            operation gave a negative remainder.  */
        if (choice_index < 0) {
            choice_index += length;
        }
    }
    return choice_index;
}


/** Loops through checking to see if the player has updated their
    choice and displaying their current choice.
    @param  choice_array chars for the player to choose.
    @param  length of choice_array.
    @param  icons_array icons representing chars from choice_array.
    @return index of the item from choice_array that was chosen.  */
int choice_cycle (char* choice_array, int length, icon_t* icon_array)
{
    int choice_index = 0;
    while (!navswitch_pushed ())
    {
        pacer_wait ();
        navswitch_update ();
        button_update ();

        if (button_toggle) {
            update_bitmap ();
            if (button_pushed ()) {
                button_toggle = 0;
            }
        } else {
            tinygl_update ();
            if (button_pushed ()) {
                button_toggle = 1;
            }
        }
        choice_index = update_choice (choice_index, length);
        display_choice (choice_index, choice_array, icon_array);
    }
    return choice_index;
}
