# 1up pi60 rgb v2

I purchased a 1upkeyboards pi60 RGB V2 60% PCB as a swap-in replacement for my Ducky One 2 Mini Frozen Llama RGB, since the pi60 offers hot swappable switches. Although the 1861ST in the  Ducky One 2 Mini is partially supported in QMK, "RGB LEDs are currently disabled until the driver is merged." The pi60 is fully supported in QMK.

## Layers

Here is a brief summary of my layers:

* Layer 0: Windows base layer.
* Layer 1: Gaming layer.
* Layer 2: Navigation and Fn layer (activated by holding either the Fn or Caps Lock key). For example:
  * Hold the Fn key and press Backspace for Delete.
  * Hold the Fn key and press a number key for the corresponding function key.
For example, Fn+2 for F2, Fn+5 for F5, and so on. The `-
 and `=` keys are F11 and F12.
  * Hold the Fn key and press the quote key for backquote. (Hold Shift for `~`.)
  * Hold the Fn key and press M, <, and > for mute, volume down, and volume up.
  * Hold the Fn key and press H and N for PgUp and PgDn.
  * Hold the Fn key and press U and O for Home and End.
  * Hold the Fn key and use IJKL for arrow keys.

## Layout

The right Shift, Alt, Windows, and Ctrl keys double as arrow keys, even without holding Fn. For example, hold right Shift for Shift, but tap it for up arrow.

The Caps Lock key doubles as the Fn key. Tap it for Caps Lock, but Hold it for Fn.

For example, hold Caps Lock and press Backspace for Delete.

Hold the Fn key (or Caps Lock) and press the left Windows key to toggle the gaming layer. This

has the following e ects:

* The left Windows key is disabled.
* The Caps Lock key works as Caps Lock.
* The right Shift, Alt, Windows, and Ctrl keys are arrow keys.

## Features

### RGB Matrix Lighting

The `rgb_matrix_indicators_advanced_user` function performs the following tasks:

* The 1upkeyboards pi60 RGB V2 has built-in underglow RGB. However, the Ducky One 2 Mini Frozen Llama case is opaque, so the underglow RGB matrix LEDs are turned off.
* The RGB matrix LED for Caps Lock is either off or on (fully white) to indicate the Caps Lock status.
* If the gaming layer is currently active, the RGB matrix LED for the left Windows key is turned off, since that key is disabled on that layer.

### Key Cancellation

Simultaneous Opposing Cardinal Directions ([SOCD](https://www.hitboxarcade.com/blogs/support/what-is-socd)) is a gaming concept where conflicting directional inputs are registered at the same time. For example, when a player presses both the left and right directional inputs simultaneously. This might happen if you were pressing the A key to move left then tried to press the D key to switch direction to the right without fully releasing the A key first.

In many games, these simultaneous opposing inputs can create conflicts or unintended behaviors. If a game is not programmed to handle these inputs correctly, it might not know whether to move the character left or right or might simply not register any movement at all.

To address SOCD issues, controllers implement certain rules or algorithms to handle conflicting inputs. For example, a common approach is to prioritize one direction over the other.

Razer added SOCD to their mechanical keyboards, calling it [Snap Tap](https://youtu.be/Feny5bs2JCg).

Wooting followed Razer and added SOCD to their mechanical keyboards. They also added a similar feature to their analog Hall effect keyboards called [Rappy Snappy](https://youtu.be/Uzv4bmtir3k) that activates the key that is pressed further.

QMK has a pull request for a similar feature called [Key Cancellation](https://github.com/qmk/qmk_firmware/pull/24000).

Consider the following scenario:

1. Press A
2. Press D
3. Release A
4. Release D

Here is what the keycode events look like without Key Cancellation:

```
KEY-DOWN - QMK: KC_A    Event key: a           Code: KeyA          KeyCode: 65
KEY-DOWN - QMK: KC_D    Event key: d           Code: KeyD          KeyCode: 68
KEY-UP   - QMK: KC_A    Event key: a           Code: KeyA          KeyCode: 65 in 154.000ms
KEY-UP   - QMK: KC_D    Event key: d           Code: KeyD          KeyCode: 68 in 280.000ms
```

However, when Key Cancellation detects that D has been pressed, it first sends a key up event for A to the computer:

```
KEY-DOWN - QMK: KC_A    Event key: a           Code: KeyA          KeyCode: 65
KEY-UP   - QMK: KC_A    Event key: a           Code: KeyA          KeyCode: 65 in 354.000ms
KEY-DOWN - QMK: KC_D    Event key: d           Code: KeyD          KeyCode: 68
KEY-UP   - QMK: KC_D    Event key: d           Code: KeyD          KeyCode: 68 in 401.000ms
```

## Building

If you have not only done so, set up QMK external userspace like this:

```
cd $HOME
qmk config user.overlay_dir="$(realpath qmk_userspace)"
```

Compile the firmware like this:

```
qmk compile -kb 1upkeyboards/pi60_rgb_v2 -km fansforflorida
```

## Flashing

Flash the firmware like this:

```
qmk flash -kb 1upkeyboards/pi60_rgb_v2 -km fansforflorida
```

Press Fn+Right Shift to enter the bootloader.
