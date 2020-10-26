#include QMK_KEYBOARD_H
#include "jumar.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*[_0_QWERTY] = LAYOUT_wrapper( \
        KC_ESC , KC_MYCM, XXXXXXX, KC_GRV , XXXXXXX, XXXXXXX, KC_CUT  , KC_PSCR, XXXXXXX, KC_LEFT, KC_UP  , KC_DOWN, KC_RGHT, KC_BSPC,
        ROW4_LEFT_BASE                                      , KC_COPY , XXXXXXX,                                       ROW4_RGHT_BASE,
        ROW3_LEFT_BASE                                      , KC_PASTE, XXXXXXX,                                       ROW3_RGHT_BASE,
        ROW2_LEFT_BASE                                      , KC_APP  , KC_INS ,                                       ROW2_RGHT_BASE,
        CTL_ENT, KC_HYPR, KC_MEH ,KC_LGUI, ALT_BSP, LT3_SPC , KC_BSPC , KC_ENT , LT3_ENT, LT1_DEL , LT4_GRV, XXXXXXX, XXXXXXX, XXXXXXX
    ),
	[_1_SYMBOLS_NUMPAD] = LAYOUT(
        KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______, _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
        KC_ESC , KC_EXLM, KC_EQL , KC_LPRN, KC_RPRN, KC_PIPE, _______, _______, KC_UNDS, KC_P7  , KC_P8  , KC_P9  , KC_PPLS, _______,
        _______, KC_PERC, KC_ASTR, KC_LCBR, KC_RCBR, KC_AMPR, _______, _______, KC_AT  , KC_P4  , KC_P5  , KC_P6  , KC_PMNS, KC_NLCK,
        _______, KC_HASH, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______, _______, KC_DLR , KC_P1  , KC_P2  , KC_P3  , KC_PAST, KC_PENT,
        _______, _______, _______, KC_APP , _______, _______, _______, _______, _______, _______, KC_P0  , KC_PDOT, KC_PSLS, KC_PEQL
    ),
	[_2_MOUSE_MEDIA] = LAYOUT(
        RESET  , DEBUG  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_U, XXXXXXX, KC_MS_U, XXXXXXX, KC_WH_U, XXXXXXX,
        XXXXXXX, _______, _______, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN3, KC_BTN2, XXXXXXX, XXXXXXX, KC_BTN1, KC_MPLY, KC_MFFD, XXXXXXX, XXXXXXX, XXXXXXX
    ),
	[_3_NAV] = LAYOUT(
        RESET  , DEBUG  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_HOME,   KC_UP,  KC_END, KC_PGUP, _______,
        _______, _______, KC_LSFT, _______, KC_LSFT, _______, _______, _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
	[_4_GAMING] = LAYOUT(
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , _______, _______, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , _______, KC_PGUP, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS,
        KC_CAPS, KC_A   , LSFT_S , KC_D   , LCTL_F , KC_G   , _______, KC_PGDN, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , _______, _______, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_UP  , KC_ESC ,
        KC_LCTL, _______, KC_LGUI, _______, KC_LALT, KC_SPC , KC_BSPC, KC_DEL , KC_ENT , KC_SLSH, _______, KC_LEFT, KC_DOWN, KC_RGHT
    ),
	[_5_GRAVE_RGB] = LAYOUT(
        RESET  , DEBUG  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_GRV , XXXXXXX, XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, RGB_SAI, RGB_HUI, RGB_VAI, RGB_SPI , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, RGB_SAD, RGB_HUD, RGB_VAD, RGB_SPD , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_RMOD, RGB_LYR, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )*/
    [_0_QWERTY] = LAYOUT_wrapper(
        ROW5_LEFT_BASE, KC_CUT  , KC_PSCR, ROW5_RIGHT_BASE,
        ROW4_LEFT_BASE, KC_COPY , XXXXXXX, ROW4_RIGHT_BASE,
        ROW3_LEFT_BASE, KC_PASTE, XXXXXXX, ROW3_RIGHT_BASE,
        ROW2_LEFT_BASE, KC_APP  , KC_INS , ROW2_RIGHT_BASE,
        CTL_ENT, KC_HYPR, KC_MEH , ROW1_LEFT_BASE, KC_BSPC, KC_ENT , ROW1_RIGHT_BASE, XXXXXXX, XXXXXXX, XXXXXXX
    ),
	[_1_SYMBOLS_NUMPAD] = LAYOUT_wrapper(
        ROW5_LEFT_SYMB_NUMPAD, _______, _______, ROW5_RIGHT_SYMB_NUMPAD,
        ROW4_LEFT_SYMB_NUMPAD, _______, _______, ROW4_RIGHT_SYMB_NUMPAD,
        ROW3_LEFT_SYMB_NUMPAD, _______, _______, ROW3_RIGHT_SYMB_NUMPAD,
        ROW2_LEFT_SYMB_NUMPAD, _______, _______, ROW2_RIGHT_SYMB_NUMPAD,
        THREE_TRNS, ROW1_LEFT_SYMB_NUMPAD, _______, _______, ROW1_RIGHT_SYMB_NUMPAD, THREE_TRNS
    ),
	[_2_MOUSE_MEDIA] = LAYOUT_wrapper(
        ROW5_LEFT_MOUSE_MEDIA, XXXXXXX, XXXXXXX, ROW5_RIGHT_MOUSE_MEDIA,
        ROW4_LEFT_MOUSE_MEDIA, XXXXXXX, XXXXXXX, ROW4_RIGHT_MOUSE_MEDIA,
        ROW3_LEFT_MOUSE_MEDIA, XXXXXXX, XXXXXXX, ROW3_RIGHT_MOUSE_MEDIA,
        ROW2_LEFT_MOUSE_MEDIA, XXXXXXX, XXXXXXX, ROW2_RIGHT_MOUSE_MEDIA,
        THREE_TRNS, ROW1_LEFT_MOUSE_MEDIA, XXXXXXX, XXXXXXX, ROW1_RIGHT_MOUSE_MEDIA, THREE_TRNS
    ),
	[_3_NAV] = LAYOUT_wrapper(
        ROW5_LEFT_NAV_CPY_PASTA, _______, _______, ROW5_RIGHT_NAV_CPY_PASTA,
        ROW4_LEFT_NAV_CPY_PASTA, _______, _______, ROW4_RIGHT_NAV_CPY_PASTA,
        ROW3_LEFT_NAV_CPY_PASTA, _______, _______, ROW3_RIGHT_NAV_CPY_PASTA,
        ROW2_LEFT_NAV_CPY_PASTA, _______, _______, ROW2_RIGHT_NAV_CPY_PASTA,
        THREE_TRNS, ROW1_LEFT_NAV_CPY_PASTA, _______, _______, ROW1_RIGHT_NAV_CPY_PASTA, THREE_TRNS
    ),
	[_4_GAM] = LAYOUT(
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , _______, _______, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , _______, KC_PGUP, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS,
        KC_CAPS, KC_A   , LSFT_S , KC_D   , LCTL_F , KC_G   , _______, KC_PGDN, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , _______, _______, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_UP  , KC_ESC ,
        KC_LCTL, _______, KC_LGUI, _______, KC_LALT, KC_SPC , KC_BSPC, KC_DEL , KC_ENT , KC_SLSH, TG(_4_GAM), KC_LEFT, KC_DOWN, KC_RGHT
    ),
   [_5_RGB] = LAYOUT_wrapper(
        ROW5_LEFT_RGB, XXXXXXX, XXXXXXX, ROW5_RIGHT_RGB,
        ROW4_LEFT_RGB, XXXXXXX, XXXXXXX, ROW4_RIGHT_RGB,
        ROW3_LEFT_RGB, XXXXXXX, XXXXXXX, ROW3_RIGHT_RGB,
        ROW2_LEFT_RGB, XXXXXXX, XXXXXXX, ROW2_RIGHT_RGB,
        THREE_TRNS, ROW1_LEFT_RGB, XXXXXXX, XXXXXXX, ROW1_RIGHT_RGB, THREE_TRNS
    ),
};

void matrix_init_user(void) {
    matrix_init_user_RGB_LYR();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  process_record_user_RGB(keycode, record);
  return true;
}
