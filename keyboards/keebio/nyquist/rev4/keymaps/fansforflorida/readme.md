# Nyquist

My Nyquist layout is based on my FoldKB layout:

* The `=` key is at top left next to 1.
* The `-` key is at the top right next to 0.
* Backspace is next to P.
* The key next to A is Command for macOS or Ctrl for Windows/Linux.

Dedicated arrow keys are at the bottom right of the keyboard. Instead of the vim arrangement of left, down, up, right, I arranged my arrow keys like this: up, left, down, right. The left, down, and right arrow keys are in the same order as an inverted T arrow cluster; only up is in a different position.

Holding the "raise" key (next to the left space key) activates a layer with IJKL for arrows, H and N for PgUp and PgDn, and U and O for Home and End. This puts the navigation keys right on the home row.

I currently have a Nyquist rev3.5 (which has an ATmega32U4) and a Nyquist rev4 (which has an RP2040). The ATmega32U4 only has enough memory for 5 layers, but the RP2040 has enough memory for at least 10 layers. The config.h file tests for `RP2040_BOOTLOADER_DOUBLE_TAP_RESET` to set `DYNAMIC_KEYMAP_LAYER_COUNT`. (Let me know if there is a better way.) I currently only use 5 layers, but it is nice to know I have more available.
 
Here is a brief summary of my layers:

* Layer 0: Windows/Linux layout. The key next to A is Ctrl.
* Layer 1: Mac layout. The key next to A is Command.
* Layer 2: Navigation and Fn layer (activated by holding the "raise" key next to the left space key). For example:
    * F1-F10 are on the number row
    * Del is on Backspace
    * `[` is on `<`
    * `]` is on `>`
    * `\` is on `/`
    * `` ` `` is on `'`
* Layer 3: Numpad layer (activated by holding the "lower" key next to the right space key). See below for an explanation.
* Layer 4: Symbol layer (activated by holding the left space key). This brings symbols to my home row (for example, `(` and `)` to J and K).

The numpad layer puts a tenkey right on my home row:

```
U I O
J K L
M < >
```

Zero is N. It is not a full numpad, but it is very handy for entering 2FA codes for login or numbers in a spreadsheet without reaching for an external numpad. It uses number row keys to avoid NumLock issues in Windows.
