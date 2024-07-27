# Quefrency rev3

## SOCD

Simultaneous Opposing Cardinal Directions ([SOCD](https://www.hitboxarcade.com/blogs/support/what-is-socd)) is a gaming concept where conflicting directional inputs are registered at the same time. For example, when a player presses both the left and right directional inputs simultaneously. This might happen if you were pressing the A key to move left then tried to press the D key to switch direction to the right without fully releasing the A key first.

In many games, these simultaneous opposing inputs can create conflicts or unintended behaviors. If a game is not programmed to handle these inputs correctly, it might not know whether to move the character left or right or might simply not register any movement at all.

To address SOCD issues, controllers implement certain rules or algorithms to handle conflicting inputs. For example, a common approach is to prioritize one direction over the other.

Razer added SOCD to their mechanical keyboards, calling it [Snap Tap](https://youtu.be/Feny5bs2JCg).

Wooting followed Razer and added SOCD to their mechanical keyboards. They also added a similar feature to their analog Hall effect keyboards called [Rappy Snappy](https://youtu.be/Uzv4bmtir3k) that activates the key that is pressed further.

QMK has a pull request for a similar feature called [Key Cancellation](https://github.com/qmk/qmk_firmware/pull/24000).

## What Key Cancellation Does

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

## How to Enable QMK Key Cancellation

First, you will need to check out the Key Cancellation pull request:

```
gh pr checkout 24000
```

To use Key Cancellation, add the following to your `rules.mk`

```make
KEY_CANCELLATION_ENABLE = yes
```

Your `keymap.c` will then need a Key Cancellation list definition:

```c
#ifdef KEY_CANCELLATION_ENABLE
const key_cancellation_t PROGMEM key_cancellation_list[] = {
    // on key down
    //       |    key to be released
    //       |     |
    [0] = {KC_D, KC_A},
    [1] = {KC_A, KC_D}
};
#endif
```

By default, Key Cancellation is disabled even after adding it to `rules.mk`. You need to use the `KX_CATG` (`0x7C7D`) or `KX_CAON` (`0x7C7B`) keycode to enable it. The status is stored in persistent memory, so you should not need to enable it again.
