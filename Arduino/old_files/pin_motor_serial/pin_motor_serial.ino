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
  Serial.begin( 9600 );
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
}



void loop() {
  char inkey;
  if( Serial.available() > 0  ) {
    inkey = Serial.read();
    if(inkey == 'a'){
      digitalWrite(motor1, HIGH);
      digitalWrite(motor2, LOW);
      delay(1000);
      Serial.print("motor:+\n");
    }
    if(inkey == 'd'){
      digitalWrite(motor2, HIGH);
      digitalWrite(motor1, LOW);
      delay(1000);
      Serial.print("motor:-\n");
    }

  }else{
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, LOW);
  }
}




