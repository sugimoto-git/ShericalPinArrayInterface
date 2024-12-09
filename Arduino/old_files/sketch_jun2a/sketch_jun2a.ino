#include <ESP32Servo.h>
#define SERVO_PIN1 2
#define SERVO_PIN2 3
Servo myServo1;
Servo myServo2;
long currentTime, LEDTimer11, LEDTimer12;
static const byte servoInterval = 25;
long servoTimer;
bool flag;
void setup() {
  myServo1.attach(SERVO_PIN1);
  myServo2.attach(SERVO_PIN2);
}
void loop(){
  currentTime = millis();
  if (currentTime - LEDTimer12 > 5000){
    LEDTimer12 = currentTime;
    if(flag == 1){
      flag = 0;
      myServo1.write(360);
      myServo2.write(0);
    }else{
      flag = 1;
      myServo2.write(360);
      myServo1.write(0);
    }
  }
}


