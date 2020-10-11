/** @file   message.c
    @author Bailey Lissington, Dillon Pike
    @date   11 Oct 2020
    @brief  Function that displays a message to the led matrix.
*/


#include <string.h>
#include "tinygl.h"


/** Displays a message to the led matrix.
    @param message string to display.  */
void display_message (char* message)
{
    /** Scrolls through message if it has more than 1 character.  */
    if (strlen (message) > 1) {
        tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    } else {
        tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
    }
    tinygl_text (message);
}
