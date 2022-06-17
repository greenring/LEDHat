// LEDHat - Arduino library for LED hat.
//
// Connect VCC to 3.3v. Connect DATA to TX. Connect GND to G.

#include <LEDHat.h>
int brightness = 168; // Brightness, specified in range [160, 168]
LEDHat hat(brightness);

bool frame[FRAME_HEIGHT][FRAME_WIDTH];

// Default values.
void demoScanHorizontal(int frameDelay = 20);
void demoScanVertical(int frameDelay = 20);
void demoBlink(int blinkDelay = 300, int numBlinks = 10);

// Setup.
void setup() {

}

// Loop.
void loop() {
  demoScanVertical();
  delay(500);

  demoScanHorizontal();
  delay(500);

  demoBlink();
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