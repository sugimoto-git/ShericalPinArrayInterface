/*
 * ESP32でSi7021を読み、Ambientに送り、DeepSleepする
 */
#include <WiFi.h>
#include <SparkFunHTU21D.h>
#include <Ambient.h>

#define TIME_TO_SLEEP 10 /* Time ESP32 will go to sleep (in seconds) */

const char* ssid = "aterm-5dfbc6-g";
const char* password = "288d57d4703de";
unsigned int channelId = 83465;       // AmbientのチャネルID
const char* writeKey = "fff849d1a22e46fd";  // ライトキー

WiFiClient client;
Ambient ambient;
HTU21D sensor;


#define BATTERY 39  // バッテリー電圧を測るピン

void setup() {
  unsigned long starttime = millis();
  Serial.begin(115200);
  while (!Serial)
    ;

  WiFi.begin(ssid, password);              // Wi-Fiネットワークに接続する
  while (WiFi.status() != WL_CONNECTED) {  // 接続したか調べる
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  // ローカルIPアドレスをプリントする

  ambient.begin(channelId, writeKey, &client);  // チャネルIDとライトキーを指定してAmbientの初期化

  sensor.begin();
  // if (!sensor.begin()) {
  //   Serial.println("Did not find HTU sensor!");
  //   while (true)
  //     ;
  // }
  pinMode(BATTERY, INPUT);  // バッテリー測定ピンをINPUTモードにする

  float temp = sensor.readTemperature();
  float humid = sensor.readHumidity();
  float vbat = (analogRead(BATTERY) / 4095.0 * 3.3 + 0.1132) * 2.0;
  Serial.printf("temp: %.2f, humid: %.2f, vbat: %.1f\r\n", temp, humid, vbat);

  ambient.set(1, temp);   // Ambientのデータ1に温度をセットする
  ambient.set(2, humid);  // データ2に湿度をセットする
  ambient.set(3, vbat);   // データ3にバッテリー電圧をセットする
  ambient.send();         // Ambientに送信する
  delay(10);
  // Deep sleepする時間を計算する
  uint64_t sleeptime = TIME_TO_SLEEP * 1000000 - (millis() - starttime) * 1000;
  esp_deep_sleep(sleeptime);  // DeepSleepモードに移行
                              // ここには戻らない
}

void loop() {
}
