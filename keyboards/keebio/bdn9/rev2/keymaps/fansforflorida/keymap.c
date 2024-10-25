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

enum layer_names {
    _VSTUDIO, // Visual Studio
    _ECLIPSE, // Eclipse
    _EMPTY2,
    _EMPTY3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* 
     * .--------------------.---------------.-------------.
     * | Open Type          | Change Layers | Open File   |
     * :--------------------+---------------+-------------:
     * | Toggle Breakpoints | Run/Resume    | End         |
     * :--------------------+---------------+-------------:
     * | Step Over          | Step Into     | Step Return |
     * '--------------------'---------------'-------------'
     */

    [_VSTUDIO] = LAYOUT(
        C(KC_T),     TO(1),  C(KC_O),
        C(S(KC_F9)), KC_F5,  S(KC_F5),
        KC_F10,      KC_F11, S(KC_F11)
    ),

    [_ECLIPSE] = LAYOUT(
        C(S(KC_T)),  TO(0),  C(S(KC_R)),
        LCA(KC_B),   KC_F8,  C(KC_F2),
        KC_F6,       KC_F5,  KC_F7
    ),

    [_EMPTY2] = LAYOUT(
        XXXXXXX, TO(3),   XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [_EMPTY3] = LAYOUT(
        XXXXXXX, TO(0),   XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX
    )

};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_VSTUDIO] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [_ECLIPSE] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [_EMPTY2] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [_EMPTY3] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
};
#endif

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    HSV hsv;

    switch(get_highest_layer(layer_state | default_layer_state)) {
        case _VSTUDIO:
            hsv = (HSV){HSV_PURPLE};
            break;
        case _ECLIPSE:
            hsv = (HSV){HSV_RED};
            break;
        case _EMPTY2:
            hsv = (HSV){HSV_GREEN};
            break;
        case _EMPTY3:
        default:
            hsv = (HSV){HSV_BLUE};
            break;
    }

    hsv.v = rgb_matrix_get_val();

    RGB rgb = hsv_to_rgb(hsv);
    for (uint8_t i = led_min; i < led_max; i++) {
        // To only affect RGB underglow, add this:
        // if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return false;
}
#endif
