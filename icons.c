#include "ledmat.h"

#define ROCK_ICON {0x3F, 0x21, 0x41, 0x42, 0x7E}
#define PAPER_ICON {0x3C, 0x42, 0x42, 0x44, 0x38}
#define SCISSORS_ICON {0x20, 0x57, 0x38, 0x57, 0x20}

typedef uint8_t icon_t[5];

void display_bitmap(icon_t bitmap)
{
    for (int i = 0; i < 5; i++)
    {
        ledmat_display_column(bitmap[i], i);
    }
}

