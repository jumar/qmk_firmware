#include QMK_KEYBOARD_H
#include "jumar.h"

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

enum layer_names {
  _0_QWERTY,
  _1_SYMBOLS_NUMPAD,
  _2_MOUSE_MEDIA,
  _3_NAV,
  _4_FN,
  _5_GRAVE_RGB,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_0_QWERTY] = LAYOUT(
        TD(TAB_ESC), KC_Q,       KC_W      , KC_E      , KC_R       , KC_T   ,                  TD(Y_REDO), KC_U        , KC_I   , KC_O  , KC_P   , KC_BSPC,
        TD(SFT_CPS), LT2_A     , LSFT_S    , LT3_D     , LCTL_F     , KC_G   ,                  KC_H      , RCTL_J      , LT5_K  , RSFT_L, KC_SCLN, KC_QUOT,
        KC_LCTL    , TD(Z_UNDO), TD(X_CUTT), TD(C_COPY), TD(V_PASTE), KC_B   ,                  KC_N      , KC_M        , KC_COMM, KC_DOT, KC_SLSH, KC_BSLS,
                                                         KC_LGUI    , KC_LALT, KC_SPC, LT3_ENT, LT1_DEL   , LT4_APP
    ),
	[_1_SYMBOLS_NUMPAD] = LAYOUT(
        KC_ESC,  KC_EXLM, KC_EQL,  KC_LPRN, KC_RPRN, KC_PIPE,                   KC_UNDS, KC_P7, KC_P8, KC_P9, KC_PPLS, _______,
        _______, KC_PERC, KC_ASTR, KC_LCBR, KC_RCBR, KC_AMPR,                   KC_AT,   KC_P4, KC_P5, KC_P6, KC_PMNS, KC_NLCK,
        _______, KC_HASH, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                   KC_DLR,  KC_P1, KC_P2, KC_P3, KC_PAST, KC_PENT,
                                            _______, _______, _______, _______, _______, KC_P0
    ),
	[_2_MOUSE_MEDIA] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_WH_U, XXXXXXX, KC_MS_U, XXXXXXX, KC_WH_U, _______,
        XXXXXXX, _______, _______, XXXXXXX, _______, XXXXXXX,                   KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
                                            XXXXXXX, KC_BTN3, KC_BTN2, KC_BTN1, KC_MPLY, KC_MFFD
    ),
	[_3_NAV] = LAYOUT(
        RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR,                   KC_PGUP, KC_HOME, KC_UP,   KC_END,  XXXXXXX, _______,
        XXXXXXX, XXXXXXX, _______, _______, _______, XXXXXXX,                   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            _______, _______, _______, _______, _______, XXXXXXX
    ),
	[_4_FN] = LAYOUT(
        KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_LSFT, XXXXXXX, _______, XXXXXXX, _______, XXXXXXX,                   XXXXXXX, _______, XXXXXXX, _______, XXXXXXX, XXXXXXX,
        KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            _______, _______, _______, _______, _______, _______
    ),
    [_5_GRAVE_RGB] = LAYOUT(
        RESET,   XXXXXXX, XXXXXXX, KC_GRV,  XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        XXXXXXX, XXXXXXX, RGB_SAI, RGB_HUI, RGB_VAI, RGB_SPI,                   XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, RGB_SAD, RGB_HUD, RGB_VAD, RGB_SPD,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX, XXXXXXX
    )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

