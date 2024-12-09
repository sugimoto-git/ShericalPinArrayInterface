// ESPC32C3間通信(送信側, 4*4バージョン, LEDつき)
// ESP-NOWというプロトコルでのブロードキャスト通信
// 流れは以下の通り
  // setup()
    // シリアル通信開始
    // ESP-NOW初期化
    // slave用意・登録
    // ESP-NOW送受信コールバック登録
  // loop()
    // シリアルで文字受け取る
    // それに応じた指令を送信
  // OnDataSent および OnDataRecv
    // 空
// flow



// ESP-NOW関連
#include <esp_now.h>
#include <WiFi.h>
// #include <PCA9685.h>
esp_now_peer_info_t slave;
// 指令関連
uint8_t calibr[] = {0}; // calibration
uint8_t data_U[] = {1, 0, 0, 1,
                    1, 0, 0, 1,
                    1, 0, 0, 1,
                    0, 1, 1, 0}; // U
uint8_t data_P[] = {1, 1, 1, 0,
                    1, 0, 0, 1,
                    1, 1, 1, 0,
                    1, 0, 0, 0}; // P
uint8_t data_O[] = {0, 1, 1, 0,
                    1, 0, 0, 1,
                    1, 0, 0, 1,
                    0, 1, 1, 0}; // O
uint8_t data_C[] = {0, 1, 1, 0,
                    1, 0, 0, 0,
                    1, 0, 0, 0,
                    0, 1, 1, 0}; // C
int ds = 16; // data size

uint8_t data_A[] = {0, 1, 1, 0,
                    1, 0, 0, 1,
                    1, 1, 1, 1,
                    1, 0, 0, 1}; // A
// uint8_t data_C[] = {0, 1, 1, 0,
//                     1, 0, 0, 0,
//                     1, 0, 0, 0,
//                     0, 1, 1, 0}; // C(上で定義済み)
uint8_t data_D[] = {1, 1, 1, 0,
                    1, 0, 0, 1,
                    1, 0, 0, 1,
                    1, 1, 1, 0}; // D
uint8_t data_F[] = {1, 1, 1, 0,
                    1, 0, 0, 0,
                    1, 1, 1, 0,
                    1, 0, 0, 0}; // F
uint8_t data_H[] = {1, 0, 0, 1,
                    1, 0, 0, 1,
                    1, 1, 1, 1,
                    1, 0, 0, 1}; // H
uint8_t data_I[] = {1, 1, 1, 0,
                    0, 1, 0, 0,
                    0, 1, 0, 0,
                    1, 1, 1, 0}; // I
uint8_t data_J[] = {1, 1, 1, 1,
                    0, 0, 1, 0,
                    1, 0, 1, 0,
                    0, 1, 1, 0}; // J
uint8_t data_K[] = {1, 0, 0, 1,
                    1, 0, 1, 0,
                    1, 1, 0, 0,
                    1, 0, 1, 1}; // K
uint8_t data_L[] = {1, 0, 0, 0,
                    1, 0, 0, 0,
                    1, 0, 0, 1,
                    1, 1, 1, 1}; // L
uint8_t data_M[] = {1, 0, 0, 1,
                    1, 1, 1, 1,
                    1, 0, 0, 1,
                    1, 0, 0, 1}; // M
uint8_t data_N[] = {1, 0, 0, 1,
                    1, 1, 0, 1,
                    1, 0, 1, 1,
                    1, 0, 0, 1}; // N
// uint8_t data_O[] = {0, 1, 1, 0,
//                     1, 0, 0, 1,
//                     1, 0, 0, 1,
//                     0, 1, 1, 0}; // O(上で定義済み)
// uint8_t data_P[] = {1, 1, 1, 0,
//                     1, 0, 0, 1,
//                     1, 1, 1, 0,
//                     1, 0, 0, 0}; // P(上で定義済み)
uint8_t data_Q[] = {0, 1, 0, 0,
                    1, 0, 1, 0,
                    1, 0, 1, 0,
                    0, 1, 0, 1}; // Q
// 他の文字も作ってみる


// 送信コールバック
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  // 空
}
// 受信コールバック
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  // 空
}
// 送信データと結果の表示
void send(const uint8_t *data, int data_len) {
  if ( data_len == 1 ) { // キャリブレーション
    printf("calibration\n");
  } else if ( data_len == ds ) { // その他サイズdsのdata
    printf("%d %d %d %d\n",  data[0],  data[1],  data[2],  data[3]);
    printf("%d %d %d %d\n",  data[4],  data[5],  data[6],  data[7]);
    printf("%d %d %d %d\n",  data[8],  data[9], data[10], data[11]);
    printf("%d %d %d %d\n", data[12], data[13], data[14], data[15]);
  }
  esp_err_t result = esp_now_send(slave.peer_addr, data, data_len);
  Serial.print("Send Status: ");
  if (result == ESP_OK) {
    Serial.println("Success");
  } else {
    Serial.println("Failed");
  }
}


void setup() {
  // シリアル通信
  Serial.begin(115200);

  // ESP-NOW初期化(WiFi部分要らない可能性はある)
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if ( esp_now_init() != ESP_OK ) ESP.restart();
  // マルチキャスト用Slave登録
  memset(&slave, 0, sizeof(slave));
  for ( int i = 0; i < 6; i++ ) slave.peer_addr[i] = (uint8_t)0xff;
  if (esp_now_add_peer(&slave) == ESP_OK) Serial.println("Pair success");
  // ESP-NOWコールバック登録, 送信も受信も両方登録しないといけない
  esp_now_register_send_cb(OnDataSent); // 送信
  esp_now_register_recv_cb(OnDataRecv); // 受信
}

void loop() {
  if ( Serial.available() > 0 ) {
    switch ( Serial.read() ) { // 文字で一時的に受け取る
      case '1': send(data_U, ds); break; // U
      case '2': send(data_P, ds); break; // P
      case '3': send(data_O, ds); break; // O
      case '4': send(data_C, ds); break; // C
      // サイズ0のデータは送れないみたいなので1に
      case 'c': send(calibr,  1); break; // calibration
      default : break;
    }
  }
  delay(1000);
}





