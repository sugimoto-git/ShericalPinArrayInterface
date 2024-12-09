#include <Wire.h>
#include "AMG8833.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include "Arduino_ST7789.h"

#define AMG88_ADDR 0x69  // I2Cアドレス

AMG8833 amg8833(AMG88_ADDR);

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240  // Change this to 96 for 1.27" OLED.

#define TFT_MOSI 18
#define TFT_SCLK 19
#define TFT_DC 17
#define TFT_CS -1
#define TFT_RST 5

#define COLx3 24
#define ROWx3 24
#define CELL_W (SCREEN_WIDTH / COLx3)
#define CELL_H (SCREEN_HEIGHT / ROWx3)

#define BLACK 0x0000

Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_CS);

uint32_t heat(float);  // heat関数の宣言

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  pinMode(21, INPUT_PULLUP);  // SDAをプルアップする
  pinMode(22, INPUT_PULLUP);  // SDAをプルアップする
  Wire.begin();               // Wireライブラリを初期化
  amg8833.begin();            // AMG8833を初期化

  tft.init(SCREEN_WIDTH, SCREEN_HEIGHT);
  tft.fillScreen(BLACK);
}

void interpolate_image(float *src, uint8_t src_rows, uint8_t src_cols, float *dest, uint8_t dest_rows, uint8_t dest_cols);  // 補完関数の宣言

void loop() {
  float temp[64];  // AMG8833から読んだ8 x 8の温度データ
  float tempx3[ROWx3 * COLx3];
  amg8833.read(temp);
  interpolate_image(temp, 8, 8, tempx3, ROWx3, COLx3);
  for (int y = 0; y < ROWx3; y++) {
    for (int x = 0; x < COLx3; x++) {
      float t = tempx3[(ROWx3 - y - 1) * COLx3 + COLx3 - x - 1];
      int minT = 80, maxT = 0;
      for (int i = 0; i < 64; i++) {
        if (temp[i] < minT)
          minT = temp[i];
        if (temp[i] > maxT)
          maxT = temp[i];
      }
      uint16_t color = heat(map(constrain((int)t, minT, maxT), minT, maxT, 0, 100) / 100.0);
      tft.fillRect(x * CELL_W, y * CELL_H, CELL_W, CELL_H, color);
    }
  }
}


