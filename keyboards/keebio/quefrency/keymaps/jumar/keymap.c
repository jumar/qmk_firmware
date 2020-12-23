//#define KEYBOARD_keebio_quefrency_rev2
#include QMK_KEYBOARD_H
#include "jumar.h"

extern keymap_config_t keymap_config;
  /*
   * ┌─────┬─────┐┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐┌─────┐
   * │ F1  │ F2  ││ESC  │  1  │  2  │  3  │  4  │  5  │  6  │     │  7  │  8  │  9  │  0  │  -  │  =  │BSLS │ DEL ││HOME │
   * ├─────┼─────┤├─────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┘  ┌──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴─────┤├─────┤
   * │ F3  │ F4  ││TAB     │  Q  │  W  │  E  │  R  │  T  │     │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │BSPC    ││END  │
   * ├─────┼─────┤├────────┴┬────┴┬────┴┬────┴┬────┴┬────┴┐    └┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴────────┤├─────┤
   * │ F5  │ F6  ││CAPS     │  A  │  S  │  D  │  F  │  G  │     │  H  │  J  │  K  │  L  │  ;  │  '  │ENTER        ││PGUP │
   * ├─────┼─────┤├─────────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┐  └──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴───────┬─────┤├─────┤
   * │ F7  │ F8  ││LSHFT       │  Z  │  X  │  C  │  V  │  B  │     │  N  │  M  │  ,  │  .  │  /  │RSHFT     │ UP  ││PGDWN│
   * ├─────┼─────┤├──────┬─────┴─┬───┴──┬──┴───┬──┴────┴─────┤     ├─────┴─────┴────┬┴────┬┴────┬┴────┬─────┼─────┤├─────┤
   * │ F9  │F10  ││LCTRL │L_ALT  │L_GUI │FN    │SPC          │     │SPC             │R_ALT│R_CTR│APP  │LEFT │DOWN ││RIGHT│
   * └─────┴─────┘└──────┴───────┴──────┴──────┴─────────────┘     └────────────────┴─────┴─────┴─────┴─────┴─────┘└─────┘
   */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_0_QWERTY] = LAYOUT_65_with_macro(
    KC_F1,   KC_F2,   KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  XXXXXXX, KC_BSPC, KC_HOME, \
    KC_F3,   KC_F4,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS, KC_END, \
    KC_F5,   KC_F6,   KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                    KC_PGUP, \
    KC_F7,   KC_F8,   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                   KC_UP,   KC_PGDN, \
    KC_F9,   KC_F10,  KC_LCTL, KC_LALT, KC_LGUI, MO(_6_FN),KC_SPC, KC_SPC,  XXXXXXX, KC_RALT, KC_APP,  KC_RCTL,                            KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_6_FN] = LAYOUT_65_with_macro(
    _______, _______, KC_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_BSPC, RESET, \
    _______, _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, EEP_RST, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, KC_TILD, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______
  )
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 1) { // I only have this one
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    else if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}
