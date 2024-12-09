#include "SparkFunHTU21D.h"
HTU21D sensor;  // Sparkfun HTU21Dオブジェクトを初期化する
void setup() {
  Serial.begin(115200);
  while (!Serial);
  sensor.begin();
}
void loop() {
  Serial.print("Humidity: ");
  Serial.print(sensor.readHumidity(), 2);  // HTU21Dから湿度を読む
  // Serial.print("¥tTemperature: ");
  Serial.print(" ");
  Serial.println(sensor.readTemperature(), 2);  // HTU21Dから温度を読む
  delay(1000);
}
