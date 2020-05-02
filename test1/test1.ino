/*
 * https://solarbotics.com/product/33600/
 * 42BYGHW811 NEMA-17 Bipolar 48mm Stepper
 * Board Connector A is Black
 * Board Connector B is Green
 * Board Connector C is Red
 * Board Connector D is Blue
 * Voltage 3.1V
 * Current 2.5A
 * To wire for counter-clockwise rotation, swap the Red and Blue wires.
 *
 * https://www.allaboutcircuits.com/tools/voltage-divider-calculator/
 * Vin = 5 V
 * R1 = 220 Ohm
 * R2 = 330 Ohm
 *
 * https://www.pololu.com/product/1182
 */


// include stepper library
#include <Stepper.h>

const int stepsPerRevolution = 200;  // Nema17 motor has 200 steps in 360 degrees rotation

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);  // pins 8,9 go to PULL+ & PULL- , pins 10,11 go to DIR+ & DIR-

int tracknumber = 2;          // SET HOW MANY TRACKS YOU WANT UP AND BACK
int trackdistance = 20000;

int actualtracknumber = 0;    // current track number

int motiondirection = 2;      // set initial forward motor increments.
int forwardsincrement = 2;    // forward
int backwardsincrement = -2;  // backwards

int moves = 0;                // current move number
int goforit = 1;              // start or stop the move ?

int topspeed = 3201;          // TOP SPEED OF TRACKING
int bottomspeed = 1;          // start and end speed of RAMP up/down

int benspeed = 1;             // current speed

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  if (goforit == 1)
  {
    moveit();
  }
  else
  {
    donothing();
  }
}

void moveit() {

  int x = 1;
  for (int i = 50; i > -1; i = i + x )
  {
    if (i >= topspeed)
    {
      topspeedhold();    // hold top speed for trackdistance variable
      x = -1;            // switch direction at peak
    }
    if (i <= bottomspeed)
    {
      x = +1; // switch direction at troff
      moves++;
      actualtracknumber++;
    }
    int benspeed=i;
    myStepper.setSpeed(benspeed);
    myStepper.step(motiondirection);

    if (moves >=1) motiondirection = backwardsincrement; // switch direction 
    if (moves >=2) motiondirection = forwardsincrement , moves = 0;
    if (actualtracknumber >= tracknumber * 2 )  // when the motor has done forward and back the TRACKNUMBER amount set then back to void();
    {
      goforit = 0;
      return;
    }
  }
}

void topspeedhold() {  // hold top speed for trackdistance variable

  int f = 1;
  for (int f = 50; f > -1; f = f + 1 )
  {
    if (f >= trackdistance)
    {
      return;
    }
    myStepper.setSpeed(topspeed);
    myStepper.step(motiondirection);
  }
}

void donothing() {
  while(1);
}
