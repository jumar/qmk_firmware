#include QMK_KEYBOARD_H
#include "jumar.h"

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

enum layer_names {
  _0_QWERTY = 0,
  _1_SYMBOLS_NUMPAD,
  _2_MOUSE_MEDIA,
  _3_NAV,
  _4_FN,
  _5_RGB,
  _6_GAMING,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_0_QWERTY] = LAYOUT_wrapper( \
        ROW4_LEFT_BASE      ,                   ROW4_RGHT_BASE      ,
        ROW3_LEFT_BASE      ,                   ROW3_RGHT_BASE      ,
        ROW2_LEFT_BASE      ,                   ROW2_RGHT_BASE      ,
               KC_LGUI, ALT_BSP, LT3_SPC, LT3_ENT, LT1_DEL , LT4_GRV
    ),
	[_1_SYMBOLS_NUMPAD] = LAYOUT(
        KC_ESC , KC_EXLM, KC_EQL , KC_LPRN, KC_RPRN, KC_PIPE,                   KC_UNDS, KC_P7  , KC_P8  , KC_P9  , KC_PPLS, _______,
        _______, KC_PERC, KC_ASTR, KC_LCBR, KC_RCBR, KC_AMPR,                   KC_AT  , KC_P4  , KC_P5  , KC_P6  , KC_PMNS, KC_NLCK,
        _______, KC_HASH, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                   KC_DLR,  KC_P1  , KC_P2  , KC_P3  , KC_PAST, KC_PENT,
                                            KC_APP , TG(_6_GAMING), _______, _______, _______, KC_P0
    ),
	[_2_MOUSE_MEDIA] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_WH_U, XXXXXXX, KC_MS_U, XXXXXXX, KC_WH_U, _______,
        XXXXXXX, _______, _______, XXXXXXX, _______, XXXXXXX,                   KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
                                            XXXXXXX, KC_BTN3, KC_BTN2, KC_BTN1, KC_MPLY, KC_MFFD
    ),
	[_3_NAV] = LAYOUT(
        KC_PSCR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_PGUP, KC_HOME, KC_UP  , KC_END,  XXXXXXX, KC_PSCR,
        XXXXXXX, XXXXXXX, _______, _______, _______, XXXXXXX,                   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            _______, _______, _______, _______, _______, XXXXXXX
    ),
	[_4_FN] = LAYOUT(
        KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                   KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,
        KC_LSFT, XXXXXXX, _______, XXXXXXX, _______, XXXXXXX,                   XXXXXXX, _______, KC_PGUP, KC_HOME, KC_UP  , KC_END ,
        KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,
                                            _______, _______, _______, _______, _______, _______
    ),
  [_5_RGB] = LAYOUT(
        RESET  , XXXXXXX, XXXXXXX, KC_GRV , XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        XXXXXXX, XXXXXXX, RGB_SAI, RGB_HUI, RGB_VAI, RGB_SPI,                   XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, RGB_SAD, RGB_HUD, RGB_VAD, RGB_SPD,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX, XXXXXXX
    ),
  [_6_GAMING] = LAYOUT(
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , XXXXXXX,
        KC_TAB , KC_Q   , LSFT_W , KC_E   , LCTL_R , KC_T   ,                   KC_H   , KC_J   , KC_K   , KC_L   , KC_UP  , XXXXXXX,
        XXXXXXX, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                   KC_N   , KC_M   , KC_COMM, KC_LEFT, KC_DOWN, KC_RGHT,
                                            XXXXXXX, KC_LALT, KC_SPC , KC_ENT , KC_DEL , TG(_6_GAMING)
    ),
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
const char *read_layer_state(void); // commented as we have our own implementation
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

const char *read_mode_icon(bool swap);
const char *read_host_led_state(void);
void set_timelog(void);
const char *read_timelog(void);

char matrix_line_str[24];

void matrix_scan_user(void) {
   iota_gfx_task();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    set_timelog();
  }
  return true;
}

const char *read_layer_state(void) {
  uint8_t layer = biton32(layer_state);

  strcpy(matrix_line_str, "Layer: ");

  switch (layer)
  {
    case _0_QWERTY:
      strcat(matrix_line_str, "QWERTY");
      break;
    case _1_SYMBOLS_NUMPAD:
      strcat(matrix_line_str, "Symbols/Num");
      break;
    case _2_MOUSE_MEDIA:
      strcat(matrix_line_str, "Mouse/Media");
      break;
    case _3_NAV:
      strcat(matrix_line_str, "Navigation");
      break;
    case _4_FN:
      strcat(matrix_line_str, "FN/Nav");
      break;
    case _5_RGB:
      strcat(matrix_line_str, "RGB");
      break;
    case _6_GAMING:
      strcat(matrix_line_str, "Gaming");
      break;
    default:
      sprintf(matrix_line_str + strlen(matrix_line_str), "Unknown (%d)", layer);
  }

  return matrix_line_str;
}
const char *read_usb_state(void) {

  strcpy(matrix_line_str, "USB  : ");

  switch (USB_DeviceState) {
    case DEVICE_STATE_Unattached:
      strcat(matrix_line_str, "Unattached");
      break;
    case DEVICE_STATE_Suspended:
      strcat(matrix_line_str, "Suspended");
      break;
    case DEVICE_STATE_Configured:
      strcat(matrix_line_str, "Connected");
      break;
    case DEVICE_STATE_Powered:
      strcat(matrix_line_str, "Powered");
      break;
    case DEVICE_STATE_Default:
      strcat(matrix_line_str, "Default");
      break;
    case DEVICE_STATE_Addressed:
      strcat(matrix_line_str, "Addressed");
      break;
    default:
      strcat(matrix_line_str, "Invalid");
  }

  return matrix_line_str;
}

const char *read_wpm(void) {
  strcpy(matrix_line_str, "WPM: ");
  char buff[4];
  uint8_t wpm = get_current_wpm();
  if(wpm < 1000) {
    itoa(wpm, buff, 10);
  }
  else {
    strcpy(buff, "err");
  }
  strcat(matrix_line_str, buff);
  return matrix_line_str;
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write(matrix, read_logo());
    //matrix_write_ln(matrix, read_layer_state());
    //matrix_write_ln(matrix, read_usb_state());
    //matrix_write_ln(matrix, read_keylog()); // Matrix debugging
    //matrix_write_ln(matrix, read_keylogs()); // Prints typed chars (does not work with dual function keys
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_timelog()); // prints last timestamp and elaspsed time
  } else {
    matrix_write_ln(matrix, read_host_led_state());
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_wpm());
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

