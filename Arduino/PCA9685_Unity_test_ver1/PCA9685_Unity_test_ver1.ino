// PCA9685とESPシステムとUnity間の通信プログラム

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm0 = Adafruit_PWMServoDriver(0x40);

void setup() {
  Serial.begin(9600);
  pwm0.begin();
  pwm0.setPWMFreq(1000);
}

int n, i;
int flag = 0;
void loop() {
  if (flag == 0) {
    for (i = 0; i < 16; i += 2) {
      pwmA_0(i); //All
    }
    delay(1000);
    flag = 1;
  } else {
    for (i = 0; i < 16; i += 2) {
      pwmB_0(i); //All
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

