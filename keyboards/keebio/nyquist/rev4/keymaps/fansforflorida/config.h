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

#pragma once

#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

#define DYNAMIC_KEYMAP_LAYER_COUNT 10

#define ONESHOT_TIMEOUT 5000

// Enables syncing Caps Lock state between both halves of the split keyboard
#define SPLIT_LED_STATE_ENABLE

// Enables syncing modifier state (including One Shot) between both halves of the split keyboard
#define SPLIT_MODS_ENABLE

#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_A
