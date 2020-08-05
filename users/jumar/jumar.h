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
#define LT3_D    LT(3,KC_D)
#define LCTL_F   LCTL_T(KC_F)
#define RCTL_J   RCTL_T(KC_J)
#define LT5_K    LT(5,KC_K)
#define RSFT_L   RSFT_T(KC_L)
#define LT3_ENT  LT(3,KC_ENT)
#define LT1_DEL  LT(1,KC_DEL)
#define LT4_GRV  LT(4,KC_GRV)

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TAB_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_ESC),
  [SFT_CPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
  [X_CUTT]  = ACTION_TAP_DANCE_DOUBLE(KC_X, KC_CUT),
  [C_COPY]  = ACTION_TAP_DANCE_DOUBLE(KC_C, KC_COPY),
  [V_PASTE] = ACTION_TAP_DANCE_DOUBLE(KC_V, KC_PASTE),
  [Z_UNDO]  = ACTION_TAP_DANCE_DOUBLE(KC_Z, KC_UNDO),
  [Y_REDO]  = ACTION_TAP_DANCE_DOUBLE(KC_Y, KC_REDO),
};
