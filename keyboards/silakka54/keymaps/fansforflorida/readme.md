# Silakka54

Custom Vial firmware for the [Silakka54](https://github.com/Squalius-cephalus/silakka54) split keyboard. The Silakka54 uses the RP2040 Zero controller, which has an onboard WS2812 RGB LED. This firmware flashes the WS2812 at startup and uses it as a Caps Lock indicator.

The LED is driven directly via QMK's [`ws2812` API](https://docs.qmk.fm/drivers/ws2812) rather than the [RGB lighting](https://docs.qmk.fm/features/rgblight) subsystem. Because the board has only a single WS2812, driving it directly avoids the overhead of the rgblight subsystem.

## Features

### Startup color flash

When the keyboard powers on or is reset, the LED flashes red, green, and blue in sequence, pausing briefly between each color. This acts as a power-on self-test of the WS2812 chip. The flash runs once at startup and only on the master half of the keyboard (the half connected to the computer).

### Caps Lock indicator

While Caps Lock is active, the LED lights a dim, steady blue. The brightness is intentionally low so the LED is noticeable as a status light without being distracting.

## Installation

These files must be placed inside your local clone of the [`vial-qmk`](https://github.com/vial-kb/vial-qmk) repository before building.

1. Set up your QMK/Vial build environment, if you have not already done so (see the [Vial porting guide](https://get.vial.today/docs/) and [QMK setup docs](https://docs.qmk.fm/newbs_getting_started)).

2. Copy the files from this directory into the `keyboards/silakka54/keymaps/vial` directory of your `vial-qmk` repository, overwriting the stock Vial keymap files:

   ```bash
   cp * <path-to-vial-qmk>/keyboards/silakka54/keymaps/vial/
   ```

   Replace `<path-to-vial-qmk>` with wherever you cloned the `vial-qmk` repository.

## Building

From the root of your `vial-qmk` clone, run:

```bash
make silakka54:vial
```

## Flashing

To flash the firmware, run:

```bash
make silakka54:vial:flash
```

After running this command, double-tap the Reset button on the RP2040 Zero to put it into bootloader mode. The controller will appear as a mass storage drive named `RPI-RP2`, and the build system will copy the firmware to it automatically.

Repeat the flashing process for both halves of the keyboard.

## Restoring the stock keymap

To uninstall this firmware and restore the original Vial keymap, run the following from the root of your `vial-qmk` clone:

```bash
git restore keyboards/silakka54/keymaps/vial/
git clean -fd keyboards/silakka54/keymaps/vial/
```

The first command reverts any stock files that were overwritten; the second removes any files added by this firmware that are not part of the stock keymap. Then rebuild and reflash to return the keyboard to the stock firmware.
