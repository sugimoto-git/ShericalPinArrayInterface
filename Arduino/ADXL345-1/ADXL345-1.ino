#include <Wire.h>     // I2Cライブラリ
#include <ADXL345.h>  // 加速度センサーライブラリ

ADXL345 adxl;  // 加速度センサーのオブジェクト生成

String inputString = "";      // 受信データを保持する変数
bool stringComplete = false;  // 受信を完了したかどうかのフラグ

int x, y, z;  // 加速度データの変数

void setup() {
  Serial.begin(57600);  // シリアル通信開始
  while (!Serial) {
  }

  Wire.begin();  // I2Cライブラリ開始

  adxl.powerOn();  // 加速度センサーオブジェクトの初期化

  pinMode(2, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}



void loop() {
  // ============================================
  // 加速度センサーの読み取りと送信
  // ============================================
  adxl.readXYZ(&x, &y, &z);  // x, y, z に加速度を代入

  int photoRef1 = analogRead(A0);  // フォトリフレクターの読み取り
  int photoRef2 = analogRead(A1);

  Serial.print(x);  // X軸
  Serial.print(",");
  Serial.print(y);  // Y軸
  Serial.print(",");
  Serial.print(z);  // Z軸
  Serial.print(",");
  Serial.print(photoRef1);  // フォトリフレクタ1
  Serial.print(",");
  Serial.print(photoRef2);  // フォトリフレクタ2
  Serial.println("");

  // ============================================
  // 受信したコマンドの処理
  // ============================================
  if (stringComplete) {       // 受信完了のフラグが立っていた場合の処理
    String is = inputString;  // 受信文字列のコピーを作る
    is.trim();                // 改行コードを削除

    if (is.equals("start")) {  // startを受信したら
      digitalWrite(2, HIGH);   // モーターを動かす
    }

    if (is.equals("stop")) {  // stopを受信したら
      digitalWrite(2, LOW);   // モーターを止める
    }

    inputString = "";        // 受信文字列をクリア
    stringComplete = false;  // 受信フラグをクリア
  }

  delay(10);
}
// ============================================
// シリアル通信の受信
// ============================================
void serialEvent() {  // シリアル通信を受信したイベント
  while (Serial.available()) {
    char inChar = (char)Serial.read();  // 受信データを文字列に変換する
    inputString += inChar;              // inputStringに付け足す
    if (inChar == '\n') {               // 改行コードを受け取ったら、受信完了フラグを立てる
      stringComplete = true;
    }
  }
}
