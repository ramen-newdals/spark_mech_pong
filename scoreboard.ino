
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70);
}

void loop() {
  //define inputs
  //set initial score to 0 for both sides
  
  int playerOneScore = 0;
  int playerTwoScore = 0;

  int playerOneLeftDigit = 0;
  int playerOneRightDigit = 0;

  int playerTwoLeftDigit = 0;
  int playerTwoRightDigit = 0;
  

  matrix.drawColon(true); //draws colon in between the two scores to separate them

  //if player one scores a point:
  if (TRUE) {
    playerOneScore++; //player one's score goes up by one

    playerOneLeftDigit = playerOneScore/10; //takes number in the tens
    playerOneRightDigit = playerOneScore%10; //takes number in the ones

    matrix.writeDigitNum(0,playerOneLeftDigit); //writes value of playerOneLeftDigit to location 0
    matrix.writeDigitNum(1,playerOneRightDigit); //writes value of playerOneRightDigit to location 1

    matrix.writeDisplay();
  }

  if (TRUE) {
    playerTwoScore++;

    playerTwoLeftDigit = playerTwoScore/10; //takes number in the tens
    playerTwoRightDigit = playerTwoScore%10; //takes number in the ones

    matrix.writeDigitNum(3,playerTwoLeftDigit); //writes value of playerTwoLeftDigit to location 3
    matrix.writeDigitNum(4,playerTwoRightDigit); //writes value of playerTwoLeftDigit to location 4

    matrix.writeDisplay();
  }
    
  }

