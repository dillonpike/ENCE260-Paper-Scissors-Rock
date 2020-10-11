/** @file   icons.h
    @author Bailey Lissington, Dillon Pike
    @date   11 Oct 2020
    @brief  Code containing bitmaps of various icons and functions
            to display the icons.
*/


#ifndef ICONS_H
#define ICONS_H


#define ROCK_ICON {0x3C, 0x42, 0x42, 0x44, 0x38}
#define PAPER_ICON {0x3F, 0x21, 0x41, 0x42, 0x7E}
#define SCISSORS_ICON {0x20, 0x57, 0x38, 0x57, 0x20}
#define COLUMN_NUM 5


typedef uint8_t icon_t[COLUMN_NUM];


/** Updates current_bitmap array if function is passed a different
    bitmap.
    @param bitmap 5x7 bitmap image to be displayed  */
void display_bitmap (icon_t bitmap);


/** Turns off the previous column of the led matrix, then turns on the
    current column according to the bitmap, and advances to the next
    column.  */
void update_bitmap (void);


/** Resets current_bitmap to the default bitmap.  */
void reset_bitmap (void);


#endif
