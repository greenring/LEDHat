#ifndef LEDHat_h
#define LEDHat_h

#define FRAME_HEIGHT 12
#define FRAME_WIDTH 48
#define NUM_BYTES 72

class LEDHat
{
  public:
    LEDHat(int brightness);
    void writeFrame(bool frame[FRAME_HEIGHT][FRAME_WIDTH]);
    void clear();

  private:
    int byteIndex(int i, int j);
    int bitIndex(int i, int j);
    byte checksum(byte data[NUM_BYTES]);

    int _brightness;
    int _head;
    byte _foot[4];
    bool _frame[FRAME_HEIGHT][FRAME_WIDTH];
};

#endif
