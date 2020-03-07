  /*
 * Assumptions:
 * Ball moves at 8 m/s
 * Stepper moves using full steps
 * Playing field is 60x85 cm
 * Position (0,0) corresponds to *here*:
 * 
 *   [Player 1's paddle]
 * |*here*              |
 * |                    |
 * |                    |
 * |                    |
 * |                    |
 * |                    |
 *   [Player 2's paddle]
 */

//I'm using AccelStepper instead of Stepper.h because stepper.h doesn't support multiple steppers
//AccelStepper documentation: https://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html#a748665c3962e66fbc0e9373eb14c69c1
#include <AccelStepper.h>
#include <math.h>

/*Given an initial position and a final position, drive two gantry stepper motors,
 * stepperX and stepperY to reach final position.
 * Returns true when ball has reached final position.
 * Note: Positive step values means stepper rotates clockwise (vice versa for negative step values)
 */
bool moveBall(unsigned int size[2], unsigned int xStart, unsigned int yStart, unsigned int xEnd, unsigned int yEnd) {

  //initialize steppers with pins
  AccelStepper stepperX(AccelStepper::FULL4WIRE, 2, 3, 4, 5); //TODO: change based on which pins we're using
  AccelStepper stepperY(AccelStepper::FULL4WIRE, 6, 7, 8, 9); //wire order: red, green, yellow, blue
  
  //calculate steps for X and Y axes given playing field size
  //assume playing field is 60x85 cm
  //TODO: change gearBoxRatio and stepsPerRev to reflect the motor / gearbox we're using
  float matrixPosToCmX = 60/size[0];
  float matrixPosToCmY = 85/size[1];
  int ballSpeed = 800; //in cm/s
  int stepsPerRev = 200; //for Mercury SM-42BYG011-25
  int gearBoxRatio = 1;
  float stepsPerCm = stepsPerRev/(gearBoxRatio*11); //my pulley wheel's circumference is 11cm
  
  float cmX = (xEnd - xStart)*matrixPosToCmX;
  float cmY = (yEnd - yStart)*matrixPosToCmY;
  float stepsX = cmX*stepsPerCm;
  float stepsY = cmY*stepsPerCm;

  //speed in steps/sec. use 330 (the fastest I can make it without motor stopping) for now until we test with motor driver
  int totalSpeed = 330; //ballSpeed*stepsPerCm;

  //compute components of xSpeed and ySpeed
  int xSpeed = 0;
  int ySpeed = 0;
  
  if(cmX == 0)
    ySpeed = totalSpeed;
  if(cmY == 0)
    xSpeed = totalSpeed;

  if((cmX != 0) && (cmY != 0)) {
    int angle = atan2(cmY, cmX);
    xSpeed = abs(totalSpeed*cos(angle));
    ySpeed = abs(totalSpeed*sin(angle));
  }
  /*
  Serial.print("xSpeed: ");
  Serial.print(xSpeed);
  Serial.println();
  Serial.print("ySpeed: ");
  Serial.print(ySpeed);
  Serial.println();
  Serial.print("stepsX: ");
  Serial.print(stepsX);
  Serial.println();
  Serial.print("stepsY: ");
  Serial.print(stepsY);
  Serial.println();
  */
  
  stepperX.setSpeed(xSpeed);
  stepperY.setSpeed(ySpeed);

  //TO DO: check for valid start and end positions

  stepperX.move(stepsX);
  stepperY.move(stepsY);

  //keep calling run() until motors have finished moving
  while((stepperX.distanceToGo() != 0) || (stepperY.distanceToGo() != 0)) {
    //Serial.print("X steps remaining: ");
    //Serial.print(stepperX.distanceToGo());
    //Serial.println();
    stepperX.run();
    stepperY.run();
  }
  return true;
}

//for testing purposes only
/*
void setup() {
  unsigned int xStart = 0;
  unsigned int yStart = 40;
  unsigned int xEnd = 40;
  unsigned int yEnd = 0;
  unsigned int size[2] = {60, 85}; 
  Serial.begin(9600);
  
  moveBall(size, xStart, yStart, xEnd, yEnd);
}

void loop() {
  
}
*/
