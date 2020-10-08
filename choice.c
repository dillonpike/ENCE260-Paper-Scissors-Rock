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

static int button_pressed = 0;

static void display_choice(char *choices, int choice, icon_t icon_array[])
{
    if (button_pressed) {
        char buffer[2] = {0};
        buffer[0] = choices[choice];
        buffer[1] = '\0';
        tinygl_text(buffer);
    }
    display_bitmap(icon_array[choice]);
    //choices = choices;
    // 
    
}


/** Updates value of choice depending on which way navswitch
    has been pushed.  */
static int update_choice (int choice, int length, char* choices, icon_t icon_array[])
{
    if (navswitch_push_event_p (NAVSWITCH_NORTH))
    {
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
        //update_bitmap();
        button_update();
        if(button_push_event_p(BUTTON1)) {
            if(button_pressed) {
                display_choice(choices, current_choice, icon_array);
                button_pressed = 0;
            } else {
                char buffer[2] = {0};
                buffer[0] = choices[current_choice];
                buffer[1] = '\0';
                tinygl_text(buffer);
                button_pressed = 1;
            }
            

        }
        if (button_pressed) {tinygl_update();}
        else {update_bitmap();}
        current_choice = update_choice (current_choice, length, choices, icon_array);
    }
    return current_choice;
}
