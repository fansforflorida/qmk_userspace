# Corne Keyboard (CRKBD)

To flash this keymap to a keyboard using the Elite-C controller, use:

```
qmk flash -kb crkbd/rev1 -km fansforflorida -bl dfu-split-left
qmk flash -kb crkbd/rev1 -km fansforflorida -bl dfu-split-right
```

To flash this keymap to a keyboard using the Elite-Pi controller, use:

```
qmk flash -kb crkbd/rev1 -km fansforflorida -e CONVERT_TO=elite_pi -bl uf2-split-left
qmk flash -kb crkbd/rev1 -km fansforflorida -e CONVERT_TO=elite_pi -bl uf2-split-right
```