/** @file   hardware.c
    @author Bailey Lissington, Dillon Pike
    @date   11 Oct 2020
    @brief  Functions for using the hardware of the UCFKv4.
*/


#include "navswitch.h"
#include "button.h"
#include "pio.h"


/** Return true if button is being pushed.
    @return 1 if button is pushed, otherwise 0.  */
int button_pushed (void)
{
    return button_push_event_p (BUTTON1);
}


/** Return true if navswitch is being pushed.
    @return 1 if navswitch is pushed, otherwise 0.  */
int navswitch_pushed (void)
{
    return navswitch_push_event_p (NAVSWITCH_PUSH);
}


/** Return true if navswitch is being pushed up.
    @return 1 if navswitch is pushed up, otherwise 0.  */
int navswitch_pushed_up (void)
{
    return navswitch_push_event_p (NAVSWITCH_NORTH);
}


/** Return true if navswitch is being pushed down.
    @return 1 if navswitch is pushed down, otherwise 0.  */
int navswitch_pushed_down (void)
{
    return navswitch_push_event_p (NAVSWITCH_SOUTH);
}


/** Turns led on.  */
void led_on (void)
{
    pio_output_high(LED1_PIO);
}


/** Turns led off.  */
void led_off (void)
{
    pio_output_low(LED1_PIO);
}
