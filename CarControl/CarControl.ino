#include <SoftwareSerial.h>

#define LeftTrig 8 //定義超音波感測器腳位
#define LeftEcho 9
#define RightTrig 5
#define RightEcho 4
#define FrontTrig 7
#define FrontEcho 6

#define controlLeft 11 //接到A0
#define controlRight 10 //接到A1
 
#define sensor  //定義紅外線感測器腳位

#define RXD 2 //定義藍芽腳位
#define TXD 3
SoftwareSerial bluetooth(RXD, TXD);//宣布藍芽
//注意板子上RXD接3,TXD接2

boolean sensorstate = 0; //宣告感應器狀態

int start = 0; //宣告開始變數

int compare;//左右差距

char runstatus= 'X'; //給藍芽的狀態

unsigned long distanceF=0;//距離變數前左右
unsigned long distanceL=0;
unsigned long distanceR=0;

//取得超音波距離
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


//電腦監控
void stats(){
    Serial.print("df:");
    Serial.println(distanceF);
    Serial.print("dl:");
    Serial.println(distanceL);   
    Serial.print("dr:");
    Serial.println(distanceR);
    Serial.print("compare:");
    Serial.println(compare); 
    Serial.print("run way:");
    Serial.println(runstatus); 
    Serial.println("---------------"); 
}

//藍芽傳輸
void bt(){
   // 藍芽傳輸部分 未測試
 // 用 @ 做為開始字元  @ F L R potition 換行
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
//定義前進函數
void forward(){
  analogWrite(controlLeft, 213);
  analogWrite(controlRight, 213);
  runstatus='F';
}

//定義後退函數
void backward(){
  analogWrite(controlLeft, 43);
  analogWrite(controlRight,43);
  runstatus='B';
}

//定義右修正函數
void rf(){
  analogWrite(controlLeft, 127);
  analogWrite(controlRight,213);
  runstatus='r';
}

//定義左修正函數
void lf(){
  analogWrite(controlLeft, 213);
  analogWrite(controlRight,127);
  runstatus='l';
}

//定義左轉函數
void leftward(){
  analogWrite(controlLeft, 213);
  analogWrite(controlRight,43);
  runstatus='L';
}
//定義右轉函數
void Rightward(){
  analogWrite(controlLeft, 43);
  analogWrite(controlRight,213);
  runstatus='R';
}
//停止
void stopmove(){
  analogWrite(controlLeft, 127);
  analogWrite(controlRight,127);
  runstatus='X';
}

void runway(){//路線決定
       compare=distanceL-distanceR; //中間約左4右4 
     if(distanceF>=5){//如果前方不是死路
         if(compare>=-1&&compare<=1){//不需要修正就繼續前進(
              forward();
          }     
         else if(compare>=2&&compare<=12){//左大右小
             lf();    
         }
         else if(compare<=-2&&compare>=-12){//左小右大
             rf();
          }
      }
     else {//前面沒路
        if(compare>=13){//左邊有路
         leftward();
         }
         else if(compare<=-13){//右邊有路
         Rightward();
         }
         else{//死路
          stopmove();
         }
      }
}

void setup() {
  Serial.begin(9600);         
  Serial.setTimeout(100); //每100毫秒接收一次
  Serial.println("test start!");
  bluetooth.begin(9600);
  bluetooth.setTimeout(100);
  //pinMode(sensor, INPUT);
  pinMode(LeftTrig, OUTPUT);
  pinMode(LeftEcho, INPUT);
  pinMode(RightTrig, OUTPUT);
  pinMode(RightEcho, INPUT);
  pinMode(FrontTrig, OUTPUT);
  pinMode(FrontEcho, INPUT);
  pinMode(controlLeft, OUTPUT);
  pinMode(controlRight, OUTPUT);
}


void loop() {
  if(bluetooth.available()){
    int v=bluetooth.parseInt();
    if(v==1){
      start=1;
    }
    else if(v==9){
      start=0;
    }
  }
    
   if(start==1){
      //Serial.println(start);確認手機傳出的東西
      distanceF = GetDistance(FrontTrig,FrontEcho);
      distanceL = GetDistance(LeftTrig,LeftEcho);
      distanceR = GetDistance(RightTrig,RightEcho);
      
      runway();//路線決定
      stats();//電腦監控
      bt();//藍牙傳遞
      
      //預定座標系統
     // sensorstate = digitalRead(sensor);
    // if(sensorstate == 0)
    //  Serial.println("clear");
    // else
    //   Serial.println("line");
    
  }
}
