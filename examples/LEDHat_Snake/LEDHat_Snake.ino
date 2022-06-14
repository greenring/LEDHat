// LEDHat - Arduino library for LED hat.
//
// Connect VCC to 3.3v. Connect DATA to TX. Connect GND to G.

#include <LEDHat.h>
int brightness = 168;  // Brightness, specified in range [160, 168]
LEDHat hat(brightness);
int frameDelay = 32;

int snake[FRAME_HEIGHT][FRAME_WIDTH];

int fruit[2];
int snakeHead[2];
int snakeLength;
int snakeDirection;  //1234 = NESW
int gameStatus;

// Setup.
void setup() {
  randomSeed(analogRead(0));

  gameStatus = 0;
  initializeSnake();
  spawnFruit();
}

// Loop.
void loop() {
  int direction;
  int turn;

  gameStatus = moveSnake();

  if (gameStatus == 0) {
    delay(frameDelay);

    if (AI_canSeeFruit()) {
      turn = 2 * random(2) - 1;
      turnSnake(turn);
    }

    if (AI_willCrash(snakeDirection)) {
      direction = (snakeDirection + 1) % 4;

      if (AI_willCrash(direction)) {
        turnSnake(-1);
      } else {
        turnSnake(1);
      }
    }
  }

  if (gameStatus == 1) {
    gameOver();
    initializeSnake();
    spawnFruit();
    yield();
  }
}

void initializeSnake() {
  for (int i = 0; i < FRAME_HEIGHT; i++) {
    for (int j = 0; j < FRAME_WIDTH; j++) {
      snake[i][j] = 0;
    }
  }

  snakeHead[0] = 6;
  snakeHead[1] = 12;

  snakeLength = 1;
  snakeDirection = 1;

  int i = snakeHead[0];
  int j = snakeHead[1];
  snake[i][j] = 1;
}

void spawnFruit() {

  int i = random(FRAME_HEIGHT);
  int j = random(FRAME_WIDTH);

  while (snake[i][j] > 0) {
    i = random(FRAME_HEIGHT);
    j = random(FRAME_WIDTH);
  }

  fruit[0] = i;
  fruit[1] = j;

  drawFrame();
}

void turnSnake(int turn) {
  snakeDirection = smod(snakeDirection + turn, 4);
}

bool moveSnake() {

  // New head position.
  if (snakeDirection % 2) {
    snakeHead[1] += 2 - snakeDirection;
  } else {
    snakeHead[0] += snakeDirection - 1;
  }

  snakeHead[0] = smod(snakeHead[0], FRAME_HEIGHT);
  snakeHead[1] = smod(snakeHead[1], FRAME_WIDTH);

  // Check dead.
  if (isDead()) {
    return true;
  }

  // Check fruit.
  bool hasFruit = snakeHead[0] == fruit[0] & snakeHead[1] == fruit[1];

  // Move/grow body.
  for (int i = 0; i < FRAME_HEIGHT; i++) {
    for (int j = 0; j < FRAME_WIDTH; j++) {

      if (snake[i][j] == snakeLength) {

        snakeLength += hasFruit;
        snake[i][j] = hasFruit * snakeLength;

      } else if (snake[i][j] > 0) {
        snake[i][j]++;
      }
    }
  }

  // Move head.
  int i = snakeHead[0];
  int j = snakeHead[1];
  snake[i][j] = 1;

  if (hasFruit) {
    spawnFruit();
  }

  drawFrame();
  return false;
}

bool isDead() {
  int i = snakeHead[0];
  int j = snakeHead[1];
  return snake[i][j] > 0;
}

bool AI_canSeeFruit() {
  if (snakeDirection == 0 | snakeDirection == 2) {
    return (snakeHead[0] == fruit[0]);
  }

  return (snakeHead[1] == fruit[1]);
}

bool AI_willCrash(int direction) {
  int i = snakeHead[0];
  int j = snakeHead[1];

  if (direction % 2) {
    j = smod(j - direction + 2, FRAME_WIDTH);
  } else {
    i = smod(i + direction - 1, FRAME_HEIGHT);
  }

  return snake[i][j] > 0;
}

void gameOver() {
  int blinkDelay = 128;
  int numBlinks = 10;

  for (int i = 0; i < numBlinks; i++) {
    hat.clear();
    delay(blinkDelay);
    drawFrame();
    delay(blinkDelay);
  }

  hat.clear();
  delay(2 * blinkDelay);
}

void drawFrame() {
  bool frame[FRAME_HEIGHT][FRAME_WIDTH];
  
  for (int i = 0; i < FRAME_HEIGHT; i++) {
    for (int j = 0; j < FRAME_WIDTH; j++) {
      frame[i][j] = snake[i][j] > 0;
    }
  }

  int i = fruit[0];
  int j = fruit[1];
  frame[i][j] = 1;

  hat.writeFrame(frame);
}

int smod(int a, int b) {
  // y = smod(a,b) returns y = a mod b, where y is positive.

  int y = a % b;
  if (y < 0) {
    y += b;
  }
  return y;
}
