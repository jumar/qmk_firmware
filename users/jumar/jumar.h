/*
Copyright 2020 Julien Marbach

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

#pragma once
#include QMK_KEYBOARD_H
#include "quantum.h"

// General config.h type defines
#define TAPPING_TERM 150
#define MASTER_LEFT

//Tap Dance Declarations
enum {
  TAB_ESC = 0,
  SFT_CPS,
  X_CUTT,
  C_COPY,
  V_PASTE,
  Z_UNDO,
  Y_REDO,
};

#define KC_CUT   LCTL(KC_X)
#define KC_COPY  LCTL(KC_C)
#define KC_PASTE LCTL(KC_V)
#define KC_UNDO  LCTL(KC_Z)
#define KC_REDO  LCTL(KC_Y)
// Home row and modifiers
#define LT2_A    LT(2,KC_A)
#define LSFT_S   LSFT_T(KC_S)
#define LSFT_W   LSFT_T(KC_W)
#define ALT_BSP  LALT_T(KC_BSPC)
#define LT3_D    LT(3,KC_D)
#define LCTL_F   LCTL_T(KC_F)
#define LCTL_R   LCTL_T(KC_R)
#define RCTL_J   RCTL_T(KC_J)
#define LT5_K    LT(5,KC_K)
#define RSFT_L   RSFT_T(KC_L)
#define LSFT_KP  LSFT_T(KC_CAPS)
#define LCTL_SP  LCTL_T(KC_SPC)
#define LT3_SPC  LT(3,KC_SPC)
#define LT3_ENT  LT(3,KC_ENT)
#define LT1_DEL  LT(1,KC_DEL)
#define LT6_GRV  LT(6,KC_GRV)
#define CTL_ENT  LCTL_T(KC_ENT)

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Tab, twice for Escape
  [TAB_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_ESC),
  [SFT_CPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
  [X_CUTT]  = ACTION_TAP_DANCE_DOUBLE(KC_X, KC_CUT),
  [C_COPY]  = ACTION_TAP_DANCE_DOUBLE(KC_C, KC_COPY),
  [V_PASTE] = ACTION_TAP_DANCE_DOUBLE(KC_V, KC_PASTE),
  [Z_UNDO]  = ACTION_TAP_DANCE_DOUBLE(KC_Z, KC_UNDO),
  [Y_REDO]  = ACTION_TAP_DANCE_DOUBLE(KC_Y, KC_REDO),
};

typedef union {
  uint32_t raw;
  struct {
    bool     rgb_layer_change :1;
  };
} user_config_t;

user_config_t user_config;

enum custom_keycodes {
  RGB_LYR = SAFE_RANGE, // can always be here
};

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

#define SIX_TRNS   _______, _______, _______, _______, _______, _______
#define THREE_TRNS _______, _______, _______

// Layer definition
enum layer_names {
  _0_QWERTY = 0,
  _1_SYMBOLS_NUMPAD,
  _2_MOUSE_MEDIA,
  _3_NAV,
  _4_GAM,
  _5_RGB,
  _6_FN,
};

// LAYER 0 QWERTY
#define ROW5_LEFT_BASE KC_ESC     , KC_1      , KC_2      , KC_3      , KC_4       , KC_5
#define ROW4_LEFT_BASE TD(TAB_ESC), KC_Q      , KC_W      , KC_E      , KC_R       , KC_T
#define ROW3_LEFT_BASE LSFT_KP    , LT2_A     , LSFT_S    , LT3_D     , LCTL_F     , KC_G
#define ROW2_LEFT_BASE CTL_ENT    , KC_Z      , KC_X      , KC_C      , KC_V       , KC_B
#define ROW1_LEFT_BASE                                      KC_LGUI   , KC_LALT    , LCTL_SP

#define ROW5_RIGHT_BASE KC_6      , KC_7      , KC_8   , KC_9   , KC_0   , KC_BSPC
#define ROW4_RIGHT_BASE KC_Y      , KC_U      , KC_I   , KC_O   , KC_P   , KC_BSPC
#define ROW3_RIGHT_BASE KC_H      , RCTL_J    , LT5_K  , RSFT_L , KC_SCLN, KC_QUOT
#define ROW2_RIGHT_BASE KC_N      , KC_M      , KC_COMM, KC_DOT , KC_SLSH, KC_BSLS
#define ROW1_RIGHT_BASE LT3_ENT   , LT1_DEL   , LT6_GRV

// LAYER 1 SYMOLS-NUMPAD
#define ROW5_LEFT_SYMB_NUMPAD KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6
#define ROW4_LEFT_SYMB_NUMPAD KC_ESC , KC_EXLM, KC_EQL , KC_LPRN, KC_RPRN, KC_PIPE
#define ROW3_LEFT_SYMB_NUMPAD _______, KC_PERC, KC_ASTR, KC_LCBR, KC_RCBR, KC_AMPR
#define ROW2_LEFT_SYMB_NUMPAD _______, KC_HASH, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD
#define ROW1_LEFT_SYMB_NUMPAD                            KC_APP , TG(_4_GAM), _______

#define ROW5_RIGHT_SYMB_NUMPAD KC_F7  , KC_F8  , KC_F9 , KC_F10 , KC_F11 , KC_F12
#define ROW4_RIGHT_SYMB_NUMPAD KC_UNDS, KC_P7  , KC_P8 , KC_P9  , KC_PPLS, _______
#define ROW3_RIGHT_SYMB_NUMPAD KC_AT  , KC_P4  , KC_P5 , KC_P6  , KC_PMNS, KC_NLCK
#define ROW2_RIGHT_SYMB_NUMPAD KC_DLR , KC_P1  , KC_P2 , KC_P3  , KC_PAST, KC_PENT
#define ROW1_RIGHT_SYMB_NUMPAD _______, _______, KC_P0

// LAYER 2 MOUSE-MEDIA
#define ROW5_LEFT_MOUSE_MEDIA SIX_TRNS
#define ROW4_LEFT_MOUSE_MEDIA XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ROW3_LEFT_MOUSE_MEDIA XXXXXXX, _______, _______, XXXXXXX, _______, XXXXXXX
#define ROW2_LEFT_MOUSE_MEDIA XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ROW1_LEFT_MOUSE_MEDIA                            XXXXXXX, KC_BTN3, KC_BTN2

#define ROW5_RIGHT_MOUSE_MEDIA SIX_TRNS
#define ROW4_RIGHT_MOUSE_MEDIA KC_WH_U, XXXXXXX, KC_MS_U, XXXXXXX, KC_WH_U, _______
#define ROW3_RIGHT_MOUSE_MEDIA KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, XXXXXXX
#define ROW2_RIGHT_MOUSE_MEDIA XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX
#define ROW1_RIGHT_MOUSE_MEDIA KC_BTN1, KC_MPLY, KC_MFFD

// LAYER 3 NAVIGATION-COPY-PASTA
#define ROW5_LEFT_NAV_CPY_PASTA SIX_TRNS
#define ROW4_LEFT_NAV_CPY_PASTA KC_PSCR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ROW3_LEFT_NAV_CPY_PASTA XXXXXXX, XXXXXXX, _______, _______, _______, XXXXXXX
#define ROW2_LEFT_NAV_CPY_PASTA XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ROW1_LEFT_NAV_CPY_PASTA                            _______, _______, _______

#define ROW5_RIGHT_NAV_CPY_PASTA SIX_TRNS
#define ROW4_RIGHT_NAV_CPY_PASTA KC_PGUP, KC_HOME, KC_UP  , KC_END,  XXXXXXX, KC_PSCR
#define ROW3_RIGHT_NAV_CPY_PASTA KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_APP , XXXXXXX
#define ROW2_RIGHT_NAV_CPY_PASTA XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ROW1_RIGHT_NAV_CPY_PASTA _______, _______, XXXXXXX

// LAYER 4 GAMING
#define ROW5_LEFT_GAMING SIX_TRNS
#define ROW4_LEFT_GAMING KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5
#define ROW3_LEFT_GAMING KC_TAB , KC_Q   , LSFT_W , KC_E   , LCTL_R , KC_T
#define ROW2_LEFT_GAMING XXXXXXX, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B
#define ROW1_LEFT_GAMING                            XXXXXXX, KC_LALT, KC_SPC

#define ROW5_RIGHT_GAMING SIX_TRNS
#define ROW4_RIGHT_GAMING KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , XXXXXXX
#define ROW3_RIGHT_GAMING KC_H   , KC_J   , KC_K   , KC_L   , KC_UP  , XXXXXXX
#define ROW2_RIGHT_GAMING KC_N   , KC_M   , KC_COMM, KC_LEFT, KC_DOWN, KC_RGHT
#define ROW1_RIGHT_GAMING KC_ENT , KC_DEL , TG(_4_GAM)

// LAYER 5 RGB
#define ROW5_LEFT_RGB SIX_TRNS
#define ROW4_LEFT_RGB RESET  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ROW3_LEFT_RGB XXXXXXX, RGB_MOD, RGB_SAI, RGB_HUI, RGB_VAI, RGB_SPI
#define ROW2_LEFT_RGB XXXXXXX,RGB_RMOD, RGB_SAD, RGB_HUD, RGB_VAD, RGB_SPD
#define ROW1_LEFT_RGB                            XXXXXXX, XXXXXXX, RGB_LYR

#define ROW5_RIGHT_RGB SIX_TRNS
#define ROW4_RIGHT_RGB XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______
#define ROW3_RIGHT_RGB XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX
#define ROW2_RIGHT_RGB XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ROW1_RIGHT_RGB RGB_TOG, XXXXXXX, XXXXXXX

// LAYER 6 FN
#define ROW5_LEFT_FN SIX_TRNS
#define ROW4_LEFT_FN KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6
#define ROW3_LEFT_FN KC_LSFT, XXXXXXX, _______, XXXXXXX, _______, XXXXXXX
#define ROW2_LEFT_FN KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ROW1_LEFT_FN                            _______, _______, _______

#define ROW5_RIGHT_FN SIX_TRNS
#define ROW4_RIGHT_FN KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12
#define ROW3_RIGHT_FN XXXXXXX, _______, KC_PGUP, KC_HOME, KC_UP  , KC_END
#define ROW2_RIGHT_FN XXXXXXX, XXXXXXX, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT
#define ROW1_RIGHT_FN _______, _______, _______

void keyboard_post_init_user(void) {
  // Call the keymap level matrix init.

  // Read the user config from EEPROM
  user_config.raw = eeconfig_read_user();

  // Set default layer, if enabled
  if (user_config.rgb_layer_change) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom_blue();
    rgblight_mode_noeeprom(1);
  }
}

uint32_t layer_state_set_user(uint32_t state) {
    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case _0_QWERTY:
            if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_blue(); rgblight_mode_noeeprom(1); }
            break;
        case _1_SYMBOLS_NUMPAD:
            if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_chartreuse(); rgblight_mode_noeeprom(1); }
            break;
        case _2_MOUSE_MEDIA:
            if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_coral(); rgblight_mode_noeeprom(1); }
            break;
        case _3_NAV:
            if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_red(); rgblight_mode_noeeprom(1); }
            break;
        case _4_GAM:
            if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_orange(); rgblight_mode_noeeprom(1); }
            break;
        case _5_RGB:
            if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_teal(); rgblight_mode_noeeprom(1); }
            break;
        case _6_FN:
            if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_purple(); rgblight_mode_noeeprom(1); }
            break;
        default: //  for any other layers, or the default layer
            if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_white(); rgblight_mode_noeeprom(1); }
            break;
    }
  return state;
}

// RGB LAYER INDICATOR

bool process_record_user_RGB(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_LYR:  // This allows me to use underglow as layer indication, or as normal
        if (record->event.pressed) {
            user_config.rgb_layer_change ^= 1; // Toggles the status
            eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
            if (user_config.rgb_layer_change) { // if layer state indication is enabled,
                layer_state_set(layer_state);   // then immediately update the layer color
            }
        }
        return false; break;
    case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT: // For any of the RGB codes (see quantum_keycodes.h, L400 for reference)
        if (record->event.pressed) { //This disables layer indication, as it's assumed that if you're changing this ... you want that disabled
            if (user_config.rgb_layer_change) {        // only if this is enabled
                user_config.rgb_layer_change = false;  // disable it, and
                eeconfig_update_user(user_config.raw); // write the setings to EEPROM
            }
        }
        return true; break;
    default:
      return true; // Process all other keycodes normally
  }
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
  user_config.raw = 1;
  user_config.rgb_layer_change = true; // We want this enabled by default
  eeconfig_update_user(user_config.raw); // Write default value to EEPROM now

  // use the non noeeprom versions, to write these values to EEPROM too
  rgblight_enable(); // Enable RGB by default
  rgblight_sethsv_noeeprom_blue();  // Set it to oranrge by default
  rgblight_mode(1); // set to solid by default
}

void matrix_init_user_RGB_LYR(void) {
  // Call the keymap level matrix init.

  // Read the user config from EEPROM
  user_config.raw = eeconfig_read_user();

  // Set default layer, if enabled
  if (user_config.rgb_layer_change) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom_blue();
    rgblight_mode_noeeprom(1);
  }
}
