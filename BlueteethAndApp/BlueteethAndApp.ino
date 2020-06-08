#include <SoftwareSerial.h>

const int rxpin = 2;
const int txpin = 3;
SoftwareSerial bluetooth(rxpin, txpin); 

int TrigPinF = 7;
int EchoPinF = 6;
//------int TrigPinL = X;
//------int EchoPinL = X;
//------int TrigPinR = X;
//------int EchoPinR = X;


unsigned long getDistance(int TrigPin,int EchoPin) {
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);

    // 讀取 EchoPin LOW->HIGH->LOW 的這段時間是多少 us
    unsigned long duration = pulseIn(EchoPin, HIGH);
    // 換算成距離
    unsigned long distance = duration/58;
    return distance;
}


void setup() {                
    pinMode(EchoPinF, INPUT);
    pinMode(TrigPinF, OUTPUT);
    //-----pinMode(EchoPinL, INPUT);
    //-----pinMode(TrigPinL, OUTPUT);
    //-----pinMode(EchoPinR, INPUT);
    //-----pinMode(TrigPinR, OUTPUT);
    Serial.begin(9600);
    bluetooth.begin(9600);
    bluetooth.setTimeout(100);
}
void loop() {
    unsigned long distanceF = getDistance(TrigPinF,EchoPinF);
    Serial.println(distanceF);
    //--------unsigned long distanceL = getDistance(TrigPinL,EchoPinL);
    //--------Serial.println(distanceL);
    //--------unsigned long distanceR = getDistance(TrigPinR,EchoPinR);
    //--------Serial.println(distanceR);
    
    // 用 @ 做為開始字元
    bluetooth.print("@"); 
    bluetooth.print(distanceF);
    bluetooth.write(13); 
    //--------bluetooth.print(distanceL);  
    //--------bluetooth.write("14");     
    //--------bluetooth.print(distanceR);
    //--------bluetooth.print("15");      
    
    // 用 ASCII碼 13(F),14(L),15(R) 做為結束字元
    delay(100);
}

/*---------------測試與設定藍芽用------------------
#include <SoftwareSerial.h>

const int rxpin = 2; // 接收 pin
const int txpin = 3; // 發送 pin
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
}
----------------------------------*/
