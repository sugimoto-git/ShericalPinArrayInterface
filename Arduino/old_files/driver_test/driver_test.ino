#include <Servo.h>

Servo servo7;
int up = 520;
int down = 480;
int A, B;
int preA, preB;
int count = 0;
int rotate = 0;

void setup() {
  servo7.attach(7, 1000, 2000);
  pinMode(A4, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  Serial.begin(2000000);
}

void loop() {
  A = digitalRead(3);
  B = digitalRead(4);
  servo7.write(110);
  // Serial.print(digitalRead(3));
  // Serial.print(",");
  // Serial.println(digitalRead(4));
  // servo7.write(180*analogRead(A4)/1000);
  // if (analogRead(A4) <= up && analogRead(A4) >= down) {
  //   servo7.write(90);
  //   rotate = 0;
  // } else if (analogRead(A4) >= up) {
  //   servo7.write(0);//正回転
  // } else if (analogRead(A4) <= down) {
  //   servo7.write(180);//負回転
  // }

  if(A != preA && B != preB){
    if(A == 1 && B == 0){
      count += 1;
    }
    if(A == 1 && B == 1){
      count += 1;
    }
    if(A == 0 && B == 1){
      count += 1;
    }
    if(A == 0 && B == 0){
      count += 1;
    }
  }
  if (count == 4) {
    rotate += 1;
    count = 0;
  } 
  
  Serial.print(analogRead(A4));//アナログスティックからの信号チェック
  Serial.print(",");
  Serial.print(count);//ポジション推移出力
  Serial.print(",");
  Serial.println(rotate);//回転数出力(多分)
  
  preA = A;
  preB = B;
}
