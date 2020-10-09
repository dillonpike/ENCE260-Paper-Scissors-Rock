/** @file   icons.c
    @author Bailey Lissington, Dillon Pike
    @date   08 Nov 2020
    @brief  Checks if the player won, lost, or tied.
*/


#include "tinygl.h"
#include "result.h"

static uint8_t num_wins = 0;

/** Checks whether the player won, lost, or tied, and displays it.
    @param char of the player's choice.
    @param char of the opponent's choice.
    @return defined number depending on result.  */
int get_result(char choice, char opponent_choice)
{
    int result = 0;
    if (choice == opponent_choice) {
        tinygl_text("T");
        result = TIE;

    } else if (((choice == 'R') && (opponent_choice == 'S')) || ((choice == 'P') && (opponent_choice == 'R')) || ((choice == 'S') && (opponent_choice == 'P'))) {
        tinygl_text("W");
        result = WIN;
        num_wins++;

    } else if (((choice == 'R') && (opponent_choice == 'P')) || ((choice == 'P') && (opponent_choice == 'S')) || ((choice == 'S') && (opponent_choice == 'R'))) {
        tinygl_text("L");
        result = LOSE;
    }
    return result;
}

uint8_t get_wins() {
    return num_wins;
}
