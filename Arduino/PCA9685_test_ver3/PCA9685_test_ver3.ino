#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm[11] = {
  Adafruit_PWMServoDriver(0x40),
  Adafruit_PWMServoDriver(0x41),
  Adafruit_PWMServoDriver(0x42),
  Adafruit_PWMServoDriver(0x43),
  Adafruit_PWMServoDriver(0x44),
  Adafruit_PWMServoDriver(0x45),
  Adafruit_PWMServoDriver(0x46),
  Adafruit_PWMServoDriver(0x47),
  Adafruit_PWMServoDriver(0x48),
  Adafruit_PWMServoDriver(0x49),
  Adafruit_PWMServoDriver(0x50)
};

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < 11; i++) {
    pwm[i].begin();
    pwm[i].setPWMFreq(1000);
  }
}

int n, i;
int flag = 0;
void loop() {
  if (flag == 0) {
    for (i = 0; i < 16; i += 2) {
      for (int j = 0; j < 11; j++) {
        pwmA(j, i);  // All PWM drivers
      }
    }
    delay(1000);
    flag = 1;
  } else {
    for (i = 0; i < 16; i += 2) {
      for (int j = 0; j < 11; j++) {
        pwmB(j, i);  // All PWM drivers
      }
    }
    delay(1000);
    flag = 0;
  }
}

void pwmB(int driverIndex, int pin) {
  pwm[driverIndex].setPWM(pin, 4096, 0);
  pwm[driverIndex].setPWM(pin + 1, 0, 4096);
}

void pwmA(int driverIndex, int pin) {
  pwm[driverIndex].setPWM(pin, 0, 4096);
  pwm[driverIndex].setPWM(pin + 1, 4096, 0);
}
