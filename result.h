/** @file   result.h
    @author Bailey Lissington, Dillon Pike
    @date   11 Oct 2020
    @brief  Contains functions that calculate the result of a game,
            keep track of the number of wins, and display the number
            of wins.
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
    @param choice char of the player's choice.
    @param opponent_choice char of the opponent's choice.
    @return defined number depending on result.  */
void calc_result (char choice, char received_choice);


/** Displays how many wins the player has gotten.  */
void display_results (void);


#endif
