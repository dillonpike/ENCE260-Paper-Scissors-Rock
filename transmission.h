/** @file   icons.c
    @author Bailey Lissington, Dillon Pike
    @date   08 Nov 2020
    @brief  Code containing functions to send and receive paper, scissors, rock choices.
*/


#ifndef TRANSMISSION_H
#define TRANSMISSION_H


/** Sends choice and updates display.
    @param char that represents the player's choice.  */
void send_choice (char choice);


/** Waits until a valid choice has been received.
    @return character that the other player chose.  */
char receive_choice (void);


#endif

