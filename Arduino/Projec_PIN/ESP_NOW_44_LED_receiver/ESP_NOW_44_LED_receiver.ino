// ESPC32C3間通信(受信側, 4*4バージョン, LEDつき)
// ESP-NOWというプロトコルでのブロードキャスト通信
// 流れは以下の通り
  // setup()
    // シリアル通信開始
    // サーボモーターセット
    // LEDセット
    // ESP-NOW初期化
    // ESP-NOW送受信コールバック登録
  // loop()
    // ループしている旨を表示
    // 一応伸縮リセット
    // 5秒待機
  // OnDataSent
    // 空
  // OnDataRecv
    // 指令を受け取った旨とその中身を表示
      // リセット(キャリブレーション)
      // 指令と現在の伸縮状態からやることを考え実行
        // 待機
        // 縮める + LEDオフ
        // 伸ばす + LEDオン
// flow



// ESP-NOW関連
#include <esp_now.h>
#include <WiFi.h>
// サーボモーター関連
#include <ESP32Servo.h>
// モーターの向き正ならO(obverse), 逆ならR(reverse)
// #define motor1 4 // 実際はD2ピン O
// #define motor2 5 // 実際はD3ピン O
#define motor1 5 // 実際はD3ピン R
#define motor2 4 // 実際はD2ピン R
// LED関連 // LED_CHANGING
#define LED 7 // 実際はD5ピン // LED_CHANGING
// 指令関連
#define ME 12 // 自身への指令(固有の値)
#define UDTIME 3000 // 伸縮時間(UP DOWN TIME)
int timeLonger = 0; // 伸びた時間(ミリ秒, 縮むならマイナス)


// 送信コールバック
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  // 空
}
// 受信コールバック
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  if ( data_len == 1 ) { // キャリブレーション
    Serial.println("calibrating...");
    digitalWrite(LED, LOW); // LED_CHANGING
    shorter(10000); // 10秒縮めて
    longer(2000);   // 2秒伸ばす
    timeLonger = 0; // 伸びた時間リセット
    return; // 終了
  }
  // 指令の中身表示
  Serial.printf("Received data: %2d -> %2d\n", timeLonger/UDTIME, data[ME]);
  // 指令の長さになるための思考プロセス
  // 指令(こうなってほしい) - 今の伸び
  int difference = (int)data[ME] - timeLonger/UDTIME;
  switch ( difference ) {
    case  0: // 1秒待機
      Serial.println("motor: 0");
      delay(1000);
      break;
    case -1: // 3秒縮める
      Serial.println("motor: -");
      shorter(UDTIME);
      break;
    case  1: // 3秒伸ばす
      Serial.println("motor: +");
      longer(UDTIME);
      break;
    default:
      Serial.println("Something failed");
      break;
  }
}
// time ミリ秒縮める
void shorter(int time) {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  delay(time);
  timeLonger -= time;
  digitalWrite(motor1, LOW);
  digitalWrite(LED, LOW); // LED_CHANGING
}
// time ミリ秒伸ばす
void longer(int time) {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  digitalWrite(LED, HIGH); // LED_CHANGING
  delay(time);
  timeLonger += time;
  digitalWrite(motor2, LOW);
}
// 伸縮停止
void stay() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
}


void setup() {
  // シリアル通信
  Serial.begin(115200);
  Serial.printf("Hi! I'm pin %d! Motor is %c!\n",
                ME, ((motor1 == 4) ? 'O' : 'R'));
  // サーボモーター
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  // LED // LED_CHANGING
  pinMode(LED, OUTPUT); // LED_CHANGING

  // ESP-NOW初期化(WiFi部分要らない可能性はある)
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if ( esp_now_init() != ESP_OK ) ESP.restart();
  // ESP-NOWコールバック登録, 送信も受信も両方登録しないといけない
  esp_now_register_send_cb(OnDataSent); // 送信
  esp_now_register_recv_cb(OnDataRecv); // 受信
}

void loop() {
  Serial.println("---------Looping---------");
  delay(10000); // データ受け取りはloopの外で行われるため，delayは長くても問題ない
}





