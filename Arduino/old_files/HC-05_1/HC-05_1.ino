#include<SoftwareSerial.h>
SoftwareSerial Bluetooth(10,11); //RX | TX
const int ledPin = 6;
 
void setup() {
  Bluetooth.begin(9600); //opens serial port, sets data rate to 9600 bps
  Serial.begin(9600); //opens serial port, sets data rate to 9600 bps
  Serial.println("Connect your device with 1234 as Paring Key\n");
  pinMode(ledPin, OUTPUT);
}
 
void loop() {
  if(Bluetooth.available()){
    int input = Bluetooth.read();
    if(input == 0){ //テキストデータとして送信するなら0を0x30に変える
      digitalWrite(ledPin, LOW);
    }
    else if(input == 1){ //テキストデータとして送信するなら1を0x31に変える
      digitalWrite(ledPin, HIGH);
    }
  }
}
