// LEDHat - Arduino library for LED hat.
//
// Connect VCC to 3.3v. Connect DATA to TX. Connect GND to G.

#include <LEDHat.h>
int brightness = 168; // Brightness, specified in range [160, 168]
LEDHat hat(brightness);

// Default values.
void demoScanHorizontal(int frameDelay = 20);
void demoScanVertical(int frameDelay = 20);
void demoBlink(int frameDelay = 300);

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

  bool frame[FRAME_HEIGHT][FRAME_WIDTH];
  for (int i = 0; i < FRAME_HEIGHT; i++) {
    for (int j = 0; j < FRAME_WIDTH; j++) {
      frame[i][j] = 0;
    }
  }

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

  bool frame[FRAME_HEIGHT][FRAME_WIDTH];
  for (int i = 0; i < FRAME_HEIGHT; i++) {
    for (int j = 0; j < FRAME_WIDTH; j++) {
      frame[i][j] = 0;
    }
  }

  for (int j = 0; j < FRAME_WIDTH; j++) {
    for (int i = 0; i < FRAME_HEIGHT; i++) {
      frame[i][j] = 1;
      hat.writeFrame(frame);
      delay(frameDelay);
    }
  }
}

// Demo: Blink
void demoBlink(int frameDelay) {
  hat.clear();

  bool frame[FRAME_HEIGHT][FRAME_WIDTH];
  for (int i = 0; i < FRAME_HEIGHT; i++) {
    for (int j = 0; j < FRAME_WIDTH; j++) {
      frame[i][j] = 0;
    }
  }

  int numBlinks = 5;

  for (int k = 0; k < numBlinks; k++) {
    for (int j = 0; j < FRAME_WIDTH; j++) {
      for (int i = 0; i < FRAME_HEIGHT; i++) {
        frame[i][j] = 1;
      }
    }

    hat.writeFrame(frame);
    delay(frameDelay);

    hat.clear();
    delay(frameDelay);
  }
}