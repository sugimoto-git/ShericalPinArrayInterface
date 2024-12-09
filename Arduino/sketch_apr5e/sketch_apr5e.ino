#include <Adafruit_NeoPixel.h>
#define PIN 3 //INが接続されているピンを指定
#define NUMPIXELS 1 //LEDの数を指定
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); //800kHzでNeoPixelを駆動

#include <ESP32Servo.h>
#define motor1 4
#define motor2 5
Servo myServo1;
Servo myServo2;
long currentTime, LEDTimer11, LEDTimer12;
static const byte servoInterval = 25;
long servoTimer;
bool flag = 1;


void setup() {
  pixels.begin(); //NeoPixelを開始
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
}

void loop() {
  pixels.clear(); //NeoPixelの出力をリセット
  // for(int i=0; i<NUMPIXELS; i++) { //LEDを１つずつ制御
  //   pixels.setPixelColor(i, pixels.Color(0, 0, 0)); //LEDの色を設定
  //   pixels.show();   //LEDに色を反映
  //   delay(500); //500ms待機
  // }

  currentTime = millis();
  if (currentTime - LEDTimer12 > 5000){
    LEDTimer12 = currentTime;
    if(flag == 1){
      flag = 0;
      digitalWrite(motor1, HIGH);
      digitalWrite(motor2, LOW);
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      pixels.show();
    }else{
      flag = 1;
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, HIGH);
      pixels.setPixelColor(i, pixels.Color(0, 255, 0));
      pixels.show();
    }
  }



}




