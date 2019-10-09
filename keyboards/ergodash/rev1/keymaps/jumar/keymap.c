#include QMK_KEYBOARD_H

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(KC_ESC, KC_NO, KC_CIRC, KC_GRV, KC_QUOT, KC_NO, LCTL(KC_X), KC_PSCR, KC_NO, KC_NO, KC_NO, KC_NO, TG(3), TG(2), KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, LCTL(KC_C), KC_NO, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS, KC_CAPS, LT(2,KC_A), LSFT_T(KC_S), LT(3,KC_D), LCTL_T(KC_F), KC_G, LCTL(KC_V), KC_NO, KC_H, RCTL_T(KC_J), KC_K, RSFT_T(KC_L), KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_APP, KC_INS, KC_N, KC_M, KC_COMM, KC_DOT, KC_UP, KC_APP, KC_LCTL, HYPR(KC_NO), KC_LGUI, MEH(KC_NO), KC_LALT, KC_SPC, KC_BSPC, KC_DEL, KC_ENT, MO(1), KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT),
	[1] = LAYOUT(KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO, KC_SLCK, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_NO, KC_EXLM, KC_EQL, KC_LPRN, KC_RPRN, KC_PIPE, KC_NO, KC_NO, KC_UNDS, KC_P7, KC_P8, KC_P9, KC_PPLS, KC_F12, KC_NO, KC_PERC, KC_ASTR, KC_LCBR, KC_RCBR, KC_AMPR, KC_NO, KC_NO, KC_AT, KC_P4, KC_P5, KC_P6, KC_PMNS, KC_NLCK, KC_NO, KC_HASH, KC_CIRC, KC_LCBR, KC_RCBR, KC_TILD, KC_NO, KC_NO, KC_DLR, KC_P1, KC_P2, KC_P3, KC_PAST, KC_PEQL, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_P0, KC_PDOT, KC_PSLS, KC_PENT),
	[2] = LAYOUT(RGB_MOD, RGB_HUD, RGB_HUI, RGB_TOG, RGB_VAD, RGB_VAI, RGB_LYR, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, RGB_RMOD, RGB_SAD, RGB_SAI, KC_NO, RGB_SPD, RGB_SPI, KC_NO, KC_NO, KC_WH_U, KC_NO, KC_MS_U, KC_NO, KC_WH_U, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_NO, RGB_M_R, RGB_M_G, RGB_M_B, RGB_M_K, KC_NO, KC_NO, KC_BTN3, KC_WREF, KC_NO, KC_VOLD, KC_MUTE, KC_VOLU, KC_NO, KC_NO, RGB_M_P, RGB_M_X, RGB_M_SN, RGB_M_SW, KC_BTN1, KC_BTN2, KC_NO, KC_WFWD, KC_WBAK, KC_MRWD, KC_MPLY, KC_MFFD, KC_NO, KC_NO),
	[3] = LAYOUT(RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PGUP, KC_HOME, KC_UP, KC_END, KC_PGUP, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO)
};

void keyboard_post_init_user(void) {
  // Call the keymap level matrix init.

  // Read the user config from EEPROM
  user_config.raw = eeconfig_read_user();

  // Set default layer, if enabled
  if (user_config.rgb_layer_change) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom_orange();
    rgblight_mode_noeeprom(1);
  }
}

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case 0:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_orange(); rgblight_mode_noeeprom(1); }
        break;
    case 1:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_chartreuse(); rgblight_mode_noeeprom(1); }
        break;
    case 2:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_coral(); rgblight_mode_noeeprom(1); }
        break;
    case 3:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_red(); rgblight_mode_noeeprom(1); }
        break;
    case 4:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_blue(); rgblight_mode_noeeprom(1); }
        break;
    default: //  for any other layers, or the default layer
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_white(); rgblight_mode_noeeprom(1); }
        break;
    }
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
  rgblight_sethsv_orange();  // Set it to oranrge by default
  rgblight_mode(1); // set to solid by default
}

void matrix_init_user(void) {
  // Call the keymap level matrix init.

  // Read the user config from EEPROM
  user_config.raw = eeconfig_read_user();

  // Set default layer, if enabled
  if (user_config.rgb_layer_change) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom_orange();
    rgblight_mode_noeeprom(1);
  }
}
