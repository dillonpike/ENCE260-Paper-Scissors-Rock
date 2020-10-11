/** @file   result.h
    @author Bailey Lissington, Dillon Pike
    @date   08 Nov 2020
    @brief  Checks if the player won, lost, or tied.
*/


#ifndef RESULT_H
#define RESULT_H


#define WIN 1
#define LOSE 0
#define TIE -1
#define ASCII_ZERO 48
#define WINS_MESSAGE "Wins: 00"
#define WINS_MESSAGE_LEN 8
#define WIN_MESSAGE "W"
#define TIE_MESSAGE "T"
#define LOSE_MESSAGE "L"


/** Checks whether the player won, lost, or tied, and displays it.
    @param char of the player's choice.
    @param char of the opponent's choice.
    @return defined number depending on result.  */
void calc_result(char choice, char received_choice);


/** Displays how many wins the player has gotten.  */
void display_results(void);


#endif
