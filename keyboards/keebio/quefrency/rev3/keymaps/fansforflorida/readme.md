# Quefrency rev3

## Simultaneous Opposing Cardinal Directions (SOCD)

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

## Flashing

Flash the firmware like this:

```bash
qmk flash -kb keebio/quefrency/rev3 -km fansforflorida
```

Press the reset button on the PCB to enter the bootloader.
