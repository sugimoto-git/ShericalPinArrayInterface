#include <Wire.h>
#include <PCA9685.h>            //PCA9685用ヘッダーファイル（秋月電子通商作成）

PCA9685 pwm1 = PCA9685(0x41);    //PCA9685のアドレス指定（アドレスジャンパ未接続時）
PCA9685 pwm2 = PCA9685(0x40);
//PCA9685 pwm3 = PCA9685(0x43);

#define SERVOMIN 102                //最小パルス幅 
#define SERVOMAX 492                //最大パルス幅

void setup() {
 pwm1.begin();                   //初期設定 (アドレス0x40用)
 pwm1.setPWMFreq(50);            //frequency of PWM for SG90 (アドレス0x40用)
 pwm2.begin();                   //初期設定 (アドレス0x40用)
 pwm2.setPWMFreq(50);            //frequency of PWM for SG90 (アドレス0x40用)
// pwm3.begin();                   //初期設定 (アドレス0x40用)
// pwm3.setPWMFreq(50);            //frequency of PWM for SG90 (アドレス0x40用)
}

int n=0,m=0;

void loop() {
  // PWM2を常に低に設定
  pwm2.setPWM(0, 0, 0);
  // PWM1を常に高に設定
  pwm1.setPWM(1, 0, SERVOMAX);

  delay(2000); // 1秒間待つ

    // PWM2を常に低に設定
  pwm2.setPWM(1, 0, 0);
  // PWM1を常に高に設定
  pwm1.setPWM(0, 0, SERVOMAX);

}



// void loop() {
//   n=0,m=0;
//   while (n<=180) {
//       pwm1.setPWM(0, 0, 200);
//       pwm2.setPWM(0, 0, 0);
//       delay(1000);
      
//     n=n+20 ;
//   }
//   // while (m<=180) {
//   //   for(int i=0; i<16; i++){
//   //     servo_write2(i,m);
//   //     delay(40);
//   //   }
//   //   m=m+20 ;
//   // }
// }

void servo_write1(int ch, int ang){ //動かすサーボチャンネルと角度を指定
  ang = map(ang, 0, 180, SERVOMIN, SERVOMAX); //角度（0～180）をPWMのパルス幅（102～492）に変換
  
  //delay(1);
}

//
void servo_write2(int ch, int ang){ //動かすサーボチャンネルと角度を指定
  ang = map(ang, 0, 180, SERVOMIN, SERVOMAX); //角度（0～180）をPWMのパルス幅（102～492）に変換
  pwm2.setPWM(ch, 0, ang);
  //delay(1);
}
//
//void servo_write3(int ch, int ang){ //動かすサーボチャンネルと角度を指定
//  ang = map(ang, 0, 180, SERVOMIN, SERVOMAX); //角度（0～180）をPWMのパルス幅（102～492）に変換
//  pwm3.setPWM(ch, 0, ang);
//  //delay(1);
//}
