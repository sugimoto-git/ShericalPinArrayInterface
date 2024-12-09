// GPIO 25に接続されたLEDを定義
const int ledPin = 25;
unsigned long t;
int brightness = 0;

void setup() {
  pinMode(ledPin, OUTPUT);  // LEDピンを出力に設定
}

void loop() {
  t = millis();
  // 正弦波で明るさを変化させる。振幅127, オフセット127で0~255の範囲にする
  brightness = (int)(127.5 * sin(2.0 * PI * 1.0 * (float)t / 1000.0) + 127.5);
  analogWrite(ledPin, brightness);  // LEDの明るさを制御
}
