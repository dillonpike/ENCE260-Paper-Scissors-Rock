/** @file   icons.c
    @author Bailey Lissington, Dillon Pike
    @date   08 Nov 2020
    @brief  Code containing bitmaps of various icons and code necessary to display the icons.
*/

#include "ledmat.h"
#include "icons.h"

typedef uint8_t icon_t[5];

static icon_t current_bitmap = PAPER_ICON;
static int current_col = 0;

/** displays bitmap image on LED matrix.
    @param bitmap 5x7 bitmap image to be displayed  */
void display_bitmap(icon_t bitmap)
{
    current_col = 0;
    for(int i = 0; i < 5; i++) {
        current_bitmap[i] = bitmap[i];
    }


}

void update_bitmap(void)
{
    ledmat_display_column(current_bitmap[current_col], current_col);
    current_col++;
    current_col = current_col % 5;
}
