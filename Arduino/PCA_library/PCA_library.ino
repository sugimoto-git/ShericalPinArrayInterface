#include "PCA.h"  // PCAControllerクラスをインクルード

// PCA9685のI2Cアドレスを指定してPCAControllerのインスタンスを作成
// デフォルトのアドレスは0x40ですが、必要に応じて変更してください
PCAController pcaController(0x40);

void setup() {
  Serial.begin(9600);     // シリアル通信を初期化
  pcaController.begin();  // PCAControllerを初期化
}

void loop() {

  pcaController.setServoAngle(pca.chanel[0], angle);  // チャンネル0に接続されたサーボモータを制御
  delay(500);                             // 0.5秒待機
}
