/* 
  Code 2
  Board:        Adafruit Motor/Stepper/Servo Shield for Arduino kit - v1.2 & 28BYJ-48 Stepper Motor & Arduino Uno IDE 1.8.5
  Connections:  See Fritzing in https://medium.com/jungletronics/28byj-48-stepper-motor-peak-rpm-658eae6afe2f 
  Power Supply: 5v .5A USB Power Cable right into 5.5mm Jack of Adafruit Board
  Max RPM:      15 RPM in FullDriver Mode
*/
#include <AFMotor.h>

// Connect a stepper motor with 64 steps per revolution (5.625 degree)
// to motor port #2 (M3 and M4)
AF_Stepper motor(64, 1);

boolean waveDrive = false;     // fire just a single phase at a time (Single coil)
boolean fullDrive = false;    // energize two phases at a time (Double coil)
boolean halfStep = false;     // combination of wave driving and full stepping (Interleave coil)
boolean microStep = true;
boolean bothDirection = false;

unsigned int speed = 2000;    // 2000make a modification for your test

/*  LAB RESULTS:
 *  Configurations:  (motor.setSpeed(XXX);)
 * (waveDrive)RPM_peak  350speed@5v resuts 12 rpm or  700rpm@12v resuts  20 rpm (both .5A) - > Single coil steps (2048 steps)
 * (fullDrive)RPM_peak  500speed@5v resuts 15 rpm or  700rpm@12v resuts  20 rpm (both .5A) - > Double coil steps (2048 steps) :)ideal 15 rpm 500speed@5v 
 * (halfStep) RPM_peak  400speed@5v resuts 12 rpm or  1000rpm@12v resuts 24 rpm (both .5A) - > Interleave coil steps  (4096 steps) Heat issue :/  
 * (microStep)RPM_peak 1000speed@5v resuts 10 rpm or  1000rpm@12v resuts 11 rpm (both .5A) - > Single coil steps (2048 steps) increasing the voltage makes no difference in speed  
 * 
*/

void setup() {
  Serial.begin(9600);         // set up Serial library at 9600 bps
  Serial.println("Stepper test!");

  motor.setSpeed(speed);

}

void loop() {

  unsigned long startTime;
  unsigned long endTime;
  unsigned long duration;
  int rpm;

  startTime = micros();


  if (waveDrive)
  {
    Serial.println("Single coil steps");
    motor.step(2048, FORWARD, SINGLE);
    if (bothDirection) motor.step(2048, BACKWARD, SINGLE);
  }

  if (fullDrive)
  {

    Serial.println("Double coil steps");
    motor.step(2048, FORWARD, DOUBLE);
    if (bothDirection) motor.step(2048, BACKWARD, DOUBLE);
  }

  if (halfStep)
  {
    Serial.println("Interleave coil steps");
    motor.step(2*2048, FORWARD, INTERLEAVE);
    if (bothDirection) motor.step(2*2048, BACKWARD, INTERLEAVE);
  }

  if (microStep)
  {
    Serial.println("Micrsostep steps");
    motor.step(2048, FORWARD, MICROSTEP);
    if (bothDirection) motor.step(2048, BACKWARD, MICROSTEP);
  }

}
