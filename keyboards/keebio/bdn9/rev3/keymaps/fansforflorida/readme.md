# BDN9

The Keebio BDN9 is a 3x3 macropad that supports up to 3 rotary encoders. The Keebio Jawn is a pretty aluminum case for the BDN9.

I have my BDN9 configured with my frequently used IDE shortcuts like Debug Step Over, Debug Step Out, Run, Terminate, and so on. I use separate layers for Visual Studio and Eclipse, but I do not need to memorize the shortcuts for each IDE. For example, the bottom-left key is always Debug Step Over, whether it is F10 in Visual Studio or F6 in Eclipse.

I customized the firmware to light each layer a different color to indicate the active layer. This keymap demonstrates how to implement per-layer RGB in QMK.

## RGB Matrix Lighting

The rotary encoder serves two purposes:

- **Turn** to adjust RGB brightness
- **Tap** to switch layers

Each layer is assigned a unique color for easy identification:

- Layer 0: Blue
- Layer 1: Green
- Layer 2: Cyan
- Layer 3: Red
- Layer 4: Purple
- Layer 5: Yellow

Each layer's color is defined as an HSV value in the `layer_hsv[]` array in `keymap.c`, indexed by layer number. The brightness (V) is overridden with the current RGB matrix brightness so it stays consistent when switching layers.

## Building the Firmware

If you have not already done so, set up QMK external userspace like this:

```bash
cd $HOME
qmk config user.overlay_dir="$(realpath qmk_userspace)"
```

Then compile the firmware:

```bash
qmk compile -kb keebio/bdn9/rev3 -km fansforflorida
```

## Flashing the Firmware

To flash the firmware onto your BDN9:

```bash
qmk flash -kb keebio/bdn9/rev3 -km fansforflorida
```
