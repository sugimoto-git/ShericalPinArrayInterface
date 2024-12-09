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

// アクチュエーターの情報を管理するための構造体
struct Actuator {
  int driver; // どのPWMドライバを使うか
  int pin; // ピン番号
  unsigned long lastActionTime; // 最後にアクションが行われた時間
  bool isExtended; // 伸びているかどうか
};

const int NUM_ACTUATORS = 11; // アクチュエーターの数
const int EXTEND_TIME = 1800; // 伸び/縮むの時間 (1.8秒)
Actuator actuators[NUM_ACTUATORS];

void setup() {
  Serial.begin(9600);

  // 各PWMドライバの初期化
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

  // アクチュエーターの初期化
  for (int i = 0; i < NUM_ACTUATORS; i++) {
    actuators[i].driver = i; // 各PWMドライバを順番に割り当て
    actuators[i].pin = random(0, 16); // ランダムなピン番号を割り当て
    actuators[i].lastActionTime = millis();
    actuators[i].isExtended = false; // 初期状態は縮んでいる
  }
}

void loop() {
  unsigned long currentTime = millis();
  
  // 各アクチュエーターに対して状態をチェック
  for (int i = 0; i < NUM_ACTUATORS; i++) {
    if (currentTime - actuators[i].lastActionTime >= EXTEND_TIME) {
      // 伸びている場合は縮め、縮んでいる場合は伸ばす
      if (actuators[i].isExtended) {
        pwmB(actuators[i].driver, actuators[i].pin); // 縮める
      } else {
        pwmA(actuators[i].driver, actuators[i].pin); // 伸ばす
      }
      
      // 状態を反転させ、時間を更新
      actuators[i].isExtended = !actuators[i].isExtended;
      actuators[i].lastActionTime = currentTime;
    }
  }
}

// pwmA: アクチュエーターを伸ばす
void pwmA(int actuator, int pin) {
  switch (actuator) {
    case 0: pwm0.setPWM(pin, 0, 4096); pwm0.setPWM(pin + 1, 4096, 0); break;
    case 1: pwm1.setPWM(pin, 0, 4096); pwm1.setPWM(pin + 1, 4096, 0); break;
    case 2: pwm2.setPWM(pin, 0, 4096); pwm2.setPWM(pin + 1, 4096, 0); break;
    case 3: pwm3.setPWM(pin, 0, 4096); pwm3.setPWM(pin + 1, 4096, 0); break;
    case 4: pwm4.setPWM(pin, 0, 4096); pwm4.setPWM(pin + 1, 4096, 0); break;
    case 5: pwm5.setPWM(pin, 0, 4096); pwm5.setPWM(pin + 1, 4096, 0); break;
    case 6: pwm6.setPWM(pin, 0, 4096); pwm6.setPWM(pin + 1, 4096, 0); break;
    case 7: pwm7.setPWM(pin, 0, 4096); pwm7.setPWM(pin + 1, 4096, 0); break;
    case 8: pwm8.setPWM(pin, 0, 4096); pwm8.setPWM(pin + 1, 4096, 0); break;
    case 9: pwm9.setPWM(pin, 0, 4096); pwm9.setPWM(pin + 1, 4096, 0); break;
    case 10: pwm10.setPWM(pin, 0, 4096); pwm10.setPWM(pin + 1, 4096, 0); break;
  }
}

// pwmB: アクチュエーターを縮める
void pwmB(int actuator, int pin) {
  switch (actuator) {
    case 0: pwm0.setPWM(pin, 4096, 0); pwm0.setPWM(pin + 1, 0, 4096); break;
    case 1: pwm1.setPWM(pin, 4096, 0); pwm1.setPWM(pin + 1, 0, 4096); break;
    case 2: pwm2.setPWM(pin, 4096, 0); pwm2.setPWM(pin + 1, 0, 4096); break;
    case 3: pwm3.setPWM(pin, 4096, 0); pwm3.setPWM(pin + 1, 0, 4096); break;
    case 4: pwm4.setPWM(pin, 4096, 0); pwm4.setPWM(pin + 1, 0, 4096); break;
    case 5: pwm5.setPWM(pin, 4096, 0); pwm5.setPWM(pin + 1, 0, 4096); break;
    case 6: pwm6.setPWM(pin, 4096, 0); pwm6.setPWM(pin + 1, 0, 4096); break;
    case 7: pwm7.setPWM(pin, 4096, 0); pwm7.setPWM(pin + 1, 0, 4096); break;
    case 8: pwm8.setPWM(pin, 4096, 0); pwm8.setPWM(pin + 1, 0, 4096); break;
    case 9: pwm9.setPWM(pin, 4096, 0); pwm9.setPWM(pin + 1, 0, 4096); break;
    case 10: pwm10.setPWM(pin, 4096, 0); pwm10.setPWM(pin + 1, 0, 4096); break;
  }
}
