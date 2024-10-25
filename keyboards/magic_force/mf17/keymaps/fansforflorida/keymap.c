/*
 * Copyright (C) 2024  John Hall
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_numpad_5x4(
        TG(1),   KC_SLSH, KC_ASTR, LT(2, KC_MINS),
        KC_7,    KC_8,    KC_9,
        KC_4,    KC_5,    KC_6,    KC_PLUS,
        KC_1,    KC_2,    KC_3,
        KC_0,             KC_DOT,  KC_ENT
    ),
    [1] = LAYOUT_numpad_5x4(
        _______, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_HOME, KC_UP,   KC_PGUP,
        KC_LEFT, XXXXXXX, KC_RGHT, XXXXXXX,
        KC_END,  KC_DOWN, KC_PGDN,
        KC_INS,           KC_DEL,  XXXXXXX
    ),
    [2] = LAYOUT_numpad_5x4(
        _______, KC_CALC, KC_BSPC, _______,
        RGB_MOD, RGB_VAI, RGB_HUI,
        RGB_SPD, RGB_TOG, RGB_SPI, QK_BOOT,
        RGB_RMOD,RGB_VAD, RGB_HUD,
        _______,          _______, EE_CLR
    ),
};

bool led_update_user(led_t led_state) {
    return false;
}

void keyboard_pre_init_user(void) {
    // set NumLock LED to output and off (high)
    gpio_set_pin_output(B15);
    gpio_write_pin_high(B15);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (get_highest_layer(state) > 0) {
        gpio_write_pin_low(B15);
    } else {
        gpio_write_pin_high(B15);
    }
    return state;
}
