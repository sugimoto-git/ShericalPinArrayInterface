#ifndef PCA_H
#define PCA_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class PCAController {
  public:
    PCAController(uint8_t address = 0x40);                    // コンストラクタ
    void begin();                                             // 初期化関数
    void setPWM(uint8_t channel, uint16_t on, uint16_t off);  // サーボ制御用の関数
    void setServoAngle(uint8_t channel, uint16_t angle);      // 角度を指定してサーボを動かす関数

  private:
    Adafruit_PWMServoDriver pwm;  // PCA9685のインスタンス
    int chanel[16];
};

#endif
