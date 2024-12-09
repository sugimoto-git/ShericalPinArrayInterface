#include <ESP32Servo.h>
#define motor1 4
#define motor2 5
Servo myServo1;
Servo myServo2;
long currentTime, LEDTimer11, LEDTimer12;
static const byte servoInterval = 25;
long servoTimer;
bool flag = 1;

void setup(){
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
}

void loop(){
  currentTime = millis();
  if (currentTime - LEDTimer12 > 1000){
    LEDTimer12 = currentTime;
    if(flag == 1){
      flag = 0;
      digitalWrite(motor1, HIGH);
      digitalWrite(motor2, LOW);
    }else{
      flag = 1;
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, HIGH);
    }
  }
}


