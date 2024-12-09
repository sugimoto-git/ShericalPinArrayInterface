#include <SPI.h>
#define SS 10

float Vref = 5.0 ;
SPISettings settings( 1000000 , MSBFIRST , SPI_MODE0 );

void setup() {
    pinMode(SS, OUTPUT);
    Serial.begin(9600);
    SPI.begin();
}

int adcRead(byte ch) { // 0 .. 7
    byte channelData = (ch+8 ) <<4;
// Serial.println(String(channelData,BIN));
    SPI.beginTransaction(settings);
        digitalWrite(SS, LOW);
            SPI.transfer(0b00000001); // Start bit 1
            byte highByte = SPI.transfer(channelData); // singleEnd
            byte lowByte = SPI.transfer(0x00); // dummy
        digitalWrite(SS, HIGH);
    SPI.endTransaction();
    return ((highByte & 0x03) << 8) + lowByte ;
}

void loop(){
  for(int i=0;i<8;i++){
    Serial.print("ch"+String(i)+":");
    Serial.print(adcRead(i));
    Serial.print(",");
  }
  Serial.println(" ");
  delay(500);
}


