#include "system.h"
#include "pio.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

#define DISPLAY_TASK_RATE 250

static void display_task_init(void)
{
    tinygl_init(DISPLAY_TASK_RATE);
    tinygl_font_set(&font5x7_1);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
}

int main (void)
{
    system_init ();
    display_task_init();

    while (1)
    {
        tinygl_text("R");
        tinygl_update();

    }
}
