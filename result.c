/** @file   result.c
    @author Bailey Lissington, Dillon Pike
    @date   11 Oct 2020
    @brief  Contains functions that calculate the result of a game,
            keep track of the number of wins, and display the number
            of wins.
*/


#include "tinygl.h"
#include "result.h"
#include "message.h"
#include "game_constants.h"


static uint8_t num_wins = 0;
static char wins_message[WINS_MESSAGE_LEN+1] = WINS_MESSAGE;


/** Checks whether the player won, lost, or tied, and displays it.
    @param choice char of the player's choice.
    @param opponent_choice char of the opponent's choice.
    @return defined number depending on result.  */
void calc_result (char choice, char opponent_choice)
{
    if (choice == opponent_choice) {
        display_message (TIE_MESSAGE);

    } else if (((choice == ROCK) && (opponent_choice == SCISSORS)) || ((choice == PAPER) && (opponent_choice == ROCK)) || ((choice == SCISSORS) && (opponent_choice == PAPER))) {
        display_message (WIN_MESSAGE);
        num_wins++;

    } else if (((choice == ROCK) && (opponent_choice == PAPER)) || ((choice == PAPER) && (opponent_choice == SCISSORS)) || ((choice == SCISSORS) && (opponent_choice == ROCK))) {
        display_message (LOSE_MESSAGE);
    }
}


/** Displays how many wins the player has gotten.  */
void display_results (void)
{
    /** Tens column of num_wins.  */
    wins_message[WINS_MESSAGE_LEN-2] = num_wins / 10 + ASCII_ZERO;
    /** Ones column.  */
    wins_message[WINS_MESSAGE_LEN-1] = num_wins % 10 + ASCII_ZERO;
    display_message (wins_message);
}
