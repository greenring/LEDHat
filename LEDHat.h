#ifndef LEDHat_h
#define LEDHat_h

#include "font8x8.h"

#define FRAME_HEIGHT 12
#define FRAME_WIDTH 48
#define NUM_BYTES 72

class LEDHat
{
  public:
    LEDHat(int brightness);
    void zeroFrame(bool frame[FRAME_HEIGHT][FRAME_WIDTH]);
    void writeFrame(bool frame[FRAME_HEIGHT][FRAME_WIDTH]);
    void clear();
    void blink(bool frame[FRAME_HEIGHT][FRAME_WIDTH], int blinkDelay, int numBlinks);

    void addString(bool frame[FRAME_HEIGHT][FRAME_WIDTH], String str, int x, int y);
    void scrollText(bool frame[FRAME_HEIGHT][FRAME_WIDTH], String str, int scrollDelay);

  private:
    int byteIndex(int i, int j);
    int bitIndex(int i, int j);
    byte checksum(byte data[NUM_BYTES]);
	
    void addCharacter(bool frame[FRAME_HEIGHT][FRAME_WIDTH], char character, int x, int y);

    int _brightness;
    int _head;
    byte _foot[4];
    bool _frame[FRAME_HEIGHT][FRAME_WIDTH];
	
	Font _font;
};

#endif
