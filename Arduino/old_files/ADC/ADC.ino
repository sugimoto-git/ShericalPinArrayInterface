#include <SPI.h>
#define SS 10
//--------------------
#include <Wire.h>
#include <PCA9685.h>           //PCA9685用ヘッダーファイル（秋月電子通商作成）
PCA9685 pwm1 = PCA9685(0x41);  //PCA9685のアドレス指定（アドレスジャンパ未接続時）
PCA9685 pwm2 = PCA9685(0x42);
//PCA9685 pwm3 = PCA9685(0x43);
int n = 0, m = 0;
#define SERVOMIN 102  //最小パルス幅
#define SERVOMAX 492  //最大パルス幅
//--------------------
int arr[8];
long previousMillis = 0;
long interval = 1000;


float Vref = 5.0;
SPISettings settings(1000000, MSBFIRST, SPI_MODE0);

void setup() {
  pinMode(SS, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  pwm1.begin();         //初期設定 (アドレス0x40用)
  pwm1.setPWMFreq(50);  //frequency of PWM for SG90 (アドレス0x40用)
  pwm2.begin();         //初期設定 (アドレス0x40用)
  pwm2.setPWMFreq(50);  //frequency of PWM for SG90 (アドレス0x40用)
}

int adcRead(byte ch) {  // 0 .. 7
  byte channelData = (ch + 8) << 4;
  // Serial.println(String(channelData,BIN));
  SPI.beginTransaction(settings);
  digitalWrite(SS, LOW);
  SPI.transfer(0b00000001);                   // Start bit 1
  byte highByte = SPI.transfer(channelData);  // singleEnd
  byte lowByte = SPI.transfer(0x00);          // dummy
  digitalWrite(SS, HIGH);
  SPI.endTransaction();
  return ((highByte & 0x03) << 8) + lowByte;
}

void servo_write1(int ch, int ang) {           //動かすサーボチャンネルと角度を指定
  ang = map(ang, 0, 180, SERVOMIN, SERVOMAX);  //角度（0～180）をPWMのパルス幅（102～492）に変換
  pwm1.setPWM(ch, 0, ang);
  //delay(1);
}
void servo_write2(int ch, int ang) {           //動かすサーボチャンネルと角度を指定
  ang = map(ang, 0, 180, SERVOMIN, SERVOMAX);  //角度（0～180）をPWMのパルス幅（102～492）に変換
  pwm2.setPWM(ch, 0, ang);
  //delay(1);
}

void loop() {
  //ADCの処理
  for (int i = 0; i < 8; i++) {
    Serial.print("ch" + String(i) + ":");
    Serial.print(arr[i] = adcRead(i));
    Serial.print(",");
  }
  Serial.println(" ");



  //ADCの値に基づいて出力
  n = 0, m = 0;

  if (arr[0] > 500) {
    servo_write1(0, 90);
  } else {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > interval) {
      servo_write1(0, 0);
    }
  }

  if (arr[6] > 500) {
    servo_write2(0, 90);
  } else {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > interval) {
      servo_write2(0, 0);
    }
  }

  delay(500);
}
