/** @file   intro.c
    @author Bailey Lissington, Dillon Pike
    @date   11 Oct 2020
    @brief  Intro sequence for a game.
*/


#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"
#include "message.h"
#include "hardware.h"


/** Displays message until navswitch has been pushed.
    @param message message to display  */
void run_intro (char* message)
{
    display_message (message);
    navswitch_update ();
    while (!navswitch_pushed ())
    {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
    }
}
