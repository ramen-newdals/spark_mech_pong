/*Given an initial position and a final position, drive two gantry stepper motors,
 * stepperX and stepperY, at 8 m/s to reach final position
 * 
 * Since I don't know how big our matrix can be, I made two versions:
 * 
 * 1) moveBallWithSteps assumes the parameters use a matrix with size
 * (number of steps to reach 60cm) X (number of steps to reach 85cm).
 * That matrix seems too big...
 * 
 * 2) moveBallWithCm assumes the parameters use a matrix with size 60 x 85 (cm)
 */
/*
 * Assumptions (I will modify the code if these assumptions aren't true anymore):
 * Ball moves at 8 m/s
 * Playing space is 60x85 cm
 * Stepper moves using full steps
 * Position (0,0) corresponds to *here*:
 * 
 *   [Player 1's paddle]
 * |                    |
 * |                    |
 * |                    |
 * |                    |
 * |                    |
 * |*here*              |
 *   [Player 2's paddle]
 * 
 */

 /*Questions:
  * ints vs floats: how precise should our calculations be?
  * How to reduce memory usage if we're using floats?
  * max int value is 32,767
  * Do we need to add in some decceleration/acceleration when changing directions quickly in case we
  * skip steps or motor cant change direction instantaneously at high speeds?
  * 
  * Need to check:
  * y axis stepper moves lslowly? see step version
  * test cm version. same speed as step version?
  * check and label which direction is fwd and bwd
  */

#include <AccelStepper.h>
#include <math.h>

/*******************GLOBAL VARIABLES**********************/
AccelStepper stepperX(AccelStepper::FULL4WIRE, 2, 3, 4, 5); //TODO: change based on which pins we're using
AccelStepper stepperY(AccelStepper::FULL4WIRE, 6, 7, 8, 9); //wire order: red, green, yellow, blue

//please feel free to condense the following unit conversions to save memory
//TODO: change gearBoxRatio and stepsPerRev to reflect the motor / gearbox we're using
int ballSpeed = 800; //in cm/s
int stepsPerRev = 200; //for Mercury SM-42BYG011-25
int gearBoxRatio = 1;
float stepsPerCm = stepsPerRev/(gearBoxRatio*11); //my pulley wheel's circumference is 11cm

//speed in steps/sec. use 330 (aka 100rpm) for now until we test with motor driver
int totalSpeed = 330; //ballSpeed*stepsPerCm;

/***************END OF GLOBAL VARIABLES******************/

//Drive stepperX and stepperY to reach desired position
//Assumes xEnd - xStart = number of steps needed to travel
void moveBallWithSteps(int xStart, int yStart, int xEnd, int yEnd) {

  float stepsX = xEnd - xStart;
  float stepsY = yEnd - yStart;
  int angle = atan2(stepsY, stepsX);
  int xSpeed = abs(totalSpeed*cos(angle));
  int ySpeed = abs(totalSpeed*sin(angle));

  stepperX.setSpeed(xSpeed);
  stepperY.setSpeed(ySpeed);

  //TO DO: check for valid start and end positions

  stepperX.move(stepsX);
  stepperY.move(stepsY);
}

//Version 2: using a 60x85 matrix
//assumes xEnd - xStart = number of cm needed to travel
void moveBallWithCm(int xStart, int yStart, int xEnd, int yEnd) {

  int cmX = xEnd - xStart;
  int cmY = yEnd - yStart;
  float stepsX = cmX*stepsPerCm;
  float stepsY = cmY*stepsPerCm;
  int angle = atan2(cmY, cmX);
  int xSpeed = abs(totalSpeed*cos(angle));
  int ySpeed = abs(totalSpeed*sin(angle));

  Serial.print("xSpeed: ");
  Serial.print(xSpeed);
  Serial.println();
  Serial.print("ySpeed: ");
  Serial.print(ySpeed);
  Serial.print("stepsX: ");
  Serial.print(stepsX);
  Serial.println();
  Serial.print("stepsY: ");
  Serial.print(stepsY);
  Serial.println();

  stepperX.setSpeed(xSpeed);
  stepperY.setSpeed(ySpeed);

  //TO DO: check for valid start and end positions

  stepperX.move(stepsX);
  stepperY.move(stepsY);
}

//for testing purposes only
void setup() {
  int xStart = 0;
  int yStart = 40;
  int xEnd = 40;
  int yEnd = 0;
  Serial.begin(9600);
  
  moveBallWithCm(xStart, yStart, xEnd, yEnd);

}

void loop () {
  stepperX.run();
  stepperY.run();
}
