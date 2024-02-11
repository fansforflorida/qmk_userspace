# Nyquist rev4

Here is a brief summary of my layers:

* Layer 0: Windows/Linux layout. The key next to A is Ctrl.
* Layer 1: Mac layout. The key next to A is Command.
* Layer 2: Navigation and Fn layer (activated by holding the left space key). For example:
  * F1-F10 are on the number row
  * Del is on Backspace
  * `[` is on `<`
  * `]` is on `>`
  * `\` is on `/`
  * `` ` `` is on `'`
* Layer 3: Numpad layer (activated by holding the Fn key below Z). The numpad layer puts a tenkey right on my home row:

```
Y U I
H J K
N M <
```

My 2u space key is zero, and the up arrow key is dot. It is not a full numpad, but it is very handy for entering 2FA codes for login or numbers in a spreadsheet without reaching for an external numpad. It uses number row keys to avoid NumLock issues in Windows.

My Nyquist layout is based on my FoldKB layout:

* The `=` key is at top left next to 1.
* The `-` key is at the top right next to 0.
* Backspace is next to P.
* The key next to A is Command for macOS or Ctrl for Windows/Linux.
* The Ctrl, Fn, Windows, and Alt keys are in the lower left in the same order and position as my FoldKB.

I use my left hand for modifiers, so I put those keys on the left half.

I normally use my right thumb for spacebar, so I made the left spacebar dual function using [Layer-Tap](https://docs.qmk.fm/#/feature_layers?id=switching-and-toggling-layers). Hold it to access layer 2, but tap it for space. This way, I can hold spacebar with my left thumb and use IJKL for arrows, H and N for PgUp and PgDn, and U and O for Home and End with my right hand. This puts the navigation keys right on the home row.

Dedicated arrow keys are at the bottom right of the keyboard. Instead of the vim arrangement of left, down, up, right, I arranged my arrow keys like this: up, left, down, right. The left, down, and right arrow keys are in the same order as an inverted T arrow cluster; only up is in a different position.

The left Shift key is a [one shot key](https://docs.qmk.fm/#/one_shot_keys). For example, you can type a capital A character by first pressing and releasing Shift, and then pressing and releasing A.

You can change any of the above using VIA, but there are a few features that I enabled in the firmware:

I enabled [Caps Word](https://docs.qmk.fm/#/feature_caps_word). Double tap left Shift to turn on Caps Word. While active, letters are capitalized and `-` becomes `_`. This makes it easier to type `PROGRAM_CONSTANTS`. I never use Caps Lock, but if I really need Caps Lock, I can access it on layer 2.

## Building

If you have not only done so, set up QMK external userspace like this:

```
cd $HOME
qmk config user.overlay_dir="$(realpath qmk_userspace)"
```

Compile the firmware like this:

```
qmk compile -kb keebio/nyquist/rev4 -km fansforflorida
```

## Flashing

Flash the firmware like this:

```
qmk flash -kb keebio/nyquist/rev4 -km fansforflorida
```

You will need to flash both sides separately.
