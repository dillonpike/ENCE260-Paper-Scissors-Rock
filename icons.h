/** @file   icons.h
    @author Bailey Lissington, Dillon Pike
    @date   08 Nov 2020
    @brief  Code containing bitmaps of various icons and code necessary to display the icons.
*/


#ifndef ICONS_H
#define ICONS_H

typedef uint8_t icon_t[5];

#define ROCK_ICON {0x3F, 0x21, 0x41, 0x42, 0x7E}
#define PAPER_ICON {0x3C, 0x42, 0x42, 0x44, 0x38}
#define SCISSORS_ICON {0x20, 0x57, 0x38, 0x57, 0x20}

/** displays bitmap image on LED matrix.
    @param bitmap 5x7 bitmap image to be displayed  */
void display_bitmap(icon_t bitmap);

#endif