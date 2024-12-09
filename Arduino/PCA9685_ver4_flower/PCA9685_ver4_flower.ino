#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define pca1 5
#define pca2 6

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
  
  calibration();
}


int n, i,j;
int flag = 0;
void loop() {
  delay(500);
  pwmA(pca1,8);
  delay(800);
  pwmB(pca1,8);
  delay(800);

  pwmA(pca1,10);
  delay(800);
  pwmB(pca1,10);
  delay(800);

  pwmA(pca1,12);
  delay(800);
  pwmB(pca1,12);
  delay(800);

  pwmA(pca1,14);
  delay(800);
  pwmB(pca1,14);
  delay(800);



  pwmA(pca2,8);
  delay(800);
  pwmB(pca2,8);
  delay(800);

  pwmA(pca2,10);
  delay(800);
  pwmB(pca2,10);
  delay(800);

  pwmA(pca2,12);
  delay(800);
  pwmB(pca2,12);
  delay(800);

  pwmA(pca2,14);
  delay(800);
  pwmB(pca2,14);
  delay(800);


}


void pwmB(int driverIndex, int pin) {
  pwm[driverIndex].setPWM(pin, 4096, 0);
  pwm[driverIndex].setPWM(pin + 1, 0, 4096);
}

void pwmA(int driverIndex, int pin) {
  pwm[driverIndex].setPWM(pin, 0, 4096);
  pwm[driverIndex].setPWM(pin + 1, 4096, 0);
}

void calibration(){
  for (j = 0; j < 12; j++){
    for (i = 0; i < 16; i += 2) {
      pwmB(j,i);
    }
  }
  delay(1000);
  Serial.println("calibration done");
}
