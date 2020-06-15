#include <AFMotor.h>
#include <SoftwareSerial.h>
#define LeftTrig A0 //定義超音波感測器腳位
#define LeftEcho A1
#define RightTrig A2
#define RightEcho A3
#define FrontTrig A4
#define FrontEcho A5

#define sensor 9 //定義紅外線感測器腳位

#define RXD 2 //定義藍芽腳位
#define TXD 10

AF_Stepper left(256, 1); //宣告步進馬達腳位
AF_Stepper right(256, 2);

boolean sensorstate = 0; //宣告感應器狀態

boolean start = 0; //宣告開始變數

//定義前進函數
void forward(){
  left.onestep(BACKWARD, DOUBLE );
  right.onestep(FORWARD, DOUBLE );
}

//定義後退函數
void backward(){
  left.onestep(FORWARD, DOUBLE );
  right.onestep(BACKWARD, DOUBLE );
}

//定義右轉函數
void rightward(){
  left.onestep(BACKWARD, DOUBLE );
  right.onestep(BACKWARD, DOUBLE );
}

//定義左轉函數
void leftward(){
  left.onestep(FORWARD, DOUBLE );
  right.onestep(FORWARD, DOUBLE );
}

unsigned long GetDistance(int Trig, int Echo) {
  unsigned long distance=100;
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  unsigned long duration = pulseIn(Echo, HIGH);
  distance = duration/58;
  delay(100);
  return distance;
}


void setup() {
  Serial.begin(9600);         
  Serial.setTimeout(100); //每100毫秒接收一次
  Serial.println("test start!");
  pinMode(sensor, INPUT);
  pinMode(LeftTrig, OUTPUT);
  pinMode(LeftEcho, INPUT);
  pinMode(RightTrig, OUTPUT);
  pinMode(RightEcho, INPUT);
  pinMode(FrontTrig, OUTPUT);
  pinMode(FrontEcho, INPUT);
}

void loop() {
  if (start==1 )
  {

  }
  
  //在監控面顯示數據
    unsigned long distanceF = GetDistance(FrontTrig,FrontEcho);
    Serial.println(distanceF);
    delay(100);
    unsigned long distanceL = GetDistance(LeftTrig,LeftEcho);
    Serial.println(distanceL);
    unsigned long distanceR = GetDistance(RightTrig,RightEcho);
    Serial.println(distanceR);
    Serial.println("---------------");
    
    
  sensorstate = digitalRead(sensor);
 // if(sensorstate == 0)
 //  Serial.println("clear");
 // else
 //   Serial.println("line");
    
 // delay(500);
  
 // 藍芽傳輸部分
 // 用 @ 做為開始字元  @F L R換行
    bluetooth.print("@"); 
    bluetooth.print(distanceF);
    bluetooth.print(" "); 
    bluetooth.print(distanceL); 
    bluetooth.print(" ");   
    bluetooth.print(distanceR);
    bluetooth.write(13); 
  
  
}
