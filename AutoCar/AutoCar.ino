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
SoftwareSerial bluetooth(RXD, TXD);//宣布藍芽

boolean sensorstate = 0; //宣告感應器狀態

int start = 0; //宣告開始變數

char runstatus= 'X'; //給藍芽的狀態

unsigned long distanceF=0;//距離變數前左右
unsigned long distanceL=0;
unsigned long distanceR=0;

int location[4][4];//宣告座標

int Left = 11;//左右輪輸出pin
int Right =10;//

void add(){
  
  }

//取得超音波距離函數
unsigned long GetDistance(int Trig, int Echo) {
  unsigned long distance=100;
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  unsigned long duration = pulseIn(Echo, HIGH, 1000);
  Serial.println(duration);
  distance = duration/58;
  delay(10);
  return distance;
}

//監控
void stats(){
    distanceF = GetDistance(FrontTrig,FrontEcho);
    Serial.print("df:");
    Serial.println(distanceF);
    distanceL = GetDistance(LeftTrig,LeftEcho);
    Serial.print("dl:");
    Serial.println(distanceL);
    distanceR = GetDistance(RightTrig,RightEcho);
    Serial.print("dr:");
    Serial.println(distanceR);
}

//藍芽傳輸
void bt(){
   // 藍芽傳輸部分 未測試
 // 用 @ 做為開始字元  @ F L R potition x y 換行
    bluetooth.print("@"); 
    bluetooth.print(distanceF);
    bluetooth.print(" "); 
    bluetooth.print(distanceL); 
    bluetooth.print(" ");   
    bluetooth.print(distanceR);
    bluetooth.print(" ");
    bluetooth.print(runstatus);
    bluetooth.write(13); 
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
  pinMode(Left, OUTPUT);//左輪輸出
  pinMode(Right, OUTPUT);//右輪輸出
}


void loop() {
  stats();
  
  //預定座標系統
  //sensorstate = digitalRead(sensor);
  //if(sensorstate == 1){
  //  add();
  //  }
//  if(sensorstate == 0)
//   Serial.println("clear");
//  else
//    Serial.println("line");
   
  int compare=distanceL-distanceR; //中間約左4右4
  Serial.print("comapre test:");
  Serial.println(compare);
  Serial.print("run way:");
  Serial.println(runstatus);  
  if(distanceF>=5){//如果前方不是死路
      if(compare>=-3&&compare<=3){//不需要修正就繼續前進(
        analogWrite(Left, 255);
        analogWrite(Right, 255);
      }     
      else if(compare>=2&&compare<=12){//左大右小
        analogWrite(Left, 255);
        analogWrite(Right, 127);     
      }
      else if(compare<=-2&&compare>=-12){//左小右大
        analogWrite(Left, 127);
        analogWrite(Right, 255);
      }
  }
  else{
     runstatus='X';
  }

  bt();
  Serial.println("---------------"); */
}

/*
//藍芽測試
#include <SoftwareSerial.h>
const int rxpin = 2; // 接收 pin
const int txpin = 10; // 發送 pin
SoftwareSerial bluetooth(rxpin, txpin); // 建立虛擬序列埠
void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600); // 初始化藍芽序列埠
}
void loop() {
  if (bluetooth.available())
  {
    char c = bluetooth.read();
    Serial.print(c);
  }
  if (Serial.available())
  {
    char c = Serial.read();
    bluetooth.print(c);
  }
}*/
