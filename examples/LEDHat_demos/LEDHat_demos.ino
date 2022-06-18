// LEDHat - Arduino library for LED hat.
//
// Connect VCC to 3.3v. Connect DATA to TX. Connect GND to G.

#include <LEDHat.h>
int brightness = 168; // Brightness, specified in range [160, 168]
LEDHat hat(brightness);

bool frame[FRAME_HEIGHT][FRAME_WIDTH];

// Setup.
void setup() {

}

// Loop.
void loop() {
  int frameDelay;
  int blinkDelay;
  int numBlinks;

  frameDelay = 20;
  demoScanVertical(frameDelay);
  delay(500);

  frameDelay = 20;
  demoScanHorizontal(frameDelay);
  delay(500);

  blinkDelay = 10;
  demoBlink(blinkDelay, numBlinks);
  delay(500);
}

// Demo: Vertical Scan.
void demoScanVertical(int frameDelay) {
  hat.clear();

  hat.zeroFrame(frame);
  for (int i = 0; i < FRAME_HEIGHT; i++) {
    for (int j = 0; j < FRAME_WIDTH; j++) {
      frame[i][j] = 1;
      hat.writeFrame(frame);
      delay(frameDelay);
    }
  }
}

// Demo: Horizontal Scan.
void demoScanHorizontal(int frameDelay) {
  hat.clear();

  hat.zeroFrame(frame);
  for (int j = 0; j < FRAME_WIDTH; j++) {
    for (int i = 0; i < FRAME_HEIGHT; i++) {
      frame[i][j] = 1;
      hat.writeFrame(frame);
      delay(frameDelay);
    }
  }
}

// Demo: Blink
void demoBlink(int blinkDelay, int numBlinks) {
  hat.clear();

  hat.zeroFrame(frame);
  for (int j = 0; j < FRAME_WIDTH; j++) {
    for (int i = 0; i < FRAME_HEIGHT; i++) {
      frame[i][j] = 1;
    }
  }

  hat.blink(frame, blinkDelay, numBlinks);
}