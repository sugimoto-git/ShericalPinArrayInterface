// DRV8835のピン定義
const int motorPin1 = 4;  // モーター制御ピン1（方向）
const int motorPin2 = 5;  // モーター制御ピン2（方向）
const unsigned long extendTime = 10;  // アクチュエーターが最大まで伸びる時間（ミリ秒）
const unsigned long retractTime = 10; // アクチュエーターが最小まで縮む時間（ミリ秒）

// 異常値検出の設定
const int bufferSize = 20; // バッファサイズ（最近の20個のデータを保存）
int buffer[bufferSize];     // データバッファ
int bufferIndex = 0;        // バッファの現在の位置
bool bufferFilled = false;  // バッファが満たされたかどうか
const float thresholdMultiplier = 4.0;  // 標準偏差からの閾値の倍数

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(19200);

  // バッファを初期化
  for (int i = 0; i < bufferSize; i++) {
    buffer[i] = 0;
  }
}

void extendActuator() {
  // モーターを前進方向に回転させる
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  delay(extendTime); // 指定時間動かす
  stopMotor(); // モーター停止
}

void retractActuator() {
  // モーターを逆方向に回転させる
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  delay(retractTime); // 指定時間動かす
  stopMotor(); // モーター停止
}

void stopMotor() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}

// データの平均を計算
float calculateMean() {
  int sum = 0;
  int count = bufferFilled ? bufferSize : bufferIndex;
  for (int i = 0; i < count; i++) {
    sum += buffer[i];
  }
  return (float)sum / count;
}

// データの標準偏差を計算
float calculateStandardDeviation(float mean) {
  float sum = 0;
  int count = bufferFilled ? bufferSize : bufferIndex;
  for (int i = 0; i < count; i++) {
    sum += pow(buffer[i] - mean, 2);
  }
  return sqrt(sum / count);
}

// 異常値検出
bool detectAnomaly(int currentValue) {
  if (!bufferFilled && bufferIndex < 2) return false;  // データが少ないときは検出しない

  float mean = calculateMean();
  float stddev = calculateStandardDeviation(mean);

  // 現在の値が異常かどうかをチェック
  return abs(currentValue - mean) > thresholdMultiplier * stddev;
}

void loop() {
  // 最大まで伸ばす
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  delay(extendTime); // 指定時間動かす
  int i = analogRead(A1); // A1の値を取得
  stopMotor();

  // 最小まで縮める
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  delay(retractTime); // 指定時間動かす
  int j = analogRead(A1); // A1の値を取得
  stopMotor();

  // A1の値をバッファに追加
  buffer[bufferIndex] = j;
  bufferIndex = (bufferIndex + 1) % bufferSize;
  if (bufferIndex == 0) {
    bufferFilled = true;
  }

  // 異常値検出を行う
  bool anomalyDetected = detectAnomaly(j);

  // データと異常値検出の結果をシリアル出力
  // Serial.print("A1 Value: ");
  Serial.print(j);
  Serial.print(" ");
  Serial.print(1024);
  Serial.print(" ");
  Serial.println(0);
  if (anomalyDetected) {
    // Serial.println(" -> Anomaly detected!");
  } else {
    // Serial.println(" -> Normal.");
  }
}





