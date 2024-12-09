void setup() {
  // USB経由のシリアル通信を初期化
  Serial.begin(9600);
  while (!Serial) {
    delay(10); // シリアルポートが利用可能になるまで待機
  }
  Serial.println("ESP32 USB Serial Transmitter Initialized.");
}

void loop() {
  // 送信する整数値の配列
  int values[5] = {10, 20, 30, 40, 50};

  // 配列を文字列形式で送信（カンマ区切りで送信）
  for (int i = 0; i < 5; i++) {
    Serial.print(values[i]);
    if (i < 4) {
      Serial.print(","); // カンマ区切り
    }
  }
  Serial.println(); // 行末の送信

  delay(1000); // 1秒待機
}
