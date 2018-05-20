// Author: Michael Garod
// Date Created: 5/20/18

// Portions of code taken from minimatrix16x8 example sketch
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

static const uint8_t PROGMEM
  alien11_bmp[] = { // Alien #1, Frame #1
    B00100100,
    B00100100,
    B01111110,
    B11011011,
    B11111111,
    B11111111,
    B10100101,
    B00100100
  },
  alien12_bmp[] = { // Alien #1, Frame #2
    B00100100,
    B10100101,
    B11111111,
    B11011011,
    B11111111,
    B01111110,
    B00100100,
    B01000010
  },
  alien21_bmp[] = { // Alien #2, Frame #1
    B00000000,
    B00111100,
    B01111110,
    B11011011,
    B11011011,
    B01111110,
    B00100100,
    B11000011
  },
  alien22_bmp[] = { // Alien #2, Frame #2
    B00111100,
    B01111110,
    B11011011,
    B11011011,
    B01111110,
    B00100100,
    B00100100,
    B00100100,
  },
  alien31_bmp[] = { // Alien #3, Frame #1
    B00011000,
    B00111100,
    B01111110,
    B11011011,
    B11111111,
    B00100100,
    B01011010,
    B01000010,
  },
  alien32_bmp[] = { // Alien #3, Frame #2
    B00011000,
    B00111100,
    B01111110,
    B11011011,
    B11111111,
    B00100100,
    B01011010,
  };

void drawSpaceInvadersLeft() {
  for (int8_t x=16; x>=-30; x--) {
    matrix.setCursor(x,0);
    if (x % 2) {
      matrix.clear();
      matrix.setRotation(1);
      matrix.drawBitmap(x, 0, alien11_bmp, 8, 8, LED_ON);
      matrix.drawBitmap(x+10, 0, alien21_bmp, 8, 8, LED_ON);
      matrix.drawBitmap(x+20, 0, alien31_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      delay(150);
    } else {
      matrix.clear();
      matrix.drawBitmap(x, 0, alien12_bmp, 8, 8, LED_ON);
      matrix.drawBitmap(x+10, 0, alien22_bmp, 8, 8, LED_ON);
      matrix.drawBitmap(x+20, 0, alien32_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      delay(150);
    }
  }
}

void drawSpaceInvadersRight() {
  for (int8_t x=-8; x<=38; x++) {
    matrix.setCursor(x,0);
    if (x % 2) {
      matrix.clear();
      matrix.setRotation(1);
      matrix.drawBitmap(x, 0, alien11_bmp, 8, 8, LED_ON);
      matrix.drawBitmap(x-10, 0, alien21_bmp, 8, 8, LED_ON);
      matrix.drawBitmap(x-20, 0, alien31_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      delay(150);
    } else {
      matrix.clear();
      matrix.drawBitmap(x, 0, alien12_bmp, 8, 8, LED_ON);
      matrix.drawBitmap(x-10, 0, alien22_bmp, 8, 8, LED_ON);
      matrix.drawBitmap(x-20, 0, alien32_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      delay(150);
    }
  }
}

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
    delay(100);
  }
}

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
  drawSpaceInvadersRight();
  drawRain();
  drawScrollingText("Mike");
  drawSpaceInvadersLeft();
  drawRain();
}
