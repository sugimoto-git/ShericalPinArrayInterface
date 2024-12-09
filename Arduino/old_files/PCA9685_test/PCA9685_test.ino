#include <Wire.h>
#include <PCA9685.h>            //PCA9685用ヘッダーファイル（秋月電子通商作成）

PCA9685 pwm = PCA9685(0x40);    //PCA9685のアドレス指定（アドレスジャンパ未接続時）

#define SERVOMIN 102                //最小パルス幅 
#define SERVOMAX 492                //最大パルス幅

void setup() {
 pwm.begin();                   //初期設定 (アドレス0x40用)
 pwm.setPWMFreq(50);            //frequency of PWM for SG90 (アドレス0x40用)
}

int n=0;

void loop() {
  n=0;
  while (n<=180) {
    for(int i=0; i<16; i++){
      servo_write(i,n);
      delay(40);
    }
    n=n+20 ;
  } 
}

void servo_write(int ch, int ang){ //動かすサーボチャンネルと角度を指定
  ang = map(ang, 0, 180, SERVOMIN, SERVOMAX); //角度（0～180）をPWMのパルス幅（102～492）に変換
  pwm.setPWM(ch, 0, ang);
  //delay(1);
}