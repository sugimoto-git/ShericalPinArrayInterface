#define MCP9700AE 25

void setup() {
  Serial.begin(115200);  // シリアルの初期化
  while (!Serial);       // シリアル回線が利用可能になるまで待つ
  pinMode(MCP9700AE, INPUT);  // MCP9700AEピンのモードを入力モードにする
}

void loop() {
  int e = analogRead(MCP9700AE);          // MCP9700AEピンの値を読む
  float Vout = e / 4095.0 * 3.3 + 0.113;  // 補正式を使って電圧を補正する
  float temp = (Vout - 0.5) / 0.01;       // 電圧から温度に変換する
  Serial.println(temp);                   // 温度をシリアルに出力する
  delay(1000);                            // 1秒待つ
}