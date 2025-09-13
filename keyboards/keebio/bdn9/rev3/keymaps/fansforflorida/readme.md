# BDN9

I have a Keebio BDN9 macropad configured with my frequently used IDE shortcuts like Debug Step Over, Debug Step Out, Run, Terminate, and so on. I use relegendable keycaps to label each key. Here is how I configured my BDN9:

| **Open Type**          | **Change Layers** | **Open File**   |
|:-----------------------|:------------------|:----------------|
| **Toggle Breakpoints** | **Run/Resume**    | **End**         |
| **Step Over**          | **Step Into**     | **Step Return** |

I use separate layers for Visual Studio and Eclipse, but I do not need to memorize the actual keycodes—thanks to consistent physical placement. For example, the bottom-left key is always Debug Step Over, whether it is F10 in Visual Studio or F6 in Eclipse.

This keymap demonstrates how to use layers in QMK.

---

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

The firmware extracts RGB values from the binary representation of the layer number (plus one). For example:

- **Bit 0** (LSB): Blue channel
- **Bit 1**: Green channel
- **Bit 2**: Red channel

For example:

- Layer 0 → (0+1) = 1 → binary `001` → RGB(0,0,1) = Blue
- Layer 1 → (1+1) = 2 → binary `010` → RGB(0,1,0) = Green
- Layer 2 → (2+1) = 3 → binary `011` → RGB(0,1,1) = Cyan

The RGB values are then converted to HSV color space to maintain consistent brightness when switching layers.

The code can be easily modified to use a predefined array of HSV colors instead of this binary mapping approach.

---

## Building the Firmware

If you have not only done so, set up QMK external userspace like this:

```bash
cd $HOME
qmk config user.overlay_dir="$(realpath qmk_userspace)"
```

Then compile the firmware:

```bash
qmk compile -kb keebio/bdn9/rev3 -km fansforflorida
```

---

## Flashing the Firmware

To flash the firmware onto your BDN9:

```bash
qmk flash -kb keebio/bdn9/rev3 -km fansforflorida
```
