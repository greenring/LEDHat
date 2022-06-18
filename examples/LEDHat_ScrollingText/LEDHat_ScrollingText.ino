// LEDHat - Arduino library for LED hat.
//
// Connect VCC to 3.3v. Connect DATA to TX. Connect GND to G.

#include <LEDHat.h>

int brightness = 168; // Brightness, specified in range [160, 168]
LEDHat hat(brightness);

bool frame[FRAME_HEIGHT][FRAME_WIDTH];

void setup() {
  hat.clear();
  hat.zeroFrame(frame);
}

void loop() {
  String str = "Hello, world!";
  int scrollDelay = 32;

  hat.scrollText(frame, str, scrollDelay);
}