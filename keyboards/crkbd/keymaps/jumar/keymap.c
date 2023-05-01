/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "jumar.h"
#include "transactions.h"

#ifdef VIRTSER_ENABLE
#include "virtser.h"
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_0_QWERTY] = LAYOUT_wrapper(
        ROW4_LEFT_BASE, ROW4_RIGHT_BASE,
        ROW3_LEFT_BASE, ROW3_RIGHT_BASE,
        ROW2_LEFT_BASE, ROW2_RIGHT_BASE,
        ROW1_LEFT_BASE, ROW1_RIGHT_BASE
    ),
	[_1_SYMBOLS_NUMPAD] = LAYOUT_wrapper(
        ROW4_LEFT_SYMB_NUMPAD, ROW4_RIGHT_SYMB_NUMPAD,
        ROW3_LEFT_SYMB_NUMPAD, ROW3_RIGHT_SYMB_NUMPAD,
        ROW2_LEFT_SYMB_NUMPAD, ROW2_RIGHT_SYMB_NUMPAD,
        ROW1_LEFT_SYMB_NUMPAD, ROW1_RIGHT_SYMB_NUMPAD
    ),
	[_2_MOUSE_MEDIA] = LAYOUT_wrapper(
        ROW4_LEFT_MOUSE_MEDIA, ROW4_RIGHT_MOUSE_MEDIA,
        ROW3_LEFT_MOUSE_MEDIA, ROW3_RIGHT_MOUSE_MEDIA,
        ROW2_LEFT_MOUSE_MEDIA, ROW2_RIGHT_MOUSE_MEDIA,
        ROW1_LEFT_MOUSE_MEDIA, ROW1_RIGHT_MOUSE_MEDIA
    ),
	[_3_NAV] = LAYOUT_wrapper(
        ROW4_LEFT_NAV_CPY_PASTA, ROW4_RIGHT_NAV_CPY_PASTA,
        ROW3_LEFT_NAV_CPY_PASTA, ROW3_RIGHT_NAV_CPY_PASTA,
        ROW2_LEFT_NAV_CPY_PASTA, ROW2_RIGHT_NAV_CPY_PASTA,
        ROW1_LEFT_NAV_CPY_PASTA, ROW1_RIGHT_NAV_CPY_PASTA
    ),
    [_4_GAM] = LAYOUT_wrapper(
        ROW4_LEFT_GAMING, ROW4_RIGHT_GAMING,
        ROW3_LEFT_GAMING, ROW3_RIGHT_GAMING,
        ROW2_LEFT_GAMING, ROW2_RIGHT_GAMING,
        ROW1_LEFT_GAMING, ROW1_RIGHT_GAMING
    ),
   [_5_RGB] = LAYOUT_wrapper(
        ROW4_LEFT_RGB, ROW4_RIGHT_RGB,
        ROW3_LEFT_RGB, ROW3_RIGHT_RGB,
        ROW2_LEFT_RGB, ROW2_RIGHT_RGB,
        ROW1_LEFT_RGB, ROW1_RIGHT_RGB
    ),
   [_6_FN] = LAYOUT_wrapper(
        ROW4_LEFT_FN, ROW4_RIGHT_FN,
        ROW3_LEFT_FN, ROW3_RIGHT_FN,
        ROW2_LEFT_FN, ROW2_RIGHT_FN,
        ROW1_LEFT_FN, ROW1_RIGHT_FN
    ),
};

#ifdef OLED_ENABLE
//#define OLED_SUGAR

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    bool rotate_both = false;
    #ifdef OLED_SUGAR
    rotate_both = true;
    #endif
    if (is_keyboard_master() || rotate_both) {
        return OLED_ROTATION_270;
    } else {
        return rotation;
    }
}

void render_crkbd_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

#define KEYLOG_LEN 5
char     keylog_str[KEYLOG_LEN] = {};
uint8_t  keylogs_str_idx        = 0;
uint16_t log_timer              = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }

    for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) {
        keylog_str[i] = keylog_str[i - 1];
    }
    if (keycode < 60) {
        keylog_str[0] = code_to_name[keycode];
    }
    keylog_str[KEYLOG_LEN - 1] = 0;

    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        add_keylog(0);
    }
}

void render_keylogger_status(void) {
    oled_write_P(PSTR("KLogr"), false);
    oled_write(keylog_str, false);
}

void render_default_layer_state(void) {
    oled_write_P(PSTR("Lyout"), false);
    switch (get_highest_layer(default_layer_state)) {
        case _0_QWERTY:
            oled_write_P(PSTR(" QRTY"), false);
            break;
        case _1_SYMBOLS_NUMPAD:
            oled_write_P(PSTR("SymNum"), false);
            break;
    }
}

void render_layer_state(void) {
    uint8_t layer = biton32(layer_state);
    oled_write_P(PSTR("Layr:\n"), false);
    switch (layer)
    {
        case _0_QWERTY:
            oled_write_P(PSTR("QRTY\n"), true);
        break;
        case _1_SYMBOLS_NUMPAD:
            oled_write_P(PSTR("SyNum"), true);
        break;
        case _2_MOUSE_MEDIA:
            oled_write_P(PSTR("Media"), true);
        break;
        case _3_NAV:
            oled_write_P(PSTR("Nav\n"), true);
        break;
        case _4_GAM:
            oled_write_P(PSTR("Game\n"), true);
        break;
        case _5_RGB:
            oled_write_P(PSTR("RGB\n"), true);
        break;
        case _6_FN:
            oled_write_P(PSTR("FN\n"), true);
        break;
        default:
            oled_write_P(PSTR("???\n"), true);
    }
    oled_write_P(PSTR("\n"), true);
}

void render_keylock_status(uint8_t led_usb_state) {
    oled_write_P(PSTR("\nLock:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR("C"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write_ln_P(PSTR("S\n"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("\nMods:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G\n"), (modifiers & MOD_MASK_GUI));
}

void render_bootmagic_status(void) {
    /* Show Ctrl-Gui Swap options */
    /*static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };*/
    oled_write_P(PSTR("BTMGK"), false);
    /*oled_write_P(PSTR(" "), false);
    oled_write_P(logo[0][0], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][0], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[0][1], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][1], keymap_config.swap_lctl_lgui);*/
    oled_write_P(PSTR(" NKRO"), keymap_config.nkro);
}

void render_status_main(void) {
    /* Show Keyboard Layout  */
    //render_default_layer_state();
    render_layer_state();
    render_keylock_status(host_keyboard_leds());
    render_mod_status(get_mods());
    //render_bootmagic_status();

    render_keylogger_status();
}

//
// ------------------------ OLED sugar -------------------------
//

uint16_t keyCntr = 0;
#define OLED_SUGAR_HEIGHT 128
#define OLED_SUGAR_WIDTH  32
bool pixelInvert = false;

void setPixel(char * pixels, uint8_t h, uint8_t w, bool pix) {
//    oled_write_pixel(w, h, pix);
    uint16_t byteIdx = w + (h/8)*OLED_SUGAR_WIDTH;
    int8_t byteMask = 1<<(h%8);
    if(pixelInvert) pix = !pix;
    if(pix) {
        pixels[byteIdx] |= byteMask;
    } else {
        pixels[byteIdx] &= ~byteMask;
    }
}

bool getPixel(char * pixels, uint8_t h, uint8_t w) {
    uint16_t byteIdx = w + (h/8)*OLED_SUGAR_WIDTH;
    int8_t byteMask = 1<<(h%8);
    bool pix =  (pixels[byteIdx] & byteMask) != 0;
    if(pixelInvert) pix = !pix;
    return pix;
}

uint32_t rand_basic(void) {
    static uint32_t seed = 0;
    seed = 1664525*seed + 1013904223;
    return seed;
}

#define OLED_SUGAR_WITH_DOWN 1

#define OLED_SUGAR_PIXELS (OLED_SUGAR_HEIGHT*OLED_SUGAR_WIDTH)
#define OLED_SUGAR_BYTES (OLED_SUGAR_PIXELS/8)
typedef signed char lineIdx_t;
lineIdx_t* activeSugar = NULL;

char* pixels = NULL;

void oled_sugar(void) {
    //return;

    if (activeSugar == NULL) {
        activeSugar = malloc(OLED_SUGAR_HEIGHT);
        if (activeSugar != NULL) {
            memset( activeSugar, -1, OLED_SUGAR_HEIGHT );
        } else {
#ifdef PRINT_DB
            uprintf("activeSugar %X failed to inialise\n", activeSugar);
#endif
            return;
        }
    }

    if (pixels == NULL) {
        pixels = malloc(OLED_SUGAR_BYTES);
        if (pixels != NULL) {
            memset( pixels, 0, OLED_SUGAR_BYTES );
        } else {
#ifdef PRINT_DB
            uprintf("pixels %X failed to inialise\n", pixels);
#endif
            return;
        }

    }

    static uint8_t sugarCntr = 0;

   for(int16_t h = OLED_SUGAR_HEIGHT-2; h >= 0; h--) {
        lineIdx_t w = activeSugar[h];

        if(w < 0 || w >= OLED_SUGAR_WIDTH) {
            continue;
        }
        lineIdx_t wn = -1;
        bool left;
        bool right;
#ifdef OLED_SUGAR_WITH_DOWN
        uint32_t r = rand_basic();
        const uint32_t thresh1 = UINT32_MAX/3;
        const uint32_t thresh2 = UINT32_MAX-thresh1;
        left  = r < thresh1;
        right = r > thresh2;
#else
        left = ((int32_t) rand_basic())<0;
        right = !left;
#endif
        if ( left ) {
            if( w > 0 ) {
                if(!getPixel(pixels, h+1, w-1)) {
                    wn = w - 1;
                }
            }
        } else if (right) {
            if ( w < OLED_SUGAR_WIDTH-1) {
                if(!getPixel(pixels, h+1, w+1)) {
                    wn = w + 1;
                }
            }
        } else { //centre
            if(!getPixel(pixels, h+1, w)) {
                wn = w ;
            }
        }
        if(wn == -1) {
            if(!getPixel(pixels, h+1, w)) {
                wn = w;
            }
        }
        if(wn != -1) {
            setPixel(pixels, h+1, wn, true);
            activeSugar[h+1] = wn;
            setPixel(pixels, h, w, false);
        }

        activeSugar[h] = -1;
    }
    if(sugarCntr != (keyCntr&0xFF)) {

        sugarCntr++;
        lineIdx_t w = OLED_SUGAR_WIDTH/2;
        bool left = false;
        if( ((int32_t) rand_basic())<0 ) {
            w--;
            left = true;
        }
        bool full = false;
        while(getPixel(pixels,0, w)) {
            if(left) {
                if (w == 0) {
                    w = OLED_SUGAR_WIDTH-1;
                } else if ( w == OLED_SUGAR_WIDTH/2) {
                    full = true;
                    break;
                } else {
                    w--;
                }
            } else {
                if (w == OLED_SUGAR_WIDTH-1) {
                    w = 0;
                } else if ( w == OLED_SUGAR_WIDTH/2-1) {
                    full = true;
                    break;
                } else {
                    w++;
                }
            }
        }

        if(!full) {
//        if(!getPixel(pixels, 0, w)) {
            setPixel(pixels, 0, w, true);
            activeSugar[0] = w;
        } else {
            pixelInvert = !pixelInvert;
            // we where not able to add a pixel (we where full so add one now that we have inverted)
            sugarCntr--;
            oled_sugar();
        }
    }
    rand_basic(); //just here to rotate the seed
    if(!is_oled_on()) {
        //OLED timedout so we will clear everything and start fresh
        memset( pixels, 0, OLED_SUGAR_BYTES );
        memset( activeSugar, -1, OLED_SUGAR_HEIGHT );
        oled_clear();
        pixelInvert = false;
    } else {
        oled_write_raw(pixels, OLED_SUGAR_BYTES);
    }

}

//
// ------------------------- OLED Sugar End -------------------------
//
bool oled_task_user(void) {
    update_log();
    if (is_keyboard_master()) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        #ifdef OLED_SUGAR
        oled_sugar();
        #else
        render_crkbd_logo();
        #endif

    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        add_keylog(keycode);
        #ifdef OLED_ENABLE
        keyCntr++;
        transaction_rpc_send(USER_SYNC_KEY_CNTR, sizeof(keyCntr), &keyCntr);
        #endif
    }
    return true;
}


void user_sync_a_update_keyCntr_on_other_board(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    keyCntr = *((const uint16_t *)in_data);
}

void keyboard_post_init_user_jumar(void) {
    #ifdef OLED_ENABLE
    transaction_register_rpc(USER_SYNC_KEY_CNTR, user_sync_a_update_keyCntr_on_other_board);
    #endif
}

#endif // OLED_ENABLE
