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

### LEDHat_ScrollingText.ino
A demo showing scrolling text.

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

### Frame Zeros
`hat.frameZeros(frame);` sets `frame` to an array of zeros, where `frame` is a `FRAME_HEIGHT`-by-`FRAME_WIDTH` Boolean array.

### Frame Ones
`hat.frameOnes(frame);` sets `frame` to an array of ones, where `frame` is a `FRAME_HEIGHT`-by-`FRAME_WIDTH` Boolean array.

### Write Frame
`hat.writeFrame(frame);` writes the specified frame to the hat, where `frame` is a `FRAME_HEIGHT`-by-`FRAME_WIDTH` Boolean array.

### Clear
`hat.clear();` switches off all LEDs of the hat.

### Blink Frame
`hat.blinkFrame(frame,blinkDelay,numBlinks);` blinks the specified frame on the hat, where `frame` is a `FRAME_HEIGHT`-by-`FRAME_WIDTH` Boolean array, blinkDelay is an integer specifying the delay between blinks in milliseconds (ms), and numBlinks is an integer specifying the number of blinks.

### Add String
`addString(frame,str,x,y);` adds the specified string to the frame at row `x` and column `y`, where `frame` is a `FRAME_HEIGHT`-by-`FRAME_WIDTH` Boolean array, `str` is a string, and `x` and `y` are integers.

### Scroll Text
`scrollText(frame,str,scrollDelay);` scrolls the specified text on the hat, where `frame` is a `FRAME_HEIGHT`-by-`FRAME_WIDTH` Boolean array, `str` is a string, and `scrollDelay` is an integer specifying the delay between display updates in milliseconds (ms).

## Credits
### Fonts
Font based on:
 * https://github.com/dhepper/font8x8
 * http://dimensionalrift.homelinux.net/combuster/mos3/?p=viewsource&file=/modules/gfx/font8_8.asm