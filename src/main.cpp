// LEDHat - Arduino library for LED hat.
//
// This example demonstrates the usage of the LEDHat library to scroll text across an LED baseball cap.
// Press the yellow button to wake and the red button to sleep.
//
// Wiring:
//     LEDs:
//         Connect VCC to 3.3v. Connect DATA to TX. Connect GND to G.
//     Buttons:
//         Connect yellow to 2 (T2). Connect red to 4 (T0).

#include <Arduino.h>
#include "LEDHat.h"

#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE

#include <DabbleESP32.h>

LEDHat hat;                                 // Create an instance of the LEDHat class
bool frame[FRAME_HEIGHT][FRAME_WIDTH];      // Create a frame buffer for storing LED states

String str = "Hello, World!"; 

void setup() {
  Dabble.begin("LEDHat");
  hat.clear();                              // Clear the LED display
  hat.frameZeros(frame);                    // Initialize the frame buffer with zeros
}

void loop() {
  delay(500);
  Dabble.processInput();
  // Define the text to scroll
  if (Terminal.available()){
    str = Terminal.readString();
  }
  hat.scrollText(frame, str);               // Scroll the text across the LED display
}