#include <Ambient.h>
Ambient ambient;

#include <WiFi.h>
WiFiClient client;

#include "SparkFunHTU21D.h"
HTU21D sensor;  // Sparkfun HTU21Dオブジェクトを初期化する

#define TIME_TO_SLEEP 300

unsigned int channelId = 83465;             // AmbientのチャネルID
const char* writeKey = "fff849d1a22e46fd";  // ライトキー

void setup() {
  unsigned long starttime = millis();

  Serial.begin(115200);
  while (!Serial);

  WiFi.begin("aterm-5dfbc6-g", "288d57d4703de");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  ambient.begin(channelId, writeKey, &client);  // 'client'オブジェクトを指定
  sensor.begin();

  // ここから改変
  ambient.set(1, sensor.readTemperature());  // Ambientのデータ1に温度をセットする
  ambient.set(2, sensor.readHumidity());     // データ2に湿度をセットする
  ambient.send();                            // Ambientに送信する
  delay(10);
  uint64_t sleeptime = TIME_TO_SLEEP * 1000000 - (millis() - starttime) * 1000;
  
  esp_deep_sleep(sleeptime);
}

void loop() {
  // ambient.set(1, sensor.readTemperature());  // Ambientのデータ1に温度をセットする
  // ambient.set(2, sensor.readHumidity());     // データ2に湿度をセットする
  // ambient.send();                            // Ambientに送信する
  // delay(5 * 1000);
}
