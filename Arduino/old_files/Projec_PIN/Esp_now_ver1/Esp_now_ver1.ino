#include <WiFi.h> // WiFI.h も必要らしいです。
#include <esp_now.h>

esp_now_peer_info_t slave;

// 送信コールバック 関数です。ここでは、MACアドレスのみ設定して、メッセージは loop 内で書きます。
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]); // デフォルト FFみたい。
}

// 受信コールバック //ここで、受信したデータを処理します。
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  char macStr[18];
  char msg[1];
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);



  sscanf((char*) data, "%d %d %d %d %d %d %d %f %d %d %d %d", // 送信データに合わせて取り出します。
         &sender, &tmt_cnt, &gps_time_hour, &gps_time_minute, &gps_time_second, &kirotei, &dist_to_xross, &gps_speed_kmph,
         &st0, &st1, &st2, &st3);

}

void setup() {
  // ESP-NOW初期化
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESPNow Init Success");
  } else {
    Serial.println("ESPNow Init Failed");
    ESP.restart();
  }

  // ESP-NOWコールバック登録
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);

  // マルチキャスト用Slave登録
  memset(&slave, 0, sizeof(slave));
  for (int i = 0; i < 6; ++i) {
    slave.peer_addr[i] = (uint8_t)0xff;
  }

  esp_err_t addStatus = esp_now_add_peer(&slave);
  if (addStatus == ESP_OK) {
    // Pair success
    Serial.println("Pair success");

}

void loop(){
  char buf[128];
  uint8_t bs[250];

  sprintf(buf, "%d %d %d %d %d %d %d %3.1f %d %d %d %d\0", // 一旦 char buf[] に貯めます。
              ME, tmt_cnt, gps_time_hour, gps_time_minute, gps_time_second, kirotei, dist_to_xross, gps_speed_kmph,
              st0, st1, st2, st3);

      memcpy(bs, buf, strlen(buf)); // 型変換が必用なのでメモリコピーします。
      esp_err_t result = esp_now_send(slave.peer_addr, bs, strlen(buf));

      //  Serial.print("Send Status: ");
      if (result == ESP_OK) {
        //    Serial.println("Success");
      } else if (result == ESP_ERR_ESPNOW_NOT_INIT) {
        Serial.println("ESPNOW not Init.");
      } else if (result == ESP_ERR_ESPNOW_ARG) {
        Serial.println("Invalid Argument");
      } else if (result == ESP_ERR_ESPNOW_INTERNAL) {
        Serial.println("Internal Error");
      } else if (result == ESP_ERR_ESPNOW_NO_MEM) {
        Serial.println("ESP_ERR_ESPNOW_NO_MEM");
      } else if (result == ESP_ERR_ESPNOW_NOT_FOUND) {
        Serial.println("Peer not found.");
      } else {
        Serial.println("Not sure what happened");
      }

}