#include <IRremote.h>

#define IR_LED_PIN 3  // 赤外線LEDを接続するピン

void setup() {
  Serial.begin(9600);
  IrSender.begin(IR_LED_PIN); // 初期化（必要な引数はピン番号だけ）
}

void loop() {
  // NECフォーマットで0x807C5AA5（例のコード）を送信
  IrSender.sendNEC(0x807C5AA5, 32); // NECフォーマット送信
  delay(2000);  // 2秒待機
  Serial.println("hello");
}
