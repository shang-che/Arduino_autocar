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
  pinMode(A0, INPUT);//左輪輸入
  pinMode(A1, INPUT);//右輪輸入


}

void loop() {
  int valueL;//左馬達控制變數
  int valueR;//右馬達控制變數
  valueL = analogRead(A0);
  valueR = analogRead(A1);

  //0-----85-----170-----255
  // 區間1 | 區間2 |  區間3
  /*
  前進:左255 右255
  後退:左0      右0
  左修正:左255  右127
  右修正:左127 右255
  左轉:左255 右0
  右轉:左0 右255
  停止:左127 右127
  */
  if(valueL > 170 && valueR > 170 && valueL <= 255 && valueR <= 255)
    forward();
  if(valueL < 85 && valueR < 85 && valueL >= 0  && valueR >= 0)
    backward();
  if(valueL > 170 && valueR >= 0 && valueL <= 255 && valueR < 85)
    leftward();
  if(valueL >= 0 && valueR <= 255 && valueL < 85 && valueR > 170)
    rightward();
  if(valueL > 170 && valueR < 170 && valueL <= 255 && valueR > 85){
    forward();
    leftward();
  }
  if(valueL >= 0 && valueR < 170 && valueL < 85 && valueR > 85){
    forward();
    rightward();
  }
}
