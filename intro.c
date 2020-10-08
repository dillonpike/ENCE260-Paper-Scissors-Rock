/** @file   intro.h
    @author Bailey Lissington, Dillon Pike
    @date   08 Nov 2020
    @brief  Code containing intro sequence for a game.
*/


#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"

/** Displays message until navswitch has been pushed.
    @param message message to display  */
void run_intro (char* message)
{
    tinygl_text (message);

    while (!navswitch_push_event_p (NAVSWITCH_PUSH))
    {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
    }
}
