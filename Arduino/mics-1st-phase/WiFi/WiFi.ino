#include <WiFi.h>
const char* ssid = "kaji-lab-Guest";
const char* password = "n8i!7fN9Cu62SZV";

void setup() {
  Serial.begin(115200);
  while (!Serial);
  WiFi.begin(ssid, password);              // Wi-Fiネットワークに接続する
  while (WiFi.status() != WL_CONNECTED) {  // 接続したか調べる
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  // ローカルIPアドレスをプリントする
}

void loop() {

}
