#include "bitmaps.h"

int   current_wpm = 0;

/* timers */
uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;

/* current frame */
uint8_t current_frame = 0;


static void render_space(void) {
    char render_row[128];
    int i;
    oled_set_cursor(0,0);
    for(i=0; i<current_wpm/4; i++) {
        render_row[i] = pgm_read_byte(space_row_1+i+state);
    };
    for(i=current_wpm/4; i<128; i++) {
        render_row[i] = (pgm_read_byte(space_row_1+i+state)&pgm_read_byte(mask_row_1+i-current_wpm/4)) | pgm_read_byte(ship_row_1+i-current_wpm/4);
    };

    oled_write_raw(render_row, 128);
    // oled_write_raw_P(space_row_1, 128);
    oled_set_cursor(0,1);
    for(i=0; i<current_wpm/4; i++) {
        render_row[i] = pgm_read_byte(space_row_2+i+state);
    };
    for(i=current_wpm/4; i<128; i++) {
        render_row[i] = (pgm_read_byte(space_row_2+i+state)&pgm_read_byte(mask_row_2+i-current_wpm/4)) | pgm_read_byte(ship_row_2+i-current_wpm/4);
    };
    oled_write_raw(render_row, 128);
    oled_set_cursor(0,2);
    for(i=0; i<current_wpm/4; i++) {
        render_row[i] = pgm_read_byte(space_row_3+i+state);
    };
    for(i=current_wpm/4; i<128; i++) {
        render_row[i] = (pgm_read_byte(space_row_3+i+state)&pgm_read_byte(mask_row_3+i-current_wpm/4)) | pgm_read_byte(ship_row_3+i-current_wpm/4);
    };

    oled_write_raw(render_row, 128);
    oled_set_cursor(0,3);
    for(i=0; i<current_wpm/4; i++) {
        render_row[i] = pgm_read_byte(space_row_4+i+state);
    };
    for(i=current_wpm/4; i<128; i++) {
        render_row[i] = (pgm_read_byte(space_row_4+i+state)&pgm_read_byte(mask_row_4+i-current_wpm/4)) | pgm_read_byte(ship_row_4+i-current_wpm/4);
    };

    oled_write_raw(render_row, 128);

    state = (state + 1 + (current_wpm/15)) % (128*2);

    if (current_wpm > 0) {
        oled_on();
        anim_sleep = timer_read32();
    } else if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
        /* clear */
        oled_set_cursor(0, 0);
        oled_write("                                                                                                    ", false);
        oled_off();
    }
}
