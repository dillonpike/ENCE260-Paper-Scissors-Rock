/** @file   icons.c
    @author Bailey Lissington, Dillon Pike
    @date   08 Nov 2020
    @brief  Checks if the player won, lost, or tied.
*/


#ifndef RESULT_H
#define RESULT_H


#define WIN 1
#define LOSE 0
#define TIE -1


/** Checks whether the player won, lost, or tied, and displays it.
    @param char of the player's choice.
    @param char of the opponent's choice.
    @return defined number depending on result.  */
int get_result(char choice, char received_choice);

void print_results(void);

#endif
