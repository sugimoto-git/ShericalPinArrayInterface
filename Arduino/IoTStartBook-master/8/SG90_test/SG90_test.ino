#include "SG90.h"

SG90 sg901;  // SG90のインスタンスを作る
SG90 sg902;  // SG90のインスタンスを作る

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;

  sg901.begin(26, 15);  // GPIO4、チャネル15で初期化
  sg902.begin(27, 15);
}

void loop() {
  for (int angle = -90; angle <= 90; angle += 90) {  // 角度を-90°から90°まで90°ずつ増やす
    sg901.write(angle);                               // SG90を動かす
    sg902.write(angle);
    delay(500);
  }
}
