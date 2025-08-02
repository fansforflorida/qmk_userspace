/* Copyright 2024  John Hall
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#define UNDERGLOW_ENABLE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_0,    TO(1),   KC_0,
        KC_0,    KC_0,    KC_0,
        KC_0,    KC_0,    KC_0
    ),
    [1] = LAYOUT(
        KC_1,    TO(2),   KC_1,
        KC_1,    KC_1,    KC_1,
        KC_1,    KC_1,    KC_1
    ),
    [2] = LAYOUT(
        KC_2,    TO(3),   KC_2,
        KC_2,    KC_2,    KC_2,
        KC_2,    KC_2,    KC_2
    ),
    [3] = LAYOUT(
        KC_3,    TO(4),   KC_3,
        KC_3,    KC_3,    KC_3,
        KC_3,    KC_3,    KC_3
    ),
    [4] = LAYOUT(
        KC_4,    TO(5),   KC_4,
        KC_4,    KC_4,    KC_4,
        KC_4,    KC_4,    KC_4
    ),
    [5] = LAYOUT(
        KC_5,    TO(0),   KC_5,
        KC_5,    KC_5,    KC_5,
        KC_5,    KC_5,    KC_5
    ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [1] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [2] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [3] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [4] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [5] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
};
#endif

#ifdef RGB_MATRIX_ENABLE
uint8_t rgb_to_hue(uint8_t rgb_mask) {
    uint8_t r = (rgb_mask & 0b100) >> 2;
    uint8_t g = (rgb_mask & 0b010) >> 1;
    uint8_t b = rgb_mask & 0b001;
    uint8_t c_max = r | g | b;
    uint16_t h;
    if (c_max == r) {
        h = 60 * ((g - b + 6) % 6);
    } else if (c_max == g) {
        h = 60 * (b + 2);
    } else if (c_max == b) {
        return 170;
    }
    return h * 255 / 360;
}

hsv_t get_layer_hsv(uint8_t layer) {
    hsv_t hsv = {
        .h = rgb_to_hue(layer + 1),
        .s = 255,
        .v = rgb_matrix_get_val()
    };
    return hsv;
}

void keyboard_post_init_user(void) {
#ifndef UNDERGLOW_ENABLE
    rgb_matrix_set_flags_noeeprom(LED_FLAG_ALL & ~LED_FLAG_UNDERGLOW);
#endif
    hsv_t hsv = get_layer_hsv(get_highest_layer(default_layer_state));
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    hsv_t hsv = get_layer_hsv(get_highest_layer(state));
    rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
    return state;
}
#endif
