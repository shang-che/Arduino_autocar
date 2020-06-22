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
  // 43      127      213
  //0-----341-----682-----1023
  //  170      511      852
  /*控制方
  前進:左213 右213
  後退:左43      右43
  左修正:左213  右127
  右修正:左127 右213
  左轉:左213 右43
  右轉:左43 右213
  停止:左127 右127
  */
  if(valueL > 682 && valueR > 682)
    forward();
  if(valueL < 341 && valueR < 341)
    backward();
  if(valueL > 682 && valueR < 341)
    leftward();
  if(valueL < 341 && valueR > 682)
    rightward();
  if(valueL > 682 && valueR < 682 && valueR > 341){
    forward();
    leftward();
  }
  if(valueL > 341 && valueL < 682 && valueR > 682){
    forward();
    rightward();
  }
}
