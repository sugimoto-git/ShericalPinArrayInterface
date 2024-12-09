// DRV8835のピン定義
const int motorPin1 = 4;  // モーター制御ピン1（方向）
const int motorPin2 = 5; // モーター制御ピン2（方向）
const unsigned long extendTime = 20; // アクチュエーターが最大まで伸びる時間（ミリ秒）
const unsigned long retractTime = 20; // アクチュエーターが最小まで縮む時間（ミリ秒）

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(19200);
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

void loop() {
  // 最大まで伸ばす
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  delay(extendTime); // 指定時間動かす
  int i = analogRead(A1);
  stopMotor();
  // delay(200); // 動作確認用のディレイ

  // 最小まで縮める
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  delay(retractTime); // 指定時間動かす
  int j = analogRead(A1);
  stopMotor();

  Serial.print(i);
  Serial.print(" ");
  Serial.print(j);
  Serial.print(" ");
  Serial.println(1024);


  // delay(200); // 動作確認用のディレイ

  // if(0 < i && i < 850){
  //   Serial.println("touched!!");
  // }else{
  //   // Serial.println("")
  // }
  if(0 < j && j < 870){
    Serial.println("touched!!");
  }else{
    // Serial.println("")
  }

}


