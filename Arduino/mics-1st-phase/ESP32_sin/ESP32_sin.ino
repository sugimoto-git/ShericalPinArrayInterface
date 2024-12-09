// GPIO 22に接続されたブザーを定義
const int buzzerPin = 22;
unsigned long t;
int outputValue = 128;

void setup() {
  // チャンネル0に60kHzの周波数でPWMを設定
  ledcSetup(0, 60000, 8);        // チャンネル0、60kHz、8ビット分解能
  ledcAttachPin(buzzerPin, 0);   // ピンをチャンネル0に接続
}

void loop() {
  t = micros();
  // サイン波の周波数成分を5000に設定して周期を早くする
  outputValue = (int)(128.0 * sin(2.0 * PI * 5000.0 * (float)t / 1000000.0) + 127.0);
  ledcWrite(0, outputValue); // チャンネル0にデューティサイクルを出力
}
