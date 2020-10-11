/** @file   choice.h
    @author Bailey Lissington, Dillon Pike
    @date   11 Oct 2020
    @brief  Functions that allow the player to choose from an array
            and display the choices.
*/


#ifndef CHOOSE_H
#define CHOOSE_H


#include "icons.h"


/** Loops through checking to see if the player has updated their
    choice and displaying their current choice.
    @param  choice_array chars for the player to choose.
    @param  length of choice_array.
    @param  icons_array icons representing chars from choice_array.
    @return index of the item from choice_array that was chosen.  */
int choice_cycle (char* choice_array, int length, icon_t* icon_array);


#endif
