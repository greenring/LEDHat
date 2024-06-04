#ifndef LEDHat_h
#define LEDHat_h

#include "font8x8.h"

#define FRAME_HEIGHT 12
#define FRAME_WIDTH 48
#define NUM_BYTES 72
#define BUTTON_RED 4
#define BUTTON_YELLOW 2
#define BUTTON_RED_T 0
#define THRESHOLD 10

class LEDHat
{
  public:
    LEDHat(int brightness = 168);
    void frameZeros(bool frame[FRAME_HEIGHT][FRAME_WIDTH]);
	void frameOnes(bool frame[FRAME_HEIGHT][FRAME_WIDTH]);
    void writeFrame(bool frame[FRAME_HEIGHT][FRAME_WIDTH]);
    void clear();
    void blinkFrame(bool frame[FRAME_HEIGHT][FRAME_WIDTH], int blinkDelay, int numBlinks);

    void addString(bool frame[FRAME_HEIGHT][FRAME_WIDTH], String str, int x, int y);
    void scrollText(bool frame[FRAME_HEIGHT][FRAME_WIDTH], String str, int scrollDelay = 25);

    void sleep();
	
	touch_pad_t touchPin;

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
	
	static void callbackYellow();
	static void callbackRed();
};

#endif
