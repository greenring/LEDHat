// LEDHat - Arduino library for LED hat.
//
// This example implements a game of Snake on an LED baseball cap.
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
#define INCLUDE_GAMEPAD_MODULE

#include <DabbleESP32.h>

LEDHat hat;
bool frame[FRAME_HEIGHT][FRAME_WIDTH];

int frameDelay = 32;

int snake[FRAME_HEIGHT][FRAME_WIDTH];

int fruit[2];
int snakeHead[2];
int snakeLength;
int snakeDirection;
int gameStatus;

void initializeSnake();
void spawnFruit();
void turnSnake(int turn);
bool moveSnake();
bool isDead();
bool AI_canSeeFruit();
bool AI_willCrash(int direction);
void gameOver();
void updateFrame();
int smod(int a, int b);

// Setup.
void setup()
{
  Dabble.begin("LEDHat");
  hat.clear(); // Clear the LED display
  hat.frameZeros(frame);

  randomSeed(analogRead(0)); // Seed the random number generator with an analog reading for randomness
  hat.frameZeros(frame);     // Initialize LED display frame

  gameStatus = 0;    // Set the initial game status
  initializeSnake(); // Initialize the snake
  spawnFruit();      // Spawn the fruit on the LED display
}

// Loop.
void loop()
{
  int newDirection;
  int turnDirection;

  gameStatus = moveSnake(); // Move the snake and update the game status

  Dabble.processInput();

  if (gameStatus == 0)
  {
    delay(frameDelay); // Delay to control the speed of the game

    turnDirection = 0;
    if (snakeDirection == 1)
    {
      if (GamePad.isUpPressed())
      {
        turnDirection = -1;
      }
      else if (GamePad.isDownPressed())
      {
        turnDirection = 1;
      }
    }
    else if (snakeDirection == 2)
    {
      if (GamePad.isRightPressed())
      {
        turnDirection = -1;
      }
      else if (GamePad.isLeftPressed())
      {
        turnDirection = 1;
      }
    }
    else if (snakeDirection == 3)
    {
      if (GamePad.isDownPressed())
      {
        turnDirection = -1;
      }
      else if (GamePad.isUpPressed())
      {
        turnDirection = 1;
      }
    }
    else
    {
      if (GamePad.isRightPressed())
      {
        turnDirection = 1;
      }
      else if (GamePad.isLeftPressed())
      {
        turnDirection = -1;
      }
    }

    turnSnake(turnDirection); // Turn the snake accordingly
  }

  if (gameStatus == 1)
  {
    gameOver();        // Perform game over actions
    initializeSnake(); // Reset the snake for a new game
    spawnFruit();      // Spawn a new fruit on the LED display
    yield();           // Yield to other processes
  }
}

void initializeSnake()
{
  // Set all elements of the snake array to 0
  for (int i = 0; i < FRAME_HEIGHT; i++)
  {
    for (int j = 0; j < FRAME_WIDTH; j++)
    {
      snake[i][j] = 0;
    }
  }

  // Set the initial position of the snake head
  snakeHead[0] = 6;  // Set the vertical position of the snake head
  snakeHead[1] = 12; // Set the horizontal position of the snake head

  // Set the initial length and direction of the snake
  snakeLength = 1;    // Initialize the snake length to 1
  snakeDirection = 1; // Set the initial direction of the snake (1 = East)

  // Set the snake head element to 1 to represent the snake's presence in the array
  int i = snakeHead[0];
  int j = snakeHead[1];
  snake[i][j] = 1;
}

void spawnFruit()
{
  // Generate random coordinates for the fruit within the frame dimensions
  int i = random(FRAME_HEIGHT);
  int j = random(FRAME_WIDTH);

  // Ensure that the generated fruit coordinates do not overlap with the snake
  while (snake[i][j] > 0)
  {
    i = random(FRAME_HEIGHT);
    j = random(FRAME_WIDTH);
  }

  // Store the valid fruit coordinates
  fruit[0] = i; // Vertical coordinate of the fruit
  fruit[1] = j; // Horizontal coordinate of the fruit

  // Update the frame to reflect the new fruit position
  updateFrame();

  // Write the updated frame to the LED display
  hat.writeFrame(frame);
}

void turnSnake(int turn)
{
  // Update the snake's direction based on the turn value
  // `turn` value: -1 represents a left turn, +1 represents a right turn

  // Calculate the new direction by adding the turn value to the current direction
  snakeDirection = smod(snakeDirection + turn, 4);

  // The `smod()` function is used to ensure the resulting direction value stays within the valid range (0-3)
}

bool moveSnake()
{
  // Move the snake, handle collision and growth, update the LED frame, and display it.
  // This function calculates the new position for the snake's head, checks for collision,
  // handles growth when reaching the fruit, updates the snake's body, and updates the LED frame.
  // Returns true if the snake collided with itself (game over).

  // Calculate the new position for the snake's head based on the current direction
  if (snakeDirection % 2)
  {
    // Odd snake direction: Update the column position (horizontal movement)
    snakeHead[1] += 2 - snakeDirection;
  }
  else
  {
    // Even snake direction: Update the row position (vertical movement)
    snakeHead[0] += snakeDirection - 1;
  }

  // Wrap the snake's head position around the frame boundaries
  snakeHead[0] = smod(snakeHead[0], FRAME_HEIGHT);
  snakeHead[1] = smod(snakeHead[1], FRAME_WIDTH);

  // Check if the snake has collided with itself, indicating game over
  if (isDead())
  {
    return true;
  }

  // Check if the snake has reached the fruit
  bool hasFruit = snakeHead[0] == fruit[0] && snakeHead[1] == fruit[1];

  // Move the snake's body and handle growth if it has eaten the fruit
  for (int i = 0; i < FRAME_HEIGHT; i++)
  {
    for (int j = 0; j < FRAME_WIDTH; j++)
    {
      if (snake[i][j] == snakeLength)
      {
        // Snake's body segment: Increase its value (age) and potentially grow the snake
        snakeLength += hasFruit;
        snake[i][j] = hasFruit * snakeLength;
      }
      else if (snake[i][j] > 0)
      {
        // Snake's body segment: Increment its value (age) by 1
        snake[i][j]++;
      }
    }
  }

  // Update the snake's head position
  int i = snakeHead[0];
  int j = snakeHead[1];
  snake[i][j] = 1;

  // If the snake has eaten the fruit, spawn a new one
  if (hasFruit)
  {
    spawnFruit();
  }

  // Update the LED frame and display it on the LED hat
  updateFrame();
  hat.writeFrame(frame);

  return false;
}

bool isDead()
{
  // Check if the snake's head is overlapping with its body
  int i = snakeHead[0];
  int j = snakeHead[1];
  return snake[i][j] > 0;
}

void gameOver()
{
  int blinkDelay = 128; // Delay between each blink (in milliseconds)
  int endDelay = 256;
  int numBlinks = 10; // Number of times the LED frame will blink

  hat.blinkFrame(frame, blinkDelay, numBlinks); // Blink the LED frame for visual effect

  hat.clear();     // Clear the LED display
  delay(endDelay); // Delay before starting new game.
}

void updateFrame()
{
  // Set the LED frame value to true if the corresponding snake element is greater than 0
  for (int i = 0; i < FRAME_HEIGHT; i++)
  {
    for (int j = 0; j < FRAME_WIDTH; j++)
    {
      frame[i][j] = snake[i][j] > 0;
    }
  }

  int i = fruit[0];
  int j = fruit[1];
  frame[i][j] = 1; // Set the LED frame value at the fruit position to true
}

int smod(int a, int b)
{
  // y = smod(a,b) returns y = a mod b, where y is positive.

  int y = a % b;
  if (y < 0)
  {
    y += b; // Adjust y to be positive if it is negative
  }
  return y;
}