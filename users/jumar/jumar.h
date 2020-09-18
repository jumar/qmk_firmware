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
#define ALT_BSP  LALT_T(KC_BSPC)
#define LT3_D    LT(3,KC_D)
#define LCTL_F   LCTL_T(KC_F)
#define RCTL_J   RCTL_T(KC_J)
#define LT5_K    LT(5,KC_K)
#define RSFT_L   RSFT_T(KC_L)
#define LSFT_KP  LSFT_T(KC_CAPS)
#define LT3_SPC  LT(3,KC_SPC)
#define LT3_ENT  LT(3,KC_ENT)
#define LT1_DEL  LT(1,KC_DEL)
#define LT4_GRV  LT(4,KC_GRV)
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

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

#define SIX_TRNS  _______, _______, _______, _______, _______, _______
#define FOUR_TRNS _______, _______, _______, _______

#define ROW5_LEFT_BASE
#define ROW4_LEFT_BASE TD(TAB_ESC), KC_Q      , KC_W      , KC_E      , KC_R       , KC_T
#define ROW3_LEFT_BASE LSFT_KP    , LT2_A     , LSFT_S    , LT3_D     , LCTL_F     , KC_G
#define ROW2_LEFT_BASE CTL_ENT    , TD(Z_UNDO), TD(X_CUTT), TD(C_COPY), TD(V_PASTE), KC_B
#define ROW1_LEFT_BASE

#define ROW5_RGHT_BASE
#define ROW4_RGHT_BASE TD(Y_REDO), KC_U        , KC_I   , KC_O  , KC_P   , KC_BSPC
#define ROW3_RGHT_BASE KC_H      , RCTL_J      , LT5_K  , RSFT_L, KC_SCLN, KC_QUOT
#define ROW2_RGHT_BASE KC_N      , KC_M        , KC_COMM, KC_DOT, KC_SLSH, KC_BSLS
#define ROW1_RGHT_BASE

#define ROW5_LEFT_SYMB _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5
#define ROW5_RGHT_SYMB KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11
#define ROW5_LEFT_VIM  SIX_TRNS
#define ROW5_RGHT_VIM  SIX_TRNS

// Row 4: 6 keys

#define ROW4_LEFT_SYMB _______, KC_EXLM, KC_AT, KC_LPRN, KC_RPRN, KC_PIPE
#define ROW4_RGHT_SYMB KC_UP,   KC_7,    KC_8,  KC_9,    KC_ASTR, KC_F12
#define ROW4_LEFT_VIM  SIX_TRNS
#define ROW4_RGHT_VIM  SIX_TRNS

// Row 3: 6 keys

#define ROW3_LEFT_SYMB _______,       KC_HASH, KC_DLR, KC_LCBR,  KC_RCBR, KC_GRV
#define ROW3_RGHT_SYMB KC_DOWN,       KC_4,    KC_5,   KC_6,     KC_PLUS, _______
#define ROW3_LEFT_VIM  _______,       DLEFT,   DRIGHT, KC_LCTL,  KC_LGUI, _______
#define ROW3_RGHT_VIM  KC_LEFT,       KC_DOWN, KC_UP,  KC_RIGHT, _______, _______



#define ROW2_LEFT_SYMB _______,       KC_PERC,     KC_CIRC, KC_LBRC,  KC_RBRC,        KC_TILD
#define ROW2_RGHT_SYMB KC_AMPR,       KC_1,        KC_2,    KC_3,     KC_BSLS,        _______
#define ROW2_LEFT_VIM  _______,       _______,     KC_TAB,  _______,  _______,        _______
#define ROW2_RGHT_VIM  SIX_TRNS



#define ROW1_LEFT_SYMB _______,       _______, _______,  _______
#define ROW1_RGHT_SYMB KC_0,          KC_DOT,  KC_EQL,   _______
#define ROW1_LEFT_VIM  FOUR_TRNS
#define ROW1_RGHT_VIM  FOUR_TRNS
