// Author: Michael Garod
// Date Created: 5/20/18

// Portions of code taken from minimatrix16x8 example sketch
// https://github.com/adafruit/Adafruit_LED_Backpack/blob/master/examples/minimatrix16x8/minimatrix16x8.ino
// Alien animations courtesy of Adafruit
// https://learn.adafruit.com/trinket-slash-gemma-space-invader-pendant/source-code

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_8x16minimatrix matrix = Adafruit_8x16minimatrix();

void setup() {
  //while (!Serial);
  Serial.begin(9600);
  Serial.println("Begin Nametag Animation");
  
  matrix.begin(0x70);  // pass in the address
  matrix.setBrightness(8); // max 15
 }

static const uint8_t PROGMEM alien_bmps[][2][8] = {
  { // Alien 1
    { // Frame 1
      B00100100,
      B00100100,
      B01111110,
      B11011011,
      B11111111,
      B11111111,
      B10100101,
      B00100100
    },
    { // Frame 2
      B00100100,
      B10100101,
      B11111111,
      B11011011,
      B11111111,
      B01111110,
      B00100100,
      B01000010
    }
  },
  { // Alien 2
    { // Frame 1
      B00000000,
      B00111100,
      B01111110,
      B11011011,
      B11011011,
      B01111110,
      B00100100,
      B11000011
    },
    { // Frame 2
      B00111100,
      B01111110,
      B11011011,
      B11011011,
      B01111110,
      B00100100,
      B00100100,
      B00100100,
    }
  },
  { // Alien 3
    { // Frame 1
      B00011000,
      B00111100,
      B01111110,
      B11011011,
      B11111111,
      B00100100,
      B01011010,
      B01000010,
    },
    { // Frame 2
      B00011000,
      B00111100,
      B01111110,
      B11011011,
      B11111111,
      B00100100,
      B01011010,
    }
  }
};
  
static const uint8_t PROGMEM
  ghost_bmp[][8] = {
    {
      B01111110,
      B11111111,
      B10011001,
      B11011101,
      B10011001,
      B11111111,
      B10111011,
      B00110011
    },
    {
      B01111110,
      B11111111,
      B10011001,
      B11011101,
      B10011001,
      B11111111,
      B11011101,
      B10011001
    },
    {
      B01111110,
      B11111111,
      B10011001,
      B11011101,
      B10011001,
      B11111111,
      B11101110,
      B11001100
    },
    {
      B01111110,
      B11111111,
      B10011001,
      B11011101,
      B10011001,
      B11111111,
      B11011101,
      B10011001
    }
  },
  pacman_bmp[][8] = {
  {
    B01111100,
    B00111110,
    B00011111,
    B00001111,
    B00001111,
    B00011111,
    B00111110,
    B01111100
  },
  {
    B01111100,
    B11111110,
    B01111111,
    B00011111,
    B00011111,
    B01111111,
    B11111110,
    B01111100
  },
  {
    B01111100,
    B11111110,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111110,
    B01111100
  },
  {
    B01111100,
    B11111110,
    B01111111,
    B00011111,
    B00011111,
    B01111111,
    B11111110,
    B01111100
  }
};

// Ghost being chased by Pacman, both moving to the left
// Time: 46 outer loop x 4 frames x 40ms delay = 7.52 seconds
void drawPacmanAttack() {
  matrix.setRotation(1);
  for (int8_t x=16; x>=-30; x--) {
    matrix.setCursor(x,0);
    for (int8_t frame=0; frame<4; frame++) {
      matrix.clear();
      matrix.drawBitmap(x,    0,  ghost_bmp[frame], 8, 8, LED_ON); // Ghost on the left
      matrix.drawBitmap(x+10, 0, pacman_bmp[frame], 8, 8, LED_ON); // 10 spaces to the right
      matrix.writeDisplay();
      delay(40);
    }
  }
}

// Space invaders move to the left
// Time: 47 loops x 150ms = 7.05 seconds
void drawSpaceInvadersLeft() {
  matrix.setRotation(1);
  int8_t frameCounter = 0;
  for (int8_t x=16; x>=-30; x--) {
    matrix.setCursor(x,0);
    matrix.clear();
    matrix.drawBitmap(x,    0, alien_bmps[0][frameCounter], 8, 8, LED_ON);
    matrix.drawBitmap(x+10, 0, alien_bmps[1][frameCounter], 8, 8, LED_ON);
    matrix.drawBitmap(x+20, 0, alien_bmps[2][frameCounter], 8, 8, LED_ON);
    matrix.writeDisplay();
    frameCounter = (frameCounter + 1) % 2;
    delay(150);
  }
}

// Space invaders move to the right
// Time: 47 loops x 150ms = 7.05 seconds
void drawSpaceInvadersRight() {
  matrix.setRotation(1);
  int8_t frameCounter = 0;
  for (int8_t x=-8; x<=38; x++) {
    matrix.setCursor(x,0);
    matrix.clear();
    matrix.drawBitmap(x,    0, alien_bmps[0][frameCounter], 8, 8, LED_ON);
    matrix.drawBitmap(x-10, 0, alien_bmps[1][frameCounter], 8, 8, LED_ON);
    matrix.drawBitmap(x-20, 0, alien_bmps[2][frameCounter], 8, 8, LED_ON);
    matrix.writeDisplay();
    frameCounter = (frameCounter + 1) % 2;
    delay(150);
  }
}

// Streams of lines of varying length fall from top of the matrix.
// Time: 36 loops x 1ms = 2.34 seconds
void drawRain() {
  randomSeed(analogRead(0));
  int8_t rand_start[16], rand_len[16];
  for (int8_t i = 0; i < 16; i++) {
    rand_start[i] = random(-24, -12);
    rand_len[i]   = random(  3,  12);
  }
  
  matrix.setRotation(1);
  for (int8_t y=0; y<36; y++) {
    matrix.clear();
    for (int8_t line=0; line < 16; line++) {
      matrix.drawLine(line, rand_start[line] + y                 ,
                      line, rand_start[line] + y + rand_len[line], LED_ON);
    }
    matrix.writeDisplay();
    delay(65);
  }
}

// Write text to the screen. Letters move from the right side to the left.
// Time: 49 loops x 100ms = 4.9 Seconds
void drawScrollingText(char* name) {
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  matrix.setRotation(1);
  for (int8_t x=16; x>=-32; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print(name);
    matrix.writeDisplay();
    delay(100);
  }
}

void loop() {
  // Approx. Total Time to cycle: ~50 Seconds
  drawSpaceInvadersRight();
  drawRain();
  drawScrollingText("Mike");
  drawRain();
  drawPacmanAttack();
  drawRain();
  drawScrollingText("Mike");
  drawRain();
  drawSpaceInvadersLeft();
  drawRain();
  drawScrollingText("Mike");
  drawRain();
}
