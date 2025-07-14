// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef TAP_DANCE_ENABLE
enum {
    TD_NO_CAPS,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap twice for Caps Lock
    [TD_NO_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_NO, KC_CAPS),
};

#   define TD_CAPS TD(TD_NO_CAPS)
#else
#   define TD_CAPS KC_CAPS
#endif

enum custom_layer {
    _BASE,
    _FN1,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_65(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_END,
        TD_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LALT, KC_LGUI, MO(_FN1),KC_SPC,          KC_SPC,   KC_SPC,  KC_RALT, KC_RCTL, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN1] = LAYOUT_65(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_DEL, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_GRV,  _______, _______,
        KC_MPLY, KC_VOLD, KC_VOLU, KC_MPRV, KC_MNXT, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______
    )
};
