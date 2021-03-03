#include QMK_KEYBOARD_H
#include "jumar.h"
#include "virtser.h"
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

#ifdef VIRTSER_ENABLE
/* listen on serial for commands. Either a set of lower case letters mapped to colors,
/  or upper case letters that change RGB mode.
/  special command C takes 3 numbers as arguments, terminated with a newline or comma or excess digits.
Command C takes 3-5octets of RGB settings. Numbers can be terminated with a comma or period.
3 octets = set all LED, 4th argument specfies specfic LED, 4+5 specify start and stop LEDs.
*/
#define SOH 0x01
#define STX 0x02
#define ETX 0x03
#define EOT 0x04

#define CMD_UNKNOWN 0
#define CMD_TIME    1
#define CMD_NOTIF   2
#define CMD_MAX     CMD_NOTIF

#define MAX_LINE_LENGTH 24

char ser_text[MAX_LINE_LENGTH] ; // ascii string payload from serial command
uint8_t ser_text_cur = 0; // cursor in ser_text array
uint8_t ser_cmd_started = 0 ; // are we in process
uint8_t ser_cmd_type = CMD_UNKNOWN;
uint8_t recv_char;

bool is_valid_cmd_code(uint8_t val) {
    return val > CMD_UNKNOWN && val <= CMD_MAX;
}

void reset_serial_protocol_parser(void) {
    ser_cmd_started = 0;
    ser_cmd_type = CMD_UNKNOWN;
}

void virtser_recv(uint8_t serIn) {
    recv_char = serIn;

    // Serial protocol:
    // key bytes:
    //  0x01 -> Start of heading
    //  0x02 -> Start of text
    //  0x03 -> End of text
    //  0x04 -> End of Transmission
    // Heading contains the code for the text payload:
    // Payload codes:
    //  0x20 -> Time
    //  0x21 -> Notification
    // Example for time (1:32 pm) transmission:
    // |0x01|0x20|0x02|0x31|0x3A|0x33|0x32|0x03|
    // Example for Notification ("ABC Meeting in 2 minutes") transmission:
    // |0x01|0x21|0x41|0x42|0x43|0x20|.........|0x03|

    if (ser_cmd_started == 0 && serIn == SOH) { // Start of header (transmission)
        ser_cmd_started = 1;
    } else if (serIn == EOT) { // End of transmission
        reset_serial_protocol_parser();
    }

    if (ser_cmd_started) {
        if (ser_cmd_type == CMD_UNKNOWN) {
            if (is_valid_cmd_code(serIn)) {
                // look for payload code in header
                ser_cmd_type = serIn;
            } else {
                // Invalid command code, reset state machine
                reset_serial_protocol_parser();
            }
        } else {
            switch (ser_cmd_type) {
                case CMD_TIME:

                    break;
                default: // todo write error message to screen
                case CMD_NOTIF:
                    break;
            }
            // parse command content
        }

    } else {
        // command not started, nothing to do
    }

    /*
#ifdef RGBLIGHT_ENABLE
    if ((serIn == 10 ) || (serIn ==  13) || ser_got_RGBbytes >=5) { //reached newline or max digits

        if (ser_cmd_started) {
            ser_cmd_started =0 ; // end loop at newline
            virtser_send('|');

            if (ser_got_RGBbytes==3) {
                rgblight_setrgb( rgb_r[0], rgb_r[1], rgb_r[2]);
            }

            if (ser_got_RGBbytes ==4) {
                if (( rgb_r[3] >=0)  && (rgb_r[3] <= RGBLED_NUM) ) { // is pos1 plausible
                    rgblight_setrgb_at ( rgb_r[0], rgb_r[1], rgb_r[2], rgb_r[3]);
                } else {
                        rgblight_setrgb( rgb_r[0], rgb_r[1], rgb_r[2]);
                }
            }

            if (ser_got_RGBbytes == 5) { // are start and end positions plausible?
                if ( (rgb_r[4] >0)  && (rgb_r[4] <= RGBLED_NUM) && (rgb_r[4] > rgb_r[3]) &&
                 (rgb_r[3] >=0)  && (rgb_r[3] <= (RGBLED_NUM -1))  ) {
                    rgblight_setrgb_range(rgb_r[0], rgb_r[1], rgb_r[2], rgb_r[3], rgb_r[4]);
               } else {
                   rgblight_setrgb( rgb_r[0], rgb_r[1], rgb_r[2]);
               }
            }
        } else { // newline outside of command loop, or something that can be ignored.
          //virtser_send('.');
        }
    }

    if (1 == ser_cmd_started) { // collecting bytes.
        if  (   // it is time to compute a byte
          ( ( (serIn == ',') || (serIn == '.') ) && (bs > 0) ) || // signal done with the byte.
            (bs ==2 )){ //or we know this is last.

            if ( (serIn <= '9') && (serIn >='0') ) { //3rd asci digit
                ser_rgbByte[bs] = serIn;
                bs++;
            //  virtser_send(serIn);
            }

            if (bs>3) {
                rgb_r[ser_got_RGBbytes]=255;
                ser_got_RGBbytes ++;
            }
            if (bs==3) {
              rgb_r[ser_got_RGBbytes] = (ser_rgbByte[0] -'0')*100 + (ser_rgbByte[1] -'0')*10 + (ser_rgbByte[2] -'0' );
              ser_got_RGBbytes ++;
            }
            if (bs ==2 ) {
               rgb_r[ser_got_RGBbytes] = (ser_rgbByte[0] -'0')*10 +  (ser_rgbByte[1] -'0' );
               ser_got_RGBbytes ++;
            }
            if (bs ==1) {
               rgb_r[ser_got_RGBbytes] = (ser_rgbByte[0] -'0');
               ser_got_RGBbytes ++;
            }  // {else wipe & start over}

          bs=0;
    //  virtser_send(ser_got_RGBbytes+'0');

        } else { // haven't got enough for our byte / no terminal marker
            if ( (serIn <= '9') && (serIn >='0') ) { //ascii only
                ser_rgbByte[bs] = serIn;
                bs++;
            //    virtser_send(serIn);
            }
        }
    } else { //not in command loop - next is command w/o arguments, or start of one.
        switch (serIn) {
            case 'C': // color switch
                ser_cmd_started=1;
                ser_got_RGBbytes = bs =0;
                virtser_send('/');
                break;

            case 'r': //red
                rgblight_setrgb(RGB_RED);
                break;

            case 'g':
                rgblight_setrgb(RGB_GREEN);
                break;

            case 'b':  // color switch
                rgblight_setrgb(RGB_BLUE);
                break;

            case 'w':  // color switch
                rgblight_setrgb(RGB_WHITE);
                break;

            case 'o':  // color black/off
                rgblight_setrgb(0,0,0);
                break;

            case 'T':  // toggle
                rgblight_toggle();
                break;

            case 'P': // pulse led
                rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING);
                break;
            case 'S':  // Static
                rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                break;

            case 'U':  // Rainbow
                rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_MOOD);
                break;

            default:
           //     virtser_send(serIn);
                break;

        }
    }
#endif // RGBLIGHT_ENABLE
*/
}

#endif // VirtSerial


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

const char *read_serial(void) {
  strcpy(matrix_line_str, ser_text);
  return matrix_line_str;
}
void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    //matrix_write(matrix, read_logo());
    matrix_write_ln(matrix, read_serial());
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

