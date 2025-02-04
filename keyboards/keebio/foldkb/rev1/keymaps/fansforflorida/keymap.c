/*
 * Copyright (C) 2023-2024  John Hall
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// Shift-Command-Q: Log out of your macOS user account. You will be asked to confirm.
#define LOGOUT LSG(KC_Q)

#define SPC_FN3 LT(3,KC_SPC)

enum layer_names {
    _MAC,
    _WIN,
    _FN,
    _NAV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAC] = LAYOUT(
        KC_MUTE, KC_ESC,  KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_BSLS, KC_DEL,
        KC_HOME,          KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_END,           KC_LGUI, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_PGUP,          KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   MO(2),
        KC_PGDN,          KC_LCTL, MO(2),   KC_LGUI, KC_LALT, SPC_FN3, SPC_FN3,     KC_SPC,  KC_SPC,           KC_RGUI, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_WIN] = LAYOUT(
        KC_MUTE, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          KC_LCTL, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______,     _______, _______,          _______, _______, _______, _______
    ),
    [_FN] = LAYOUT(
        RGB_TOG, KC_GRV,  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS, 
        _______,          _______, LOGOUT,  _______, _______, _______, _______,     _______, KC_7,    KC_8,    KC_9,    _______, _______, _______, _______, 
        _______,          KC_CAPS, _______, _______, _______, _______, _______,     _______, KC_4,    KC_5,    KC_6,    KC_COLN, KC_GRV,           _______, 
        _______,          _______, _______, _______, _______, _______, _______,     _______, KC_1,    KC_2,    KC_3,    KC_QUES, _______, _______, 
        _______,          _______, _______, TG(1),   _______, _______, _______,     KC_0,    KC_0,             KC_DOT,  _______, _______, _______
    ),
    [_NAV] = LAYOUT(
        RGB_TOG, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, MS_WHLU, _______, _______,     _______, KC_HOME, KC_UP,   KC_END,  _______, _______, _______, _______,
        _______,          _______, _______, KC_HOME, MS_WHLD, KC_END,  _______,     KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_GRV,           _______,
        _______,          _______, _______, _______, _______, _______, _______,     KC_PGDN, _______, KC_LBRC, KC_RBRC, KC_BSLS, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______,     KC_BSPC, KC_BSPC,          _______, _______, _______, _______
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_MAC] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_WIN] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [_NAV] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
};
#endif

#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_bspc[] = { KC_J, KC_K, COMBO_END };
const uint16_t PROGMEM combo_del[] = { KC_D, KC_F, COMBO_END };
const uint16_t PROGMEM combo_ent[] = { KC_K, KC_L, COMBO_END };
const uint16_t PROGMEM combo_esc[] = { KC_Q, KC_W, COMBO_END };

combo_t key_combos[] = {
  COMBO(combo_bspc, KC_BSPC),
  COMBO(combo_del, KC_DEL),
  COMBO(combo_ent, KC_ENT),
  COMBO(combo_esc, KC_ESC),
};
#endif

#ifdef OS_DETECTION_ENABLE
bool process_detected_host_os_user(os_variant_t detected_os) {
    if (detected_os != OS_MACOS && detected_os != OS_IOS) {
        layer_on(_WIN);
    }
    return false;
}
#endif
