#include <AFMotor.h>

AF_Stepper left(256, 1);
AF_Stepper right(256, 2);

int start = 0;
boolean bothDirection = true;

void forward(){
  left.onestep(BACKWARD, DOUBLE );
  right.onestep(FORWARD, DOUBLE );
}

void backward(){
  left.onestep(FORWARD, DOUBLE );
  right.onestep(BACKWARD, DOUBLE );
}

void setup() {
  Serial.begin(9600);         
  Serial.setTimeout(100);
  Serial.println("Stepper test!");
}

void loop() {

  if(Serial.available()) {
    start = Serial.parseInt();
  }
  
  if (start==1)
  {
      backward();
      delay(2);
  }
}
