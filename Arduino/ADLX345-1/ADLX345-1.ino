//おまじない
//知りたい人向け:
//Wire.h は I2C 通信用のライブラリ
//ADXL345 は先にインストールしたライブラリ
#include <Wire.h>
#include <ADXL345.h>
//インスタンスの生成と変数の宣言
ADXL345 adxl;
int x, y, z;

void setup() {
  //シリアル通信の開始と ADXL オブジェクトの起動コマンド
  Serial.begin(9600);
  adxl.powerOn();
}

void loop() {
  //x,y,z に三軸の加速度を入れてもらうおまじない
  //またまた参考:
  //C 言語なので当然ポインタを渡せる (渡してる?)
  adxl.readXYZ(&x, &y, &z);
  //シリアル通信で出力
  Serial.print(x);
  Serial.print(',');
  Serial.print(y);
  Serial.print(',');
  Serial.println(z);
  delay(10);
}
