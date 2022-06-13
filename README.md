# LEDHat

Arduino library for LED hat.

![](images/led_cap.jpg)

## Setup
Disconnect the Bluetooth controller from the hat.

The LED panel has three wires. Connect them to your Arduino as follows:

| Arduino Pin | LED Panel |
| ----------- | --------- |
| 3.3V        | VCC       |
| TX          | DATA      |
| G           | GND       |

To use the library in your Arduino sketches, include the library using
```cpp
#include <LEDHat.h>
```

## Examples
### LEDHat_demos.ino
A series of simple demos demonstrating scanning and blinking.

## Constants

| Name           | Description               | Value |
| -------------- | ------------------------- | ----- |
| `FRAME_WIDTH`  | Horizontal resolution     | 48    |
| `FRAME_HEIGHT` | Vertical resolution       | 12    |
| `NUM_BYTES`    | Number of bytes per frame | 72    |

## Functions
### Constructor
`LEDHat hat(brightness);` creates an instance of LEDHat with name `hat` with the specified brightness, where `brightness` is an integer in the range `[160 168]`.

### Write Frame
`writeFrame(frame);` writes the specified frame to the hat, where `frame` is a `FRAME_HEIGHT`-by-`FRAME_WIDTH` Boolean array.

### Clear Frame
`clear();` switches off all LEDs of the hat.