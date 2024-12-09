#define INPUT_PIN 2  // 2番ピン（アナログピンA2）

void setup() {
  Serial.begin(57600);         // シリアル通信を57600ボーで初期化
  pinMode(INPUT_PIN, INPUT);   // 入力ピンを設定
}

void loop() {
  int sensorValue = analogRead(INPUT_PIN);  // 2番ピンからアナログ値を取得
  Serial.print(sensorValue);             // シリアルモニタに値を送信
  Serial.print(",");
  Serial.print(4000);
  Serial.print(",");
  Serial.println(0);
}
