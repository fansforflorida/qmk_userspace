# Lily58

Here is a brief summary of my layers:

* Layer 0: Windows/Linux layer. Using [Mod-Tap](https://docs.qmk.fm/#/mod_tap), the key next to A is Ctrl if held or Esc if tapped.
* Layer 1: Mac layer. The key next to A is Command if held or Esc if tapped. All other keys are transparent. Toggle this layer by pressing the Windows key on layer 3.
* Layer 2: Fn layer. In addition to navigation keys, F keys, and symbols, it has a few helpful shortcuts:
  * Q is a shortcut for Cmd+Shift+Q to log out of macOS.
  * C is a shortcut for Ctrl+Shift+C, which many Windows applications recognize as a special copy function.
  * V is a shortcut for Ctrl+Alt+V, which opens the Paste Special dialog box in many Windows applications.
* Layer 3: numpad layer with a tenkey on the right half (zero is on N, and all numbers are number row keys so I do not need to worry about the NumLock state):

```
U I O
J K L
M < >
```

* Layers 4 and 5 are unused.

Putting the `=` key at top left next to 1 was borrowed from the [Datadesk SmartBoard](https://www.reddit.com/r/MechanicalKeyboards/comments/cn4gc8/i_have_been_using_this_datadesk_smartboard/). I typed on that keyboard for about 20 years, so I am very used to having that key there.

Putting Backspace next to H and N was inspired by the [X-Bows](https://x-bows.com/) keyboard. I put the Del key next to G and B for symmetry.

I use my left hand for modifiers, so I put those keys on the left half.

I use my right thumb for spacebar, so I made the left spacebar dual function using [Layer-Tap](https://docs.qmk.fm/#/feature_layers?id=switching-and-toggling-layers). Hold it to access layer 3, but tap it for Enter. This way, I can hold spacebar with my left thumb and use IJKL for arrows, H and N for PgUp and PgDn, and U and O for Home and End with my right hand.

I use mnemonics to make it easier to remember where I put special keys on layers:

* `[` is on the `<` key on layer 2
* `]` is on the `>` key on layer 2
* `\` is on the `/` key on layer 2
* `` ` `` is on the `'` key on layer 2
* Ins is on the Del key on layer 3

The left Shift key is a [one shot key](https://docs.qmk.fm/#/one_shot_keys). For example, you can type a capital A character by first pressing and releasing Shift, and then pressing and releasing A.

You can change any of the above using VIA, but there are a few features that I enabled in the firmware:

I enabled [Caps Word](https://docs.qmk.fm/#/feature_caps_word). Double tap left Shift to turn on Caps Word. While active, letters are capitalized and `-` becomes `_`. This makes it easier to type `PROGRAM_CONSTANTS`. I never use Caps Lock, but if I really need Caps Lock, I can access it on layer 3.

I have enabled [Auto Shift](https://docs.qmk.fm/#/feature_auto_shift). Tap a key and you get its character. Tap a key, but hold it *slightly* longer and you get its shifted state.

Column stagger makes it difficult for me to hit the bottom corner keys with my pinky. Auto Shift avoids needing to hit Shift at the bottom left, and Enter on the left thumb key avoids needing to hit Enter at the bottom right.
