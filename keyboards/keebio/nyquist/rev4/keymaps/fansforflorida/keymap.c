/*
 * Copyright (C) 2023-2025  John Hall
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

enum layer_names {
    _MAC,
    _WIN,
    _NAV,
    _FN
};

// One shot modifier Shift
#define OSM_SFT OSM(MOD_LSFT)

// Ctrl if held, Esc if tapped
#define MT_LCTL MT(MOD_LCTL,KC_ESC)

// Command if held, Esc if tapped
#define MT_LCMD MT(MOD_LGUI,KC_ESC)

// MO(2) if held, Space if tapped
#define SPC_FN2 LT(_NAV,KC_SPC)

// MO(3) if held, Application (Windows Context Menu key) if tapped
#define LT3_APP LT(_FN, KC_APP)

// MO(3) if held, Enter if tapped
#define LT3_ENT LT(_FN,KC_ENT)

// Shift-Command-Q: Log out of your macOS user account (you will be asked to confirm)
#define LOGOFF LSG(KC_Q)

// Shift-Command-Z: Reverse the undo command
#define REDO LSG(KC_Z)

#if defined(TAP_DANCE_ENABLE) && defined(CAPS_WORD_ENABLE)
enum {
    TD_COMMA_CAPS_WORD,
};

void dance_comma_caps_word(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        // Single tap: send comma
        tap_code(KC_COMM);
    } else if (state->count == 2) {
        if (get_mods() & MOD_MASK_SHIFT) {
            // Shift held: guillemets or bit shift left (<<)
            tap_code16(KC_LT);
            tap_code16(KC_LT);
        } else {
            // Double tap: enable Caps Word
            caps_word_on();
        }
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_COMMA_CAPS_WORD] = ACTION_TAP_DANCE_FN(dance_comma_caps_word),
};

#define TD_COMM TD(TD_COMMA_CAPS_WORD)
#else
#   if defined(TAP_DANCE_ENABLE) || defined(CAPS_WORD_ENABLE)
#   pragma message "CAPS_WORD_ENABLE = yes and TAP_DANCE_ENABLE = yes are both required for Comma/Caps Word"
#   endif
#define TD_COMM KC_COMM
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAC] = LAYOUT_ortho_5x12(
        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LGUI, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    TD_COMM, KC_DOT,  KC_SLSH, LT3_ENT,
        KC_LCTL, MO(3),   KC_LGUI, KC_LALT, SPC_FN2, SPC_FN2, KC_SPC,  KC_SPC,  KC_UP,   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_WIN] = LAYOUT_ortho_5x12(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_LCTL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, LT3_APP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_NAV] = LAYOUT_ortho_5x12(
        KC_ESC,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, MS_WHLU, _______, _______, _______, KC_HOME, KC_UP,   KC_END,  _______, KC_DEL,
        _______, _______, KC_HOME, MS_WHLD, KC_END,  _______, KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_GRV,
        _______, _______, _______, _______, _______, _______, KC_PGDN, _______, KC_LBRC, KC_RBRC, KC_BSLS, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_FN] = LAYOUT_ortho_5x12(
        KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, LOGOFF,  _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    _______, _______, _______,
        KC_CAPS, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, KC_4,    KC_5,    KC_6,    _______, _______, _______,
        _______, REDO,    _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    _______, _______, _______,
        _______, _______, TG(1),   _______, _______, _______, KC_0,    KC_0,    KC_DOT,  _______, _______, _______
    ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_MAC] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_WIN] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(KC_MNXT, KC_MPRV) },
    [_NAV] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_FN] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) }
};
#endif

#ifdef COMBO_ENABLE
enum combos {
    COMBO_BSPC,
    COMBO_DEL,
    COMBO_ENT,
    COMBO_ESC
};

const uint16_t PROGMEM combo_bspc[] = { KC_J, KC_K, COMBO_END };
const uint16_t PROGMEM combo_del[] = { KC_D, KC_F, COMBO_END };
const uint16_t PROGMEM combo_ent[] = { KC_K, KC_L, COMBO_END };
const uint16_t PROGMEM combo_esc[] = { KC_EQL, KC_1, COMBO_END };

combo_t key_combos[] = {
    [COMBO_BSPC] = COMBO(combo_bspc, KC_BSPC),
    [COMBO_DEL] = COMBO(combo_del, KC_DEL),
    [COMBO_ENT] = COMBO(combo_ent, KC_ENT),
    [COMBO_ESC] = COMBO(combo_esc, KC_ESC),
};
#endif

#ifdef RGB_MATRIX_ENABLE
void keyboard_post_init_user(void) {
    rgb_matrix_set_flags_noeeprom(LED_FLAG_UNDERGLOW);
}
#endif

#ifdef OS_DETECTION_ENABLE
bool process_detected_host_os_user(os_variant_t detected_os) {
    if (detected_os != OS_MACOS && detected_os != OS_IOS) {
        layer_on(_WIN);
    }
    return false;
}
#endif
