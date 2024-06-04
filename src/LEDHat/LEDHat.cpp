#include "Arduino.h"
#include "LEDHat.h"
#include "font8x8.h"
#include "HardwareSerial.h"

LEDHat::LEDHat(int brightness /* = 168 */)
{
  _brightness = brightness;

  // Header and footer.
  _head = NUM_BYTES + 2;
  _foot[0] = NUM_BYTES + 2;
  _foot[1] = 3;
  _foot[2] = brightness;
  _foot[3] = brightness + 3;

  HardwareSerial SerialPort(2);  //if using UART2
  Serial.begin(38400, SERIAL_8N1, 16, 17);    // opens serial port, sets data rate to 38400 bps
    
  touchPin = esp_sleep_get_touchpad_wakeup_status();
  
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_YELLOW, INPUT_PULLUP);
	
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
	
  touchAttachInterrupt(BUTTON_RED, callbackRed, THRESHOLD);
  touchAttachInterrupt(BUTTON_YELLOW, callbackYellow, THRESHOLD);
  //touchSleepWakeUpEnable(BUTTON_YELLOW,THRESHOLD);
  esp_sleep_enable_touchpad_wakeup();
  
  if (touchPin == BUTTON_RED_T) {
    sleep();
  }
}

void LEDHat::frameZeros(bool frame[FRAME_HEIGHT][FRAME_WIDTH]) {
  for (int i = 0; i < FRAME_HEIGHT; i++) {
    for (int j = 0; j < FRAME_WIDTH; j++) {
      frame[i][j] = 0;
    }
  }
}

void LEDHat::frameOnes(bool frame[FRAME_HEIGHT][FRAME_WIDTH]) {
  for (int i = 0; i < FRAME_HEIGHT; i++) {
    for (int j = 0; j < FRAME_WIDTH; j++) {
      frame[i][j] = 1;
    }
  }
}

void LEDHat::writeFrame(bool frame[FRAME_HEIGHT][FRAME_WIDTH]) {
  int idxByte;
  int idxBit;

  for (int i = 0; i < FRAME_HEIGHT; i++) {
    for (int j = 0; j < FRAME_WIDTH; j++) {
      _frame[i][j] = frame[i][j];
    }
  }

  byte data[NUM_BYTES];
  for (int i = 0; i < NUM_BYTES; i++) {
    data[i] = 0;
  }

  for (int j = 0; j < FRAME_WIDTH; j++) {
    for (int i = 0; i < FRAME_HEIGHT; i++) {
      idxByte = byteIndex(i, j);
      idxBit = bitIndex(i, j);

      bitWrite(data[idxByte], idxBit, _frame[i][j]);
    }
  }

  _foot[0] = checksum(data);
  Serial.write(_head);
  Serial.write(data, NUM_BYTES);
  Serial.write(_foot, 4);
}

void LEDHat::clear() {
  bool frame[FRAME_HEIGHT][FRAME_WIDTH];
  frameZeros(frame);
  writeFrame(frame);
}

void LEDHat::addCharacter(bool frame[FRAME_HEIGHT][FRAME_WIDTH], char character, int x, int y) {
  bool glyph[8][8];
  _font.getCharacter(glyph, character);

  for (int i = max(x, 0); i < min(x + 8, FRAME_HEIGHT); i++) {
    for (int j = max(y, 0); j < min(y + 8, FRAME_WIDTH); j++) {
      frame[i][j] = glyph[i - x][j - y];
    }
  }
}

void LEDHat::addString(bool frame[FRAME_HEIGHT][FRAME_WIDTH], String str, int x, int y) {
  int sz = str.length();

  for (int n = 0; n < sz; n++) {
    addCharacter(frame, str[n], x, y);
    y += 9 - _font.numTrailingColumns(str[n]);
  }
}

void LEDHat::scrollText(bool frame[FRAME_HEIGHT][FRAME_WIDTH], String str, int scrollDelay /* = 25 */) {
  for (int y = FRAME_WIDTH; y >= -_font.pixelWidth(str); y--) {
    frameZeros(frame);
    addString(frame, str, 2, y);
    writeFrame(frame);
    delay(scrollDelay);
  }
}

void LEDHat::blinkFrame(bool frame[FRAME_HEIGHT][FRAME_WIDTH], int blinkDelay, int numBlinks) {

  for (int i = 0; i < numBlinks; i++) {
    clear();
    delay(blinkDelay);
    writeFrame(frame);
    delay(blinkDelay);
  }
}

// Byte index.
int LEDHat::byteIndex(int i, int j) {
  int idx = (3 * j + j % 2) / 2;

  if ((i >= 8) & (j % 2)) {
    idx--;
  } else if (i >= 8) {
    idx++;
  }
  return idx;
}

// Bit index.
int LEDHat::bitIndex(int i, int j) {
  if (i < 8) {
    return 7 - i;
  }

  return 15 - (j % 2) * 4 - i;
}

// Checksum.
byte LEDHat::checksum(byte data[NUM_BYTES]) {
  byte sum = _head;
  for (int i = 0; i < NUM_BYTES; i++) {
    sum += data[i] % 256;
  }
  return sum;
}

void LEDHat::callbackYellow(){
	
}

void LEDHat::callbackRed() {
  // Race condition? Might go into sleep before setting up interrupts.
  touchAttachInterrupt(BUTTON_RED, callbackRed, THRESHOLD);
  touchAttachInterrupt(BUTTON_YELLOW, callbackYellow, THRESHOLD);
  esp_sleep_enable_touchpad_wakeup();
  esp_deep_sleep_start();
}

void LEDHat::sleep() {
  esp_deep_sleep_start();
}