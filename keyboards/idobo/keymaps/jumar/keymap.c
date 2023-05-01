#include QMK_KEYBOARD_H
#include "jumar.h"

#define LAYOUT LAYOUT_ortho_5x15

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_0_QWERTY] = LAYOUT_wrapper(
                                   ROW5_LEFT_BASE, KC_CUT  , TG(5), KC_PSCR, ROW5_RIGHT_BASE,
                                   ROW4_LEFT_BASE, KC_COPY , TG(4), XXXXXXX, ROW4_RIGHT_BASE,
                                   ROW3_LEFT_BASE, KC_PASTE, TG(3), XXXXXXX, ROW3_RIGHT_BASE,
                                   ROW2_LEFT_BASE, KC_APP  , TG(2), KC_INS , ROW2_RIGHT_BASE,
        CTL_ENT, KC_HYPR, KC_MEH , ROW1_LEFT_BASE, KC_BSPC , TG(1), KC_DEL , ROW1_RIGHT_BASE, XXXXXXX, XXXXXXX, XXXXXXX
    ),
	[_1_SYMBOLS_NUMPAD] = LAYOUT_wrapper(
                    ROW5_LEFT_SYMB_NUMPAD, _______, XXXXXXX, _______, ROW5_RIGHT_SYMB_NUMPAD,
                    ROW4_LEFT_SYMB_NUMPAD, _______, XXXXXXX, _______, ROW4_RIGHT_SYMB_NUMPAD,
                    ROW3_LEFT_SYMB_NUMPAD, _______, XXXXXXX, _______, ROW3_RIGHT_SYMB_NUMPAD,
                    ROW2_LEFT_SYMB_NUMPAD, _______, XXXXXXX, _______, ROW2_RIGHT_SYMB_NUMPAD,
        THREE_TRNS, ROW1_LEFT_SYMB_NUMPAD, _______, _______, _______, ROW1_RIGHT_SYMB_NUMPAD, THREE_TRNS
    ),
	[_2_MOUSE_MEDIA] = LAYOUT_wrapper(
                    ROW5_LEFT_MOUSE_MEDIA, XXXXXXX, XXXXXXX, XXXXXXX, ROW5_RIGHT_MOUSE_MEDIA,
                    ROW4_LEFT_MOUSE_MEDIA, XXXXXXX, XXXXXXX, XXXXXXX, ROW4_RIGHT_MOUSE_MEDIA,
                    ROW3_LEFT_MOUSE_MEDIA, XXXXXXX, XXXXXXX, XXXXXXX, ROW3_RIGHT_MOUSE_MEDIA,
                    ROW2_LEFT_MOUSE_MEDIA, XXXXXXX, _______, XXXXXXX, ROW2_RIGHT_MOUSE_MEDIA,
        THREE_TRNS, ROW1_LEFT_MOUSE_MEDIA, XXXXXXX, XXXXXXX, XXXXXXX, ROW1_RIGHT_MOUSE_MEDIA, THREE_TRNS
    ),
	[_3_NAV] = LAYOUT_wrapper(
                    ROW5_LEFT_NAV_CPY_PASTA, _______, XXXXXXX, _______, ROW5_RIGHT_NAV_CPY_PASTA,
                    ROW4_LEFT_NAV_CPY_PASTA, _______, XXXXXXX, _______, ROW4_RIGHT_NAV_CPY_PASTA,
                    ROW3_LEFT_NAV_CPY_PASTA, _______, _______, _______, ROW3_RIGHT_NAV_CPY_PASTA,
                    ROW2_LEFT_NAV_CPY_PASTA, _______, XXXXXXX, _______, ROW2_RIGHT_NAV_CPY_PASTA,
        THREE_TRNS, ROW1_LEFT_NAV_CPY_PASTA, _______, XXXXXXX, _______, ROW1_RIGHT_NAV_CPY_PASTA, THREE_TRNS
    ),
	[_4_GAM] = LAYOUT_ortho_5x15(
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , _______, XXXXXXX, _______, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , _______, _______, KC_PGUP, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS,
        KC_CAPS, KC_A   , LSFT_S , KC_D   , LCTL_F , KC_G   , _______, XXXXXXX, KC_PGDN, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , _______, XXXXXXX, _______, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_UP  , KC_ESC ,
        KC_LCTL, _______, KC_LGUI, _______, KC_LALT, KC_SPC , KC_BSPC, XXXXXXX, KC_DEL , KC_ENT , KC_SLSH, _______, KC_LEFT, KC_DOWN, KC_RGHT
    ),
   [_5_RGB] = LAYOUT_wrapper(
                    ROW5_LEFT_RGB, XXXXXXX, _______, XXXXXXX, ROW5_RIGHT_RGB,
                    ROW4_LEFT_RGB, XXXXXXX, XXXXXXX, XXXXXXX, ROW4_RIGHT_RGB,
                    ROW3_LEFT_RGB, XXXXXXX, XXXXXXX, XXXXXXX, ROW3_RIGHT_RGB,
                    ROW2_LEFT_RGB, XXXXXXX, XXXXXXX, XXXXXXX, ROW2_RIGHT_RGB,
        THREE_TRNS, ROW1_LEFT_RGB, XXXXXXX, XXXXXXX, XXXXXXX, ROW1_RIGHT_RGB, THREE_TRNS
    ),
};

void matrix_init_user(void) {
    matrix_init_user_RGB_LYR();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  process_record_user_RGB(keycode, record);
  return true;
}

#ifdef RGBLIGHT_ENABLE
// RGB LAYER INDICATOR
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
#endif
