#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

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
  pwm1.begin();           // Setups the I2C interface and hardware.
  pwm1.setPWMFreq(1000);  //Sets the PWM frequency for the entire chip, up to ~1.6 KHz.
  pwm2.begin();           // Setups the I2C interface and hardware.
  pwm2.setPWMFreq(1000);  //Sets the PWM frequency for the entire chip, up to ~1.6 KHz.

  pwm3.begin();           // Setups the I2C interface and hardware.
  pwm3.setPWMFreq(1000);  //Sets the PWM frequency for the entire chip, up to ~1.6 KHz.
  pwm4.begin();           // Setups the I2C interface and hardware.
  pwm4.setPWMFreq(1000);  //Sets the PWM frequency for the entire chip, up to ~1.6 KHz.

  pwm5.begin();           // Setups the I2C interface and hardware.
  pwm5.setPWMFreq(1000);  //Sets the PWM frequency for the entire chip, up to ~1.6 KHz.
  pwm6.begin();           // Setups the I2C interface and hardware.
  pwm6.setPWMFreq(1000);  //Sets the PWM frequency for the entire chip, up to ~1.6 KHz.

  pwm7.begin();           // Setups the I2C interface and hardware.
  pwm7.setPWMFreq(1000);  //Sets the PWM frequency for the entire chip, up to ~1.6 KHz.
  pwm8.begin();           // Setups the I2C interface and hardware.
  pwm8.setPWMFreq(1000);  //Sets the PWM frequency for the entire chip, up to ~1.6 KHz.

  pwm9.begin();           // Setups the I2C interface and hardware.
  pwm9.setPWMFreq(1000);  //Sets the PWM frequency for the entire chip, up to ~1.6 KHz.
  pwm10.begin();           // Setups the I2C interface and hardware.
  pwm10.setPWMFreq(1000);  //Sets the PWM frequency for the entire chip, up to ~1.6 KHz.
}

int n, i;
int flag = 0;
void loop() {
  if (flag == 0) {
    for (i = 0; i < 16; i += 2) {
      pwmA_1(i);
      pwmA_2(i);
    }
    delay(1000);
    flag = 1;
  } else {
    for (i = 0; i < 16; i += 2) {
      pwmB_1(i);
      pwmB_2(i);
    }
    delay(1000);
    flag = 0;
  }
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
