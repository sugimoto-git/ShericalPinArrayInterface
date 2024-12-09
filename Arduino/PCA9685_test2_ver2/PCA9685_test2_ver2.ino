// PCA9685を用いて80本のピンアレイを同時に伸縮させるプログラム

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm0 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x42);
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x43);
Adafruit_PWMServoDriver pwm4 = Adafruit_PWMServoDriver(0x44);
Adafruit_PWMServoDriver pwm5 = Adafruit_PWMServoDriver(0x45);
Adafruit_PWMServoDriver pwm6 = Adafruit_PWMServoDriver(0x46);
Adafruit_PWMServoDriver pwm7 = Adafruit_PWMServoDriver(0x47);
Adafruit_PWMServoDriver pwm8 = Adafruit_PWMServoDriver(0x48);
Adafruit_PWMServoDriver pwm9 = Adafruit_PWMServoDriver(0x49);
Adafruit_PWMServoDriver pwm10 = Adafruit_PWMServoDriver(0x50);

void setup() {
  Serial.begin(9600);

  pwm0.begin();
  pwm0.setPWMFreq(1000);
  
  pwm1.begin();
  pwm1.setPWMFreq(1000);
  pwm2.begin();
  pwm2.setPWMFreq(1000);
  
  pwm3.begin();
  pwm3.setPWMFreq(1000);
  pwm4.begin();
  pwm4.setPWMFreq(1000);
  
  pwm5.begin();
  pwm5.setPWMFreq(1000);
  pwm6.begin();
  pwm6.setPWMFreq(1000);
  
  pwm7.begin();
  pwm7.setPWMFreq(1000);
  pwm8.begin();
  pwm8.setPWMFreq(1000);
  
  pwm9.begin();
  pwm9.setPWMFreq(1000);
  pwm10.begin();
  pwm10.setPWMFreq(1000);
}

int n, i;
int flag = 0;
void loop() {
  if (flag == 0) {
    for (i = 0; i < 16; i += 2) {
      pwmA_0(i); //All
      pwmA_1(i);
      pwmA_2(i);
      pwmA_3(i);
      pwmA_4(i);
      pwmA_5(i);
      pwmA_6(i);
      pwmA_7(i);
      pwmA_8(i);
      pwmA_9(i);
      pwmA_10(i);
    }
    delay(1000);
    flag = 1;
  } else {
    for (i = 0; i < 16; i += 2) {
      pwmB_0(i); //All
      pwmB_1(i);
      pwmB_2(i);
      pwmB_3(i);
      pwmB_4(i);
      pwmB_5(i);
      pwmB_6(i);
      pwmB_7(i);
      pwmB_8(i);
      pwmB_9(i);
      pwmB_10(i);
    }
    delay(1000);
    flag = 0;
  }
}

void pwmB_0(int pin) {
  pwm0.setPWM(pin, 4096, 0);
  pwm0.setPWM(pin + 1, 0, 4096);
}

void pwmA_0(int pin) {
  pwm0.setPWM(pin, 0, 4096);
  pwm0.setPWM(pin + 1, 4096, 0);
}


void pwmB_1(int pin) {
  pwm1.setPWM(pin, 4096, 0);
  pwm1.setPWM(pin + 1, 0, 4096);
}

void pwmA_1(int pin) {
  pwm1.setPWM(pin, 0, 4096);
  pwm1.setPWM(pin + 1, 4096, 0);
}

void pwmB_2(int pin) {
  pwm2.setPWM(pin, 4096, 0);
  pwm2.setPWM(pin + 1, 0, 4096);
}

void pwmA_2(int pin) {
  pwm2.setPWM(pin, 0, 4096);
  pwm2.setPWM(pin + 1, 4096, 0);
}

void pwmB_3(int pin) {
  pwm3.setPWM(pin, 4096, 0);
  pwm3.setPWM(pin + 1, 0, 4096);
}

void pwmA_3(int pin) {
  pwm3.setPWM(pin, 0, 4096);
  pwm3.setPWM(pin + 1, 4096, 0);
}

void pwmB_4(int pin) {
  pwm4.setPWM(pin, 4096, 0);
  pwm4.setPWM(pin + 1, 0, 4096);
}

void pwmA_4(int pin) {
  pwm4.setPWM(pin, 0, 4096);
  pwm4.setPWM(pin + 1, 4096, 0);
}

void pwmB_5(int pin) {
  pwm5.setPWM(pin, 4096, 0);
  pwm5.setPWM(pin + 1, 0, 4096);
}

void pwmA_5(int pin) {
  pwm5.setPWM(pin, 0, 4096);
  pwm5.setPWM(pin + 1, 4096, 0);
}

void pwmB_6(int pin) {
  pwm6.setPWM(pin, 4096, 0);
  pwm6.setPWM(pin + 1, 0, 4096);
}

void pwmA_6(int pin) {
  pwm6.setPWM(pin, 0, 4096);
  pwm6.setPWM(pin + 1, 4096, 0);
}

void pwmB_7(int pin) {
  pwm7.setPWM(pin, 4096, 0);
  pwm7.setPWM(pin + 1, 0, 4096);
}

void pwmA_7(int pin) {
  pwm7.setPWM(pin, 0, 4096);
  pwm7.setPWM(pin + 1, 4096, 0);
}

void pwmB_8(int pin) {
  pwm8.setPWM(pin, 4096, 0);
  pwm8.setPWM(pin + 1, 0, 4096);
}

void pwmA_8(int pin) {
  pwm8.setPWM(pin, 0, 4096);
  pwm8.setPWM(pin + 1, 4096, 0);
}

void pwmB_9(int pin) {
  pwm9.setPWM(pin, 4096, 0);
  pwm9.setPWM(pin + 1, 0, 4096);
}

void pwmA_9(int pin) {
  pwm9.setPWM(pin, 0, 4096);
  pwm9.setPWM(pin + 1, 4096, 0);
}

void pwmB_10(int pin) {
  pwm10.setPWM(pin, 4096, 0);
  pwm10.setPWM(pin + 1, 0, 4096);
}

void pwmA_10(int pin) {
  pwm10.setPWM(pin, 0, 4096);
  pwm10.setPWM(pin + 1, 4096, 0);
}
