#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"

/** Displays message until navswitch has been pushed.  */
void run_intro (char* message)
{
    tinygl_text (message);

    while (!navswitch_push_event_p (NAVSWITCH_PUSH))
    {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
    }

    tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
}
