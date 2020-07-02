#include <AFMotor.h>

AF_Stepper left(256, 1); //宣告步進馬達腳位
AF_Stepper right(256, 2);

int valueLA = 0;//左馬達控制變數
int valueLB = 0;//右馬達控制變數
int valueRA = 0;//右馬達控制變數
int valueRB = 0;//右馬達控制變數

char stats='X';
//A5 LOW 在做動作，無視上層指令
//A5 HIGH 接受上層指令
//定義前進函數
void forward(){
  //Serial.println("f");
  stats='f';
  for(int i = 0;i<50;i++){
    left.onestep(BACKWARD, DOUBLE );
    right.onestep(FORWARD, DOUBLE );
    delay(2);
  }
  //digitalWrite(A5, HIGH);
}

//接受上層指令
//定義右轉函數
void rightward(){
  if(stats!='R'){
    stats='R';
    digitalWrite(A5, LOW);
    Serial.println("startr");
    for(int i = 0;i<1400;i++){
      left.onestep(BACKWARD, DOUBLE );
      right.onestep(FORWARD, DOUBLE );
      delay(2);
    }
    for(int j = 0;j<900;j++){
      left.onestep(BACKWARD, DOUBLE );
      right.onestep(BACKWARD, DOUBLE );
      delay(2);
    }
    for(int k = 0;k<600;k++){
      left.onestep(BACKWARD, DOUBLE );
      right.onestep(FORWARD, DOUBLE );
      delay(2);
    }
     
    digitalWrite(A5, HIGH);
    Serial.println("endr");
  }
  else{
    valueLA=LOW;
    valueLB=LOW;
    valueRA=LOW;
    valueRB=LOW;
  }
}
void leftward(){//定義左轉函數
  if(stats!='L'){
    stats='L';
    digitalWrite(A5, LOW);
    Serial.println("startl");  
    for(int i = 0;i<1400;i++){
      left.onestep(BACKWARD, DOUBLE );
      right.onestep(FORWARD, DOUBLE );
      delay(2);
    }
   
    for(int j = 0;j<900;j++){
      left.onestep(FORWARD, DOUBLE );
      right.onestep(FORWARD, DOUBLE );
      delay(2);
    }
    for(int k = 0;k<700;k++){
      left.onestep(BACKWARD, DOUBLE );
      right.onestep(FORWARD, DOUBLE );
      delay(2);
    }
    digitalWrite(A5, HIGH);
    stopmove();
    Serial.println("endl"); 
  }
  else{
    valueLA=LOW;
    valueLB=LOW;
    valueRA=LOW;
    valueRB=LOW;
  }
}

//定義右修正函數
void rf(){
    stats='r';
    //digitalWrite(A5, LOW);
    Serial.println("rf");  
    left.onestep(BACKWARD, DOUBLE );
    right.onestep(FORWARD, DOUBLE );
    delay(2);
    left.onestep(BACKWARD, DOUBLE );
    right.onestep(BACKWARD, DOUBLE );
    delay(2);
    //digitalWrite(A5, HIGH);  
}

void lf(){
    //digitalWrite(A5, LOW); 
    Serial.println("lf"); 
    left.onestep(BACKWARD, DOUBLE );
    right.onestep(FORWARD, DOUBLE );
    delay(2);
    left.onestep(FORWARD, DOUBLE );
    right.onestep(FORWARD, DOUBLE );
    delay(2);
    //digitalWrite(A5, HIGH);    
}
void stopmove(){  
  Serial.println("stop");
}

void setup() {
  Serial.begin(9600);         
  Serial.setTimeout(100); //每100毫秒接收一次
  pinMode(A0, INPUT);//LA
  pinMode(A1, INPUT);//LB
  pinMode(A2, INPUT);//RA
  pinMode(A3, INPUT);//RB
  pinMode(A5, OUTPUT);//通訊上層
  digitalWrite(A5,HIGH);
  delay(5000);
}

void loop() {
  
  valueLA = digitalRead(A0);
  //delay(100);
  valueLB = digitalRead(A1);
 // delay(100);
  valueRA = digitalRead(A2);
 // delay(100);
  valueRB = digitalRead(A3);
 // delay(100);
  Serial.print("LA");
  Serial.println(valueLA);
  Serial.print("LB");
  Serial.println(valueLB);
  Serial.print("RA");
  Serial.println(valueRA);
  Serial.print("RB");
  Serial.println(valueRB);
  Serial.print("stats;");
  Serial.println(stats);
  //delay(300);
  //控制方
  //前進:1111
  //(沒有)後退:XXXX   
  //左修正:1000
  //右修正:0010
  //左轉:1100
  //右轉:0011
  //停止:0000

  if(valueLA==1&&valueLB==1){
    if(valueRA==1&&valueRB==1){//1111 
      forward();
    }
    else{//1100
      leftward();
    }
  }
  else if(valueLA==1&&valueLB==0){//1000
    lf();
  }
  else if(valueLA==0&&valueLB==0){
    if(valueRA==1&&valueRB==1){//0011
      rightward();
    }
    else if(valueRA==1&&valueRB==0){//0010
      rf();
    }
    else if(valueRA==0&&valueRB==0){//0000
      stopmove();
    }
  }

  Serial.println("---------------");

}
