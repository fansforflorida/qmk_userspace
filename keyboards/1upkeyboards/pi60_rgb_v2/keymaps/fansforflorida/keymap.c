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

/* Define indicator LED indices, used for lighting effects  */
#define CAPS_LED_INDEX 45

enum layer_names {
    _GAME,
    _WIN,
    _FN,
};

/* Momentarily activates _FN layer when held, Caps Lock when tapped*/
#define LT_CAPS LT(_FN, KC_CAPS)

/* Right Shift when held, up arrow when tapped */
#define MT_UP MT(MOD_RSFT, KC_UP)

/* Right Alt when held, left arrow when tapped */
#define MT_LEFT MT(MOD_RALT, KC_LEFT)

/* Right GUI (Windows) when held, down arrow when tapped */
#define MT_DOWN MT(MOD_RGUI, KC_DOWN)

/* Right Control when held, right arrow when tapped */
#define MT_RGHT MT(MOD_RCTL, KC_RGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_GAME] = LAYOUT_60_ansi(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_UP,
        KC_LCTL, XXXXXXX, KC_LALT,                            KC_SPC,                             MO(2),   KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_WIN] = LAYOUT_60_ansi(
        QK_GESC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        LT_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          MT_UP,
        _______, KC_LGUI, _______,                            _______,                            _______, MT_LEFT, MT_DOWN, MT_RGHT
    ),

    [_FN] = LAYOUT_60_ansi(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, RGB_SPD, RGB_VAI, RGB_SPI, _______, _______, _______, KC_HOME, KC_UP,   KC_END,  KC_PSCR, KC_SCRL, KC_PAUS, _______,
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, _______, _______, KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_GRV,  _______,
        _______, _______, RGB_TOG, _______, _______, _______, KC_PGDN, KC_MUTE, KC_VOLD, KC_VOLU, _______,          _______,
        _______, TG(1),   _______,                            _______,                            _______, _______, _______, QK_BOOT
    )

};

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    /* Turn off RGB underglow */
    for (uint8_t i = led_min; i < led_max; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
            rgb_matrix_set_color(i, RGB_OFF);
        }
    }

    /* Turn off RGB for inactive keys (for example, left Windows key on gaming layer) */
    uint8_t layer = get_highest_layer(layer_state);
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) == KC_NO) {
                rgb_matrix_set_color(index, RGB_OFF);
            }
        }
    }

    /* Indicate Caps Lock status */
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LED_INDEX, 255, 255, 255);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LED_INDEX, 0, 0, 0);
    }

    return false;
}
#endif

#ifdef KEY_CANCELLATION_ENABLE
const key_cancellation_t PROGMEM key_cancellation_list[] = {
    // on key down
    //       |    key to be released
    //       |     |
    [0] = {KC_D, KC_A},
    [1] = {KC_A, KC_D}
};

layer_state_t layer_state_set_user(layer_state_t state) {
    if (get_highest_layer(state) == _GAME) {
        key_cancellation_enable();
    } else {
        key_cancellation_disable();
    }
    return state;
}
#endif
