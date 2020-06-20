#include <AFMotor.h>

AF_Stepper left(256, 1); //宣告步進馬達腳位
AF_Stepper right(256, 2);

//定義前進函數
void forward(){
  left.onestep(BACKWARD, DOUBLE );
  right.onestep(FORWARD, DOUBLE );
  delay(2);
}

//定義後退函數
void backward(){
  left.onestep(FORWARD, DOUBLE );
  right.onestep(BACKWARD, DOUBLE );
  delay(2);
}

//定義右轉函數
void rightward(){
  left.onestep(BACKWARD, DOUBLE );
  right.onestep(BACKWARD, DOUBLE );
  delay(2);
}

//定義左轉函數
void leftward(){
  left.onestep(FORWARD, DOUBLE );
  right.onestep(FORWARD, DOUBLE );
  delay(2);
}
void setup() {
  Serial.begin(9600);         
  Serial.setTimeout(100); //每100毫秒接收一次

}

void loop() {
  
}
