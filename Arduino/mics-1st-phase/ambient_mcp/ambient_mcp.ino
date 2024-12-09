#include <SPI.h>
#include <Ambient.h>

#define SPI1_CLK 18
#define SPI1_MISO 19
#define SPI1_MOSI 23
#define SPI1_SS 5

#define TIMER0 0
#define SAMPLE_PERIOD 1  // サンプリング間隔(ミリ秒)
#define SAMPLE_SIZE 100  // 1ms x 100 = 100ms
#define PERIOD 5         // 測定間隔(秒)

// set SPI freqency 1MHz
#define SPI_CLK 1000000

const char* ssid = "aterm-5dfbc6-g";
const char* password = "288d57d4703de";
unsigned int channelId = 85422;             // AmbientのチャネルID
const char* writeKey = "ae188cda567023c1";  // ライトキー

hw_timer_t* samplingTimer = NULL;
volatile int t0flag;

//uninitalised pointers to SPI objects
SPIClass SPI1(HSPI);
SPISettings spiSettings = SPISettings(SPI_CLK, SPI_MSBFIRST, SPI_MODE1);

WiFiClient client;
Ambient ambient;

void IRAM_ATTR onTimer0() {  // タイマ割込み関数
  t0flag = 1;
}

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;

  SPI1.begin(SPI1_CLK, SPI1_MISO, SPI1_MOSI, SPI1_SS);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("WiFi connected: ");
  Serial.println(WiFi.localIP());

  ambient.begin(channelId, writeKey, &client);  // チャネルIDとライトキーを指定してAmbientの初期化

  pinMode(SPI1_SS, OUTPUT);
  pinMode(SPI1_CLK, OUTPUT);
  pinMode(SPI1_MISO, INPUT);
  pinMode(SPI1_MOSI, OUTPUT);

  digitalWrite(SPI1_SS, HIGH);

  samplingTimer = timerBegin(TIMER0, 80, true);                // 分周比80、1μ秒のタイマを作る
  timerAttachInterrupt(samplingTimer, &onTimer0, true);        // タイマ割込みハンドラを指定
  timerAlarmWrite(samplingTimer, SAMPLE_PERIOD * 1000, true);  // タイマ周期を設定
}

void loop() {
  //byte data = 0b01010101;
  unsigned long t = millis();
  byte channel = 0;
  int a0 = adc_read(0);
  Serial.println(a0);
  ambient.set(1, a0);
  ambient.send();
  while ((millis() - t) < PERIOD * 1000) {
    delay(0);
  }
  // Serial.print(adc_read(0));
  // Serial.print(",");
  // Serial.print(0);
  // Serial.print(",");
  // Serial.println(4000);
}

int adc_read(uint8_t channel) {

  SPI1.beginTransaction(spiSettings);
  digitalWrite(SPI1_SS, LOW);
  SPI1.transfer(0x06 | (channel >> 2));
  int d1 = SPI1.transfer(channel << 6);
  int d2 = SPI1.transfer(0x00);
  digitalWrite(SPI1_SS, HIGH);
  SPI1.endTransaction();

  return ((d1 & 0x1F) * 256 + d2);
}
