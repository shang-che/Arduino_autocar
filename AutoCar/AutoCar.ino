#include <AFMotor.h>

// Connect a stepper motor with 64 steps per revolution (5.625 degree)
// to motor port #2 (M3 and M4) 
AF_Stepper left(256, 1);
AF_Stepper right(16, 2);

int microStep = 0;
boolean bothDirection = true;

//gunsigned int speed = 2000;    // 2000make a modification for your test

//unsigned long int ltime = 0, rtime = 0;

void setup() {
  Serial.begin(9600);         // set up Serial library at 9600 bps
  Serial.setTimeout(100);
  Serial.println("Stepper test!");
 // left.setSpeed(speed);
  //right.setSpeed(speed);
}
void loop() {
//  Serial.print("ms:");
//  Serial.println(microStep);
  if(Serial.available()) {
    microStep = Serial.parseInt();
  }
  
  if (microStep==1)
  {
//    Serial.println("Micrsostep steps");
    //unsigned long int currentTime = millis();
    //if(currentTime-ltime>1) {
      left.onestep(BACKWARD, DOUBLE );
      right.onestep(FORWARD, DOUBLE );
      delay(2);
    //  ltime = currentTime;
    //}
    //if(currentTime-rtime>1) {
    //  right.onestep(FORWARD, DOUBLE    );
    //  rtime = currentTime;
    //}
//    left.step(2048, FORWARD, MICROSTEP);
//    right.step(2048, FORWARD, MICROSTEP);
//    if (bothDirection){
//      left.step(2048, BACKWARD, MICROSTEP);
//      right.step(2048, BACKWARD, MICROSTEP);}
  }
}
