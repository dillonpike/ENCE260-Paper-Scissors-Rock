/** @file   hardware.h
    @author Bailey Lissington, Dillon Pike
    @date   11 Oct 2020
    @brief  Functions for using the hardware of the UCFKv4.
*/


#ifndef HARDWARE_H
#define HARDWARE_H


/** Return true if button is being pushed.
    @return 1 if button is pushed, otherwise 0.  */
int button_pushed (void);


/** Return true if navswitch is being pushed.
    @return 1 if navswitch is pushed, otherwise 0.  */
int navswitch_pushed (void);


/** Return true if navswitch is being pushed up.
    @return 1 if navswitch is pushed up, otherwise 0.  */
int navswitch_pushed_up (void);


/** Return true if navswitch is being pushed down.
    @return 1 if navswitch is pushed down, otherwise 0.  */
int navswitch_pushed_down (void);


/** Turns led on.  */
void led_on (void);


/** Turns led off.  */
void led_off (void);


#endif

