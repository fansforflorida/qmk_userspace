# Nyquist rev4

## Layers

Here is a brief summary of my layers:

* Layer 0: Mac layout. The key next to A is Command.
* Layer 1: Windows/Linux layout. The key next to A is Ctrl.
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

## Layout

```
┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
│ =+│ 1!│ 2@│ 3#│ 4$│ 5%│   │ 6^│ 7&│ 8*│ 9(│ 0)│ -_│
├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
│Tab│ Q │ W │ E │ R │ T │   │ Y │ U │ I │ O │ P │ BS│
├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
│Cmd│ A │ S │ D │ F │ G │   │ H │ J │ K │ L │ ;:│ '"│
├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
│Sft│ Z │ X │ C │ V │ B │   │ N │ M │ ,<│ .>│ /?│Ent│
├───┼───┼───┼───┼───┴───┤   ├───┴───┼───┼───┼───┼───┤
│Ctl│ Fn│Win│Alt│spaceFN│   │ space │ up│lft│dwn│rht│
└───┴───┴───┴───┴───────┘   └───────┴───┴───┴───┴───┘
```

My Nyquist layout is based on my FoldKB layout:

* The `=` key is at top left next to 1.
* The `-` key is at the top right next to 0.
* Backspace is next to P.
* The key next to A is Command for macOS or Ctrl for Windows/Linux.
* The Ctrl, Fn, Windows, and Alt keys are in the lower left in the same order and position as my FoldKB.

I use my left hand for modifiers, so I put those keys on the left half.

The left Shift key is a [one shot key](https://docs.qmk.fm/one_shot_keys). For example, you can type a capital A character by first pressing and releasing Shift, and then pressing and releasing A.

I normally use my right thumb for spacebar, so I made the left spacebar dual function using [Layer-Tap](https://docs.qmk.fm/feature_layers?id=switching-and-toggling-layers). Hold it to access layer 2, but tap it for space. This way, I can hold spacebar with my left thumb and use IJKL for arrows, H and N for PgUp and PgDn, and U and O for Home and End with my right hand. This puts the navigation keys right on the home row.

I like that the FoldKB has Home, End, PgUp, and PgDn keys on the left half of the keyboard. This makes it easy to use my left hand to navigate a long document and leaves my right hand free to use the mouse. I added those keys on layer 2 on ESDF. This way, I can hold spacebar with my left thumb and use E and D to PgUp and PgDn in a document.

Dedicated arrow keys are at the bottom right of the keyboard. Instead of the vim arrangement of left, down, up, right, I arranged my arrow keys like this: up, left, down, right. The left, down, and right arrow keys are in the same order as an inverted T arrow cluster; only up is in a different position.

You can change any of the above using VIA, but there are a few features that I enabled in the firmware:

## Features

### OS Detection

During USB setup, the keyboard makes a best guess at the host OS based on OS specific behavior. If the OS is neither macOS nor iOS, the keyboard activates layer 1.

### Caps Word

I enabled [Caps Word](https://docs.qmk.fm/feature_caps_word). Double tap left Shift to turn on Caps Word. While active, letters are capitalized and `-` becomes `_`. This makes it easier to type `PROGRAM_CONSTANTS`. I never use Caps Lock, but if I really need Caps Lock, I can access it on layer 2.

### Combos

I have defined the following combos:

* J + K emits Backspace
* D + F emits Del
* K + L emits Enter
* Q + W emits Esc

Notice that most of these keys are on the home row, so I do not need to move my hand to reach them. They are also not letters that you are likely to type together in a word, which reduces misfires. L+K is the only exception, but I would have to press them within 50ms of each other, so in practice, typing words like "walk" do not accidentally send Enter.

The one thing I liked when I used an X-Bows keyboard was the extra Backspace key between G and H. When I built a Lily58 keyboard, I put Backspace there and put Del on the other half. J+K and D+F are the same idea, except I do not need to move my hand.

K+L being Enter is nice because Enter is one row lower than normal; it is next to the / key. K+L is easier to reach.

### RGB Matrix Lighting

I use RGB matrix lighting to visually indicate the status of Caps Lock, one shot shift, and Caps Word. This is done in the `rgb_matrix_indicators_advanced_user` method in `keymap.c`. To minimize power draw, all LEDs are turned off except for the indicated key:

* Shift for Caps Word and one shot Shift
* the key next to A for Caps Lock.

Normally, only the master half (the half plugged into the computer) is aware of the status of modifiers, Caps Word, and Caps Lock. Therefore, only the master half would indicate those states in the RGB lighting. Some changes were made to sync the state between both halves of the split keyboard:

* Defining `SPLIT_LED_STATE_ENABLE` in the `config.h` file enables syncing the Caps Lock state.
* Defining `SPLIT_MODS_ENABLE` in the `config.h` file enables syncing modifier state (including One Shot).
* Custom code was required to sync the state of Caps Word. See `sync.c`.

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
