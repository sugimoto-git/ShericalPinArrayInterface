#include <PCA9685.h> //PCA9685用ヘッダーファイル

PCA9685 pwm0 = PCA9685(0x40);    //PCA9685のアドレス指定
PCA9685 pwm1 = PCA9685(0x40);
PCA9685 pwm2 = PCA9685(0x40);

#define SERVOMIN 150            //最小パルス幅 
#define SERVOMAX 600            //最大パルス幅

void setup() {
 pwm0.begin();                   //初期設定 (アドレス0x40用)
 pwm0.setPWMFreq(50);            //PWM周期を50Hzに設定 (アドレス0x40用)
 pwm1.begin();                   //初期設定 (アドレス0x40用)
 pwm1.setPWMFreq(50);            //PWM周期を50Hzに設定 (アドレス0x40用)
 pwm2.begin();                   //初期設定 (アドレス0x40用)
 pwm2.setPWMFreq(50);            //PWM周期を50Hzに設定 (アドレス0x40用)
}

int n=0;

void loop() {  
  servo_write(0,n,0);
  // delay(1000);
  servo_write(0,n,1);
  // delay(1000);
  servo_write(0,n,2);
  delay(1000);
  n = n+59;
  if(n>180)n=0;
}

void servo_write(int ch, int ang,int num){ //動かすサーボチャンネルと角度を指定
  ang = map(ang, 0, 180, SERVOMIN, SERVOMAX); //角度（0～180）をPWMのパルス幅（150～500）に変換
  // switch (num) {
  //   case 0:
  //     pwm0.setPWM(ch, 0, ang);
  //     break;
  //   case 1:
  //     pwm1.setPWM(ch, 0, ang);
  //     break;
  //   case 2:
  //     pwm2.setPWM(ch, 0, ang);
  //     break;
  // }
  if(num == 0){
    pwm0.setPWM(ch, 0, ang);
  }else if(n == 1){
    pwm1.setPWM(ch, 0, ang);
  }else if(n == 2){
    pwm2.setPWM(ch, 0, ang);
  }
}

