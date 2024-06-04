#include "Arduino.h"
#include "font8x8.h"

Font::Font() {}

int Font::numTrailingColumns(char character) {
  int N = 0;

  if (character == ' ') {
    return 4;
  }

  bool glyph[8][8];
  getCharacter(glyph, character);

  for (int j = 7; j >= 0; j--) {
    for (int i = 0; i < 8; i++) {
      if (glyph[i][j]) {
        return N;
      }
    }
    N++;
  }
}

int Font::pixelWidth(char character) {
  return 8 - numTrailingColumns(character);
}

int Font::pixelWidth(String str) {

  if (str.length() == 0) {
    return 0;
  }

  int N = pixelWidth(str[0]);

  for (int n = 1; n < str.length(); n++) {
    N += pixelWidth(str[n]) + 1;
  }
  return N;
}

void Font::getCharacter(bool glyph[8][8], char character) {
  if (character > 128) {
    character = '?';
  }

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      glyph[i][j] = bitRead(_fontMap[character][i], j);
    }
  }
}