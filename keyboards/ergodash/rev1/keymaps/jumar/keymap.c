#include QMK_KEYBOARD_H
#include "jumar.h"

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

enum layer_names {
  _0_QWERTY,
  _1_SYMBOLS_NUMPAD,
  _2_MOUSE_MEDIA,
  _3_NAV,
  _4_GAMING,
  _5_GRAVE_RGB,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_0_QWERTY] = LAYOUT(
        KC_ESC     , KC_MYCM    , XXXXXXX, KC_GRV       , XXXXXXX    , XXXXXXX, KC_CUT  , KC_PSCR, XXXXXXX   , KC_LEFT, KC_UP  , KC_DOWN, KC_RGHT, KC_BSPC,
        KC_TAB     , KC_Q       , KC_W   , KC_E         , KC_R       , KC_T   , KC_COPY , XXXXXXX, TD(Y_REDO), KC_U   , KC_I   , KC_O   , KC_P,    KC_BSPC,
        TD(SFT_CPS), LT2_A      , LSFT_S , LT3_D        , LCTL_F     , KC_G   , KC_PASTE, XXXXXXX, KC_H      , RCTL_J , LT5_K  , RSFT_L , KC_SCLN, KC_QUOT,
        KC_LCTL    , TD(Z_UNDO) , TD(X_CUTT), TD(C_COPY), TD(V_PASTE), KC_B   , KC_APP  , KC_INS , KC_N      , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_BSLS,
        CTL_ENT    , HYPR(KC_NO), KC_LGUI   , XXXXXXX   , KC_LALT    , KC_SPC , KC_BSPC , KC_DEL , LT3_ENT   , LT1_DEL, LT4_GRV , XXXXXXX, XXXXXXX, XXXXXXX
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
        KC_LCTL, _______, KC_LGUI, _______, KC_LALT, KC_SPC , KC_BSPC, KC_DEL , KC_ENT , _______, KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
    ),
	[_5_GRAVE_RGB] = LAYOUT(
        RESET  , DEBUG  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_GRV , XXXXXXX, XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, RGB_SAI, RGB_HUI, RGB_VAI, RGB_SPI , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, RGB_SAD, RGB_HUD, RGB_VAD, RGB_SPD , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_RMOD, RGB_LYR, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
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
