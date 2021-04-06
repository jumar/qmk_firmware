/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

//#define USE_MATRIX_I2C
#ifdef KEYBOARD_crkbd_rev1_legacy
#    undef USE_I2C
#    define USE_SERIAL
#endif

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define USE_SERIAL_PD2

#ifdef RGBLIGHT_ENABLE
    #undef RGBLED_NUM
    #define RGBLIGHT_ANIMATIONS
    #define RGBLED_NUM 27
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif

#ifdef RGB_MATRIX_ENABLE
// #define SPLIT_TRANSPORT_MIRROR useless
#   define RGB_MATRIX_KEYPRESSES // reacts to keypresses
// #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
// #   define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#   define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #   define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
// #   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)

#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 8
#    define RGB_MATRIX_VAL_STEP 8
#    define RGB_MATRIX_SPD_STEP 10

#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_REACTIVE  // Sets the default mode, if none has been set
#define RGB_MATRIX_STARTUP_HUE 180 // Sets the default hue value, if none has been set
#define RGB_MATRIX_STARTUP_SAT 255 // Sets the default saturation value, if none has been set
#define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS // Sets the default brightness value, if none has been set
#define RGB_MATRIX_STARTUP_SPD 127 // Sets the default animation speed, if none has been set


/* Disable the animations you don't want/need.  You will need to disable a good number of these    *
 * because they take up a lot of space.  Disable until you can successfully compile your firmware. */
 #   define DISABLE_RGB_MATRIX_ALPHAS_MODS                  // Static dual hue, speed is hue for secondary hue
 #   define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN             // Static gradient top to bottom, speed controls how much gradient changes
 #   define DISABLE_RGB_MATRIX_BREATHING                    // Single hue brightness cycling animation
 #   define DISABLE_RGB_MATRIX_CYCLE_ALL                    // Full keyboard solid hue cycling through full gradient
 //#   define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT             // Full gradient scrolling left to right
 #   define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN                // Full gradient scrolling top to bottom
 #   define DISABLE_RGB_MATRIX_CYCLE_OUT_IN                 // Full gradient scrolling out to in
 #   define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL            // Full dual gradients scrolling out to in
 #   define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON       // Full gradent Chevron shapped scrolling left to right
 #   define DISABLE_RGB_MATRIX_DUAL_BEACON                  // Full gradient spinning around center of keyboard
 #   define DISABLE_RGB_MATRIX_RAINBOW_BEACON               // Full tighter gradient spinning around center of keyboard
 #   define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS            // Full dual gradients spinning two halfs of keyboard
 #   define DISABLE_RGB_MATRIX_RAINDROPS                    // Randomly changes a single key's hue
 #   define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS          // Randomly changes a single key's hue and saturation
 // MODES BELOW ARE VALID ONLY IF RGB_MATRIX_FRAMEBUFFER IS DEFINED
 #   define DISABLE_RGB_MATRIX_TYPING_HEATMAP               // How hot is your WPM!
 #   define DISABLE_RGB_MATRIX_DIGITAL_RAIN                 // That famous computer simulation
 // MODES BELOW ARE VALID ONLY IF RGB_MATRIX_KEYPRESS IS DEFINED
 //#   define DISABLE_RGB_MATRIX_SOLID_REACTIVE               // Static single hue, pulses keys hit to shifted hue then fades to current hue
 #   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE        // Pulses keys hit to hue & value then fades value out
 #   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE          // Hue & value pulse near a single key hit then fades value out
 #   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE     // Hue & value pulse near multiple key hits then fades value out
 #   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS         // Hue & value pulse the same column and row of a single key hit then fades value out
 #   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS    // Hue & value pulse the same column and row of multiple key hits then fades value out
 #   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS         // Hue & value pulse away on the same column and row of a single key hit then fades value out
 #   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS    // Hue & value pulse away on the same column and row of multiple key hits then fades value out
 #   define DISABLE_RGB_MATRIX_SPLASH                       // Full gradient & value pulse away from a single key hit then fades value out
 #   define DISABLE_RGB_MATRIX_MULTISPLASH                  // Full gradient & value pulse away from multiple key hits then fades value out
 #   define DISABLE_RGB_MATRIX_SOLID_SPLASH                 // Hue & value pulse away from a single key hit then fades value out
 #   define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH            // Hue & value pulse away from multiple key hits then fades value out
#endif

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
