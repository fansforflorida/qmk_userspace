# 1up pi60 rgb v2

I purchased a 1upkeyboards pi60 RGB V2 60% PCB as a swap-in replacement for my Ducky One 2 Mini Frozen Llama RGB, since the pi60 offers hot swappable switches. Although the 1861ST in the Ducky One 2 Mini is partially supported in QMK, "RGB LEDs are currently disabled until the driver is merged." The pi60 is fully supported in QMK.

## Layers

Here is a brief summary of my layers:

Layer 0 is the base layer. The right Shift, Alt, Windows, and Ctrl keys are arrow keys when tapped and modifiers when held.

Layer 1 is the navigation and Fn layer. Activate it by holding the Fn key. For example:

* Hold the Fn key and press Backspace for Delete.
* Hold the Fn key and press a number key for the corresponding function key. For example, Fn+2 for F2, Fn+5 for F5, and so on. The `-` and `=` keys are F11 and F12.
* Hold the Fn key and press the quote key for backquote. (Hold Shift for `~`.)
* Hold the Fn key and press M, `<`, and `>` for mute, volume down, and volume up.
* Hold the Fn key and press H and N for PgUp and PgDn.
* Hold the Fn key and press U and O for Home and End.
* Hold the Fn key and use IJKL for arrow keys.

Hold the Fn key and press the left Windows key to toggle (enable/disable) the Windows keys.

## Features

### RGB Matrix Lighting

The 1upkeyboards pi60 RGB V2 has built-in underglow RGB. However, the Ducky One 2 Mini Frozen Llama case is opaque, so the underglow RGB matrix LEDs are turned off by calling `rgb_matrix_set_flags` from `keyboard_post_init_user`.

The `rgb_matrix_indicators_advanced_user` function performs the following tasks:

* The RGB matrix LED for Caps Lock is either off or on (fully white) to indicate the Caps Lock status.
* The RGB matrix LEDs for both Windows keys light up white when the Windows key is disabled.

### Simultaneous Opposing Cardinal Directions (SOCD)

Simultaneous Opposing Cardinal Directions ([SOCD](https://www.hitboxarcade.com/blogs/support/what-is-socd)) is a gaming concept where conflicting directional inputs are registered at the same time. For example, when a player presses both the left and right directional inputs simultaneously. This might happen if you were pressing the A key to move left then tried to press the D key to switch direction to the right without fully releasing the A key first.

In many games, these simultaneous opposing inputs can create conflicts or unintended behaviors. If a game is not programmed to handle these inputs correctly, it might not know whether to move the character left or right or might simply not register any movement at all.

To address SOCD issues, controllers implement certain rules or algorithms to handle conflicting inputs. For example, a common approach is to prioritize one direction over the other.

Razer added SOCD to their mechanical keyboards, calling it [Snap Tap](https://youtu.be/Feny5bs2JCg).

Wooting followed Razer and added SOCD to their mechanical keyboards. They also added a similar feature to their analog Hall effect keyboards called [Rappy Snappy](https://youtu.be/Uzv4bmtir3k) that activates the key that is pressed further.

QMK had a pull request for a similar feature called [Key Cancellation](https://github.com/qmk/qmk_firmware/pull/24000). However, it was closed pending an RFC. See the discussion in [issue 24216](https://github.com/qmk/qmk_firmware/issues/24216).

This keyboard uses the [SOCD Cleaner](https://getreuer.info/posts/keyboards/socd-cleaner/index.html) community module by Pascal Getreuer.

Consider the following scenario:

1. Press A
2. Press D
3. Release A
4. Release D

Here is what the keycode events look like without SOCD Cleaner:

```plaintext
KEY-DOWN - QMK: KC_A    Event key: a           Code: KeyA          KeyCode: 65
KEY-DOWN - QMK: KC_D    Event key: d           Code: KeyD          KeyCode: 68
KEY-UP   - QMK: KC_A    Event key: a           Code: KeyA          KeyCode: 65 in 154.000ms
KEY-UP   - QMK: KC_D    Event key: d           Code: KeyD          KeyCode: 68 in 280.000ms
```

However, when SOCD Cleaner detects that D has been pressed, it first sends a key up event for A to the computer. If the D key is released while the A key is still held, the A key is reactivated.

```plaintext
KEY-DOWN - QMK: KC_A    Event key: a           Code: KeyA          KeyCode: 65
KEY-UP   - QMK: KC_A    Event key: a           Code: KeyA          KeyCode: 65 in 320.000ms
KEY-DOWN - QMK: KC_D    Event key: d           Code: KeyD          KeyCode: 68
KEY-UP   - QMK: KC_D    Event key: d           Code: KeyD          KeyCode: 68 in 198.000ms
KEY-DOWN - QMK: KC_A    Event key: a           Code: KeyA          KeyCode: 65
KEY-UP   - QMK: KC_A    Event key: a           Code: KeyA          KeyCode: 65 in 356.000ms
```

### Guarded Reset

Opening the bootloader or clearing the EEPROM are destructive operations that should not be triggered by accident. The standard `QK_BOOT` and `EE_CLR` keycodes activate immediately on keypress, which can be a problem if a key combination is accidentally pressed.

This keyboard uses the [Guarded Reset](https://github.com/drashna/qmk_modules/tree/main/guarded_reset) community module by Drashna. It intercepts `QK_BOOT` and `EE_CLR` and requires the key to be held for 3 seconds before the action fires. An accidental press that is quickly released has no effect.

## Building

If you have not already done so, set up QMK external userspace like this:

```bash
cd $HOME
qmk config user.overlay_dir="$(realpath qmk_userspace)"
```

Compile the firmware like this:

```bash
qmk compile -kb 1upkeyboards/pi60_rgb_v2 -km fansforflorida
```

## Flashing

Flash the firmware like this:

```bash
qmk flash -kb 1upkeyboards/pi60_rgb_v2 -km fansforflorida
```

Hold Fn+Right Ctrl for 3 seconds to enter the bootloader.

Sometimes you'll want to clear the EEPROM on your board to clear out all of the settings and start fresh. To do this, hold Fn+Left Ctrl for 3 seconds.
