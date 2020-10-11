/** @file   icons.c
    @author Bailey Lissington, Dillon Pike
    @date   08 Nov 2020
    @brief  Code containing bitmaps of various icons and code necessary to display the icons.
*/

#include "ledmat.h"
#include "icons.h"

typedef uint8_t icon_t[COLUMN_NUM];

icon_t paper_icon = PAPER_ICON;
static icon_t current_bitmap = PAPER_ICON;
static int current_col = 0;


/** Updates current_bitmap array if function is passed a different
    bitmap.
    @param bitmap 5x7 bitmap image to be displayed  */
void display_bitmap(icon_t bitmap)
{
    if (bitmap != current_bitmap) {
        for(int i = 0; i < COLUMN_NUM; i++) {
            current_bitmap[i] = bitmap[i];
        }
    }
}

/** Turns off the previous column of the led matrix, then turns on the
    current column according to the bitmap, and advances to the next
    column.  */
void update_bitmap(void)
{
    ledmat_display_column(current_bitmap[current_col], current_col);
    current_col++;
    current_col = current_col % COLUMN_NUM;
}


void reset_bitmap(void) {
    for (int i = 0; i < COLUMN_NUM; i++) {
        current_bitmap[i] = paper_icon[i];
    }
}
