// LEDHat - Arduino library for LED hat.
//
// This example shows a few simple demos of the LED baseball cap.
// Press the yellow button to wake and the red button to sleep.
//
// LEDs:
//    Connect VCC to 3.3v. Connect DATA to TX. Connect GND to G.
// Buttons:
//    Connect yellow to 2 (T2). Connect red to 4 (T0).

#include <Arduino.h>
#include "LEDHat.h"

LEDHat hat;
bool frame[FRAME_HEIGHT][FRAME_WIDTH];

void demoScanVertical(int frameDelay);
void demoScanHorizontal(int frameDelay);
void demoBlink(int blinkDelay, int numBlinks);

// Setup.
void setup() {
  touch_pad_t touchPin = hat.touchPin;
  bool isFirstBoot = (touchPin == TOUCH_PAD_MAX);
  if (isFirstBoot) {
    delay(500);
    hat.scrollText(frame, "Hello.");
    hat.sleep();
  }
}

void loop() {
  int frameDelay = 20;
  int blinkDelay = 250;
  int numBlinks = 3;

  delay(500);
  demoScanVertical(frameDelay);

  delay(500);
  demoScanHorizontal(frameDelay);

  delay(500);
  demoBlink(blinkDelay, numBlinks);
}

// Demo: Vertical Scan.
void demoScanVertical(int frameDelay) {
  hat.clear();

  hat.frameZeros(frame);
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

  hat.frameZeros(frame);
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
  hat.frameOnes(frame);
  hat.blinkFrame(frame, blinkDelay, numBlinks);
}