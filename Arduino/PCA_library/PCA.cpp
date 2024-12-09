#include "PCA.h"

// コンストラクタ：PCA9685のアドレスを指定してインスタンスを初期化
PCAController::PCAController(uint8_t address)
  : pwm(address) {
}

// 初期化関数：PCA9685を初期化
void PCAController::begin() {
  pwm.begin();
  pwm.setPWMFreq(60);     // PWM周波数を60Hzに設定（サーボモータに一般的な設定）
  Wire.setClock(400000);  // I2C通信速度を400kHzに設定
}

// サーボ制御用の関数：特定のチャンネルにPWM信号を設定
void PCAController::setPWM(uint8_t channel, uint16_t on, uint16_t off) {
  pwm.setPWM(channel, on, off);
}

// サーボの角度を設定する関数
void PCAController::setServoAngle(uint8_t channel, uint16_t angle) {
  // 角度をPWM値に変換
  uint16_t pulseLength = map(angle, 0, 180, 150, 600);
  pwm.setPWM(channel, 0, pulseLength);
}
