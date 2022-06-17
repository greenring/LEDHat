# LEDHat

Arduino library for LED hat.

To avoid using the app and Bluetooth controller that comes with the hat, you can implement your own custom animations.

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

### LEDHat_Snake.ino
An AI playing a game of Snake.

## Constants

| Name           | Description               | Value |
| -------------- | ------------------------- | ----- |
| `FRAME_WIDTH`  | Horizontal resolution     | 48    |
| `FRAME_HEIGHT` | Vertical resolution       | 12    |
| `NUM_BYTES`    | Number of bytes per frame | 72    |

## Functions

### Constructor
`LEDHat hat(brightness);` creates an instance of LEDHat with name `hat` with the specified brightness, where `brightness` is an integer in the range `[160 168]`.

### Zero Frame
`hat.zeroFrame(frame);` sets `frame` to an array of zeros, where `frame` is a `FRAME_HEIGHT`-by-`FRAME_WIDTH` Boolean array.

### Write Frame
`hat.writeFrame(frame);` writes the specified frame to the hat, where `frame` is a `FRAME_HEIGHT`-by-`FRAME_WIDTH` Boolean array.

### Clear
`hat.clear();` switches off all LEDs of the hat.

### Blink
`hat.blink(frame,blinkDelay,numBlinks);` blinks the specified frame on the hat, where `frame` is a `FRAME_HEIGHT`-by-`FRAME_WIDTH` Boolean array, blinkDelay is an integer specifying the delay between display in milliseconds (ms), and numBlinks is an integer specifying the number of blinks.
