// ESP-NOW
#include <esp_now.h>
#include <WiFi.h>
// サーボモーターとシリアル通信
#include <ESP32Servo.h>
#define motor1 4
#define motor2 5

// 送信コールバック
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
}

// 受信コールバック
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println("got data");
  int inkey;
  for ( int i = 0 ; i < data_len ; i++ ) {
    // Serial
    inkey = data[i];
    if (inkey == 0) {
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, LOW);
      Serial.println("motor:0");
      delay(1000);
    } else if (inkey == 1) {
      digitalWrite(motor1, HIGH);
      digitalWrite(motor2, LOW);
      Serial.println("motor:+");
      delay(1000);
    } else if (inkey == 2) {
      digitalWrite(motor2, HIGH);
      digitalWrite(motor1, LOW);
      Serial.println("motor:-");
      delay(1000);
    } else { // 3以上
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, LOW);
      Serial.println("motor:0");
      delay(1000);
    }
  }
}


void setup() {
  // シリアル通信
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);

  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);

  // ESP-NOW初期化
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if (esp_now_init() != ESP_OK) ESP.restart();
  // ESP-NOWコールバック登録
  esp_now_register_send_cb(OnDataSent); // 送信
  esp_now_register_recv_cb(OnDataRecv); // 受信
}

void loop() {
  Serial.println("------Looping------");
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  delay(5000);
}



