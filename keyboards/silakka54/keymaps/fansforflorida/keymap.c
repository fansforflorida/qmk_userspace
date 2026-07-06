/*
 * Copyright (C) 2026  John Hall
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
#include "ws2812.h"
#include "color.h"

// Dim blue, used for Caps Lock indicator
#define RGB_CAPS_LOCK 0, 0, 20

// ms delay between each color during boot flash
#define BOOT_FLASH_DELAY_MS 100

enum layer_names {
    _WIN,
    _MAC,
    _NAV,
    _FN,
};

// MO(3) if held, Enter if tapped
#define ENT_FN LT(_FN,KC_ENT)

// Shift-Command-Q: Log out of your macOS user account. You will be asked to confirm.
#define LOGOUT LSG(KC_Q)

// Shift-Command-Z: Reverse the undo command
#define REDO LSG(KC_Z)

// MO(2) if held, Space if tapped
#define SPC_NAV LT(_NAV,KC_SPC)

// Toggles Mac layer, activating it if it's inactive and vice versa
#define TG_MAC TG(1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, ENT_FN,
                                   KC_LGUI, KC_LALT, SPC_NAV,          KC_SPC,  KC_RCTL, KC_RGUI
    ),
    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
        KC_LGUI, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
                                   KC_LCTL, _______, _______,          _______, _______, _______
    ),
    [2] = LAYOUT(
        KC_ESC,  _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, MS_WHLU, _______, _______,          _______, KC_HOME, KC_UP,   KC_END,  _______, KC_DEL,
        _______, _______, KC_HOME, MS_WHLD, KC_END,  _______,          KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_GRV,
        _______, _______, _______, _______, _______, _______,          KC_PGDN, _______, KC_LBRC, KC_RBRC, KC_BSLS, _______,
                                   _______, _______, _______,          _______, _______, _______
    ),
    [3] = LAYOUT(
        KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,            KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, LOGOUT,  _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
        KC_CAPS, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______,          _______, _______, _______, _______, _______, _______,
        _______, REDO,    _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
                                   TG_MAC,  _______, _______,          _______, _______, _______
    ),
};

// Tracks whether we've already done the boot flash, and last Caps Lock state
static bool caps_lock_led_state = false;

void set_color(uint8_t red, uint8_t green, uint8_t blue) {
    ws2812_set_color(0, red, green, blue);
    ws2812_flush();
}

void keyboard_post_init_user(void) {
    if (!is_keyboard_master()) {
        return;
    }

    ws2812_init();

    // Flash red -> green -> blue at full brightness, BOOT_FLASH_DELAY_MS apart
    set_color(RGB_RED);
    wait_ms(BOOT_FLASH_DELAY_MS);
    set_color(RGB_GREEN);
    wait_ms(BOOT_FLASH_DELAY_MS);
    set_color(RGB_BLUE);
    wait_ms(BOOT_FLASH_DELAY_MS);

    // Turn off after the flash, ready for housekeeping_task_user to take over
    set_color(RGB_OFF);
}

void housekeeping_task_user(void) {
    if (!is_keyboard_master()) {
        return;
    }

    bool caps_on = host_keyboard_led_state().caps_lock;

    if (caps_on != caps_lock_led_state) {
        caps_lock_led_state = caps_on;

        if (caps_lock_led_state) {
            set_color(RGB_CAPS_LOCK);
        } else {
            set_color(RGB_OFF);
        }
    }
}
