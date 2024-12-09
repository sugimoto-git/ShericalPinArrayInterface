#include <esp_now.h>
#include <stdio.h>
// #include <stdlib.h>
#include <WiFi.h>
esp_now_peer_info_t slave;

// 送信コールバック
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
}
// 受信コールバック
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
}


void setup() {
  // シリアル通信
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  // ESP-NOW初期化
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if ( esp_now_init() != ESP_OK ) ESP.restart();
  // マルチキャスト用Slave登録
  memset(&slave, 0, sizeof(slave));
  for ( int i = 0; i < 6; i++ ) slave.peer_addr[i] = (uint8_t)0xff;
  // // d4:f9:8d:03:39:a8
  // slave.peer_addr[0] = (uint8_t)0xd4;
  // slave.peer_addr[1] = (uint8_t)0xf9;
  // slave.peer_addr[2] = (uint8_t)0x8d;
  // slave.peer_addr[3] = (uint8_t)0x03;
  // slave.peer_addr[4] = (uint8_t)0x39;
  // slave.peer_addr[5] = (uint8_t)0xa8;
  // 84:fc:e6:00:8b:14
  // slave.peer_addr[0] = (uint8_t)0x84;
  // slave.peer_addr[1] = (uint8_t)0xfc;
  // slave.peer_addr[2] = (uint8_t)0xe6;
  // slave.peer_addr[3] = (uint8_t)0x00;
  // slave.peer_addr[4] = (uint8_t)0x8b;
  // slave.peer_addr[5] = (uint8_t)0x14;
  // esp_now_add_peer(&slave);
  esp_err_t addStatus = esp_now_add_peer(&slave);
  if (addStatus == ESP_OK) {
    // Pair success
    Serial.println("Pair success");
    Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X\n",
          slave.peer_addr[0], slave.peer_addr[1], slave.peer_addr[2],
          slave.peer_addr[3], slave.peer_addr[4], slave.peer_addr[5]);
    // char macStr[18];
    // snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
    //         slave.peer_addr[0], slave.peer_addr[1], slave.peer_addr[2],
    //         slave.peer_addr[3], slave.peer_addr[4], slave.peer_addr[5]);
  }
  // ESP-NOWコールバック登録, 送信も受信も両方登録しないといけない
  esp_now_register_send_cb(OnDataSent); // 送信
  esp_now_register_recv_cb(OnDataRecv); // 受信
}



void loop() {
  // ESP-NOW
  int n = 0;
  int os = 5; // order size
  char tmp; // order, 文字で一時的に受け取る
  uint8_t odrs[5]; // orders, メモリを追加確保で配列に
  while ( Serial.available() > 0 ) {
    tmp = Serial.read();
    odrs[n++] = ((tmp == 'a') ? 1 : (tmp == 'd') ? 2 : (tmp == 's') ? 0 : 3); // aなら順転の1, dなら逆転の2, sなら停止の0, それ以外3
    if ( n >= os ) break;
  }
  if ( n > 0 ) {
    while ( n < os ) odrs[n++] = 0; // 残りのデータを0で詰める
    esp_err_t result = esp_now_send(slave.peer_addr, odrs, os); // 送信
    printf("odrs: { %d, %d, %d, %d, %d }\n", odrs[0], odrs[1], odrs[2], odrs[3], odrs[4]);
    Serial.print("Send Status: ");
    if (result == ESP_OK) {
      Serial.println("Success");
    } else {
      Serial.println("It doesn't Success");
    }
  }
  delay(3000);
}




