# BDN9

I have a Keebio BDN9 macropad configured with all my frequently used IDE shortcuts, such as Debug Step Over, Debug Step Out, Run, Terminate, and so on. I use relegendable keycaps to label each key. Here is how I configured my BDN9:

| **Open Type** | **Change Layers** | **Open File** |
|:-:|:-:|:-:|
| **Toggle Breakpoints** | **Run/Resume** | **End** |
| **Step Over** | **Step Into** | **Step Return** |

I use separate layers for Visual Studio and Eclipse. For example, Debug Step Over is F10 in Visual Studio and F6 in Eclipse. However, I do not need to memorize these, since the bottom left key is always Debug Step Over regardless of the IDE.

## RGB Matrix Lighting

Turning the rotary encoder adjusts the RGB brightness, and tapping it changes layers. I customized the firmware to light each layer a different color as a visual indication of the active layer.

## Building

If you have not only done so, set up QMK external userspace like this:

```
cd $HOME
qmk config user.overlay_dir="$(realpath qmk_userspace)"
```

Compile the firmware like this:

```
qmk compile -kb keebio/bdn9/rev2 -km fansforflorida
```

## Flashing

Flash the firmware like this:

```
qmk flash -kb keebio/bdn9/rev2 -km fansforflorida
```
