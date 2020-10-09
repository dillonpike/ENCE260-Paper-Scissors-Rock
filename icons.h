/** @file   icons.h
    @author Bailey Lissington, Dillon Pike
    @date   08 Nov 2020
    @brief  Code containing bitmaps of various icons and code necessary to display the icons.
*/


#ifndef ICONS_H
#define ICONS_H

typedef uint8_t icon_t[5];

#define ROCK_ICON  {0x3C, 0x42, 0x42, 0x44, 0x38}
#define PAPER_ICON {0x3F, 0x21, 0x41, 0x42, 0x7E}
#define SCISSORS_ICON {0x20, 0x57, 0x38, 0x57, 0x20}
#define TROPHY_ICON {0x47, 0x59, 0x61, 0x59, 0x47}
#define TIE_ICON {0x00, 0x3D, 0x43, 0x3D, 0x00}
#define LOSE_ICON {0x40, 0x26, 0x20, 0x26, 0x40}

/** displays bitmap image on LED matrix.
    @param bitmap 5x7 bitmap image to be displayed  */
void display_bitmap(icon_t bitmap);

void update_bitmap(void);

#endif