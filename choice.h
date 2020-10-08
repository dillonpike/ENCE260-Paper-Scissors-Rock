/** @file   choice.h
    @author Bailey Lissington, Dillon Pike
    @date   08 Nov 2020
    @brief  Code corresponding to the choosing of rock, paper, scissors objects.
*/


#ifndef CHOOSE_H
#define CHOOSE_H

#include "icons.h"

/** Updates value of choice depending on which way navswitch
    has been pushed.  */
int update_choice (int choice, int length);

/** Loops through checking to see if the player has updated their
    choice and displaying their current choice.  */
int choice_cycle (char* choices, int length, icon_t icon_array[]);

#endif
