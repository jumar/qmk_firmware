#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ortho_5x15(KC_ESC, KC_MYCM, KC_CIRC, KC_GRV, KC_QUOT, KC_NO, LCTL(KC_X), KC_NO, KC_PSCR, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, LCTL(KC_C), TG(4), KC_NO, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS, KC_CAPS, LT(2,KC_A), LSFT_T(KC_S), LT(3,KC_D), LCTL_T(KC_F), KC_G, LCTL(KC_V), TG(3), KC_NO, KC_H, RCTL_T(KC_J), KC_K, RSFT_T(KC_L), KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_NO, TG(2), KC_APP, KC_N, KC_M, KC_COMM, KC_DOT, KC_UP, KC_GRV, KC_LCTL, HYPR(KC_NO), MEH(KC_NO), KC_LGUI, KC_LALT, KC_SPC, KC_BSPC, TG(1), KC_DEL, KC_ENT, MO(1), KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT),
	[1] = LAYOUT_ortho_5x15(KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO, KC_NO, KC_NO, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_NO, KC_EXLM, KC_EQL, KC_LPRN, KC_RPRN, KC_PIPE, KC_NO, KC_NO, KC_NO, KC_UNDS, KC_P7, KC_P8, KC_P9, KC_PPLS, KC_F12, KC_NO, KC_PERC, KC_ASTR, KC_LCBR, KC_RCBR, KC_AMPR, KC_NO, KC_NO, KC_NO, KC_AT, KC_P4, KC_P5, KC_P6, KC_PMNS, KC_NLCK, KC_NO, KC_HASH, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_NO, KC_NO, KC_NO, KC_DLR, KC_P1, KC_P2, KC_P3, KC_PAST, KC_PEQL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_NO, KC_P0, KC_PDOT, KC_PSLS, KC_PENT),
	[2] = LAYOUT_ortho_5x15(RGB_VAD, RGB_VAI, KC_NO, RGB_TOG, RGB_RMOD, RGB_MOD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_HUD, RGB_HUI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_U, KC_NO, KC_MS_U, KC_NO, KC_WH_U, KC_NO, RGB_SAD, RGB_SAI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_NO, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_VOLD, KC_MUTE, KC_VOLU, KC_NO, KC_NO, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, KC_NO, KC_NO, KC_NO, TG(0), KC_NO, KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_NO),
	[3] = LAYOUT_ortho_5x15(RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PGUP, KC_HOME, KC_UP, KC_END, KC_PGUP, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TG(0), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[4] = LAYOUT_ortho_5x15(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_PSCR, KC_NO, KC_NO, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_NO, KC_TRNS, KC_PGUP, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS, KC_CAPS, KC_A, LSFT_T(KC_S), KC_D, LCTL_T(KC_F), KC_G, KC_NO, KC_NO, KC_PGDN, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_NO, KC_NO, KC_NO, KC_N, KC_M, KC_COMM, KC_DOT, KC_UP, KC_ESC, KC_LCTL, KC_NO, KC_LGUI, KC_NO, KC_LALT, KC_SPC, KC_NO, KC_NO, KC_NO, KC_LCTL, KC_NO, KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT)
};

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = biton32(state);
    switch (layer) {
    case 1:
        rgblight_setrgb (0, 204, 153); // greenish
        break;
    case 2:
        rgblight_setrgb (255, 0, 50); // redish
        break;
    case 3:
        rgblight_setrgb (255, 255, 0); // yellowish
        break;
    case 4:
        rgblight_setrgb (255, 153, 0); // orangeish
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (0, 51, 204); // blue
        break;
    }
  return state;
}
