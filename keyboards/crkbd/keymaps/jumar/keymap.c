#include QMK_KEYBOARD_H
#include "jumar.h"

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

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
    matrix_init_user_RGB_LYR();
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
  process_record_user_RGB(keycode, record);
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
    case _4_GAM:
      strcat(matrix_line_str, "Gaming");
      break;
    case _5_RGB:
      strcat(matrix_line_str, "RGB");
      break;
    case _6_FN:
      strcat(matrix_line_str, "FN/Nav");
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

