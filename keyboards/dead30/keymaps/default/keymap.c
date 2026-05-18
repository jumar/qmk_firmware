#include QMK_KEYBOARD_H
#include "dead30.h"
#include "jumar.h"

#undef TAPPING_TERM
#define TAPPING_TERM 120

#define FN1_SPC     LT(1, KC_SPC)
#define FN2_BSPC    LT(2, KC_BSPC)
#define FN3_C       LT(3, KC_C)

#define FN4_V       LT(4, KC_V)
#define FN5_B       LT(5, KC_B)
#define CTL_Z       CTL_T(KC_Z)
#define ALT_X       ALT_T(KC_X)
#define ALT_N       ALGR_T(KC_N)
#define CTL_M       RCTL_T(KC_M)
#define SFT_ENT     RSFT_T(KC_ENT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐                               ┌───┐
     * │ A │                               │ Z │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */

    [_0_QWERTY] = LAYOUT_ortho_4x10_ded30(
        KC_ESC       , XXXXXXX, XXXXXXX   , XXXXXXX  , XXXXXXX    , XXXXXXX    , XXXXXXX        , XXXXXXX     , XXXXXXX, KC_BSPC      ,
        TD(Q_TAB)    , KC_W   , KC_E      , KC_R     , KC_T       , KC_Y       , KC_U           , KC_I        , KC_O   , TD(P_BSPC)   ,
        TD(A_CAPS)   , LSFT_S , LT3_D     , LCTL_F   , KC_G       , KC_H       , RCTL_J         , LT5_K       , RSFT_L , TD(SCLN_QUOT),
        KC_Z         , KC_X   , TD(C_LGUI), TD(V_ALT), TD(B_SPACE), LT(1,TD(N_ENTER)), TD(M_DEL), TD(COMM_GRV), KC_DOT , TD(SLSH_BSLS)
    ),
    [_1_SYMBOLS_NUMPAD] = LAYOUT_ortho_4x10_ded30(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_EXLM, KC_EQL , KC_LPRN, KC_RPRN, KC_PIPE, KC_UNDS, KC_7   , KC_8   , KC_9   , KC_PLUS,
        KC_PERC, KC_ASTR, KC_LCBR, KC_RCBR, KC_AMPR, KC_AT  , KC_4   , KC_5   , KC_6   , KC_MINS,
        KC_HASH, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_DLR , KC_1   ,TD(N2_N0),KC_3   , KC_ASTR
    ),
    [_2_MOUSE_MEDIA] = LAYOUT_ortho_4x10_ded30(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_3_NAV] = LAYOUT_ortho_4x10_ded30(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_HOME, KC_UP  , KC_END,  XXXXXXX,
        XXXXXXX, _______, _______, _______, XXXXXXX, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_APP ,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_INS , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_4_GAM] = LAYOUT_ortho_4x10_ded30(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, KC_PGUP, KC_HOME, KC_UP  , KC_END,  XXXXXXX,
        KC_TAB,  _______, _______, _______, _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_APP ,
        _______, _______, _______, _______, _______, KC_INS , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_5_RGB] = LAYOUT_ortho_4x10_ded30(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_6_FN] = LAYOUT_ortho_4x10_ded30(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};
