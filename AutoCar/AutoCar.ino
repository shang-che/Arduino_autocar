#include <AFMotor.h>

AF_Stepper left(256, 1);
AF_Stepper right(256, 2);
int sensor = 9;
boolean sensorstate = 0;

int start = 0;

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
  pinMode(sensor, INPUT);
}

void loop() {
  sensorstate = digitalRead(sensor);
  if(sensorstate == 0)
    Serial.println("clear");
  else
    Serial.println("line");
  delay(500);
  if(Serial.available()) {
    start = Serial.parseInt();
  }
  if (start==1)
  {
      forward();
      delay(2);
  }
  
}
