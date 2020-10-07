#ifndef CHOOSE_H
#define CHOOSE_H

/** Updates value of choice depending on which way navswitch
    has been pushed.  */
int update_choice (int choice, int length);

/** Loops through checking to see if the player has updated their
    choice and displaying their current choice.  */
int choice_cycle (char* choices, int length);

#endif
