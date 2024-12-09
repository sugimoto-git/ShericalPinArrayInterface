#define SW_BTN_PIN  3
#define IR_RECV_PIN 2
#define IR_LED_PIN  5
#define PULSE_DELAY 8
#define MAX_SAMPLES 100    // 最大サンプル数

unsigned int irData[] = {1022, 895, 442, 67, 52, 68, 51, 68, 160, 68, 54, 67, 164, 67, 52, 68, 51, 68, 51, 68, 52, 67, 52, 68, 50, 68, 160, 70, 51, 68, 52, 70, 53, 68, 52, 67, 52, 70, 51, 68, 51, 68, 51, 70, 52, 67, 161, 68, 51, 68, 51, 68, 54, 68, 52, 68, 53, 68, 52, 67, 164, 68, 160, 68, 53, 68, 160, 68, 160, 68, 166, 70, 160, 68, 
 1978, 67, 52, 68, 160, 68, 51, 68, 51, 68, 54, 68, 51, 68, 53, 68, 52, 68, 54, 68, 53, 68, 52, 67, 54, 68, 51, 68, 54, 67, 52, 68, 163, 68, 51, 68, 51, 67, 52, 68, 51, 68, 50, 69, 52, 67, 52, 68, 51, 68, 51, 68, 54, 67, 52, 68, 53, 68, 160, 68, 160, 68, 54, 68, 51, 70};
unsigned int irDataSize = sizeof(irData) / sizeof(irData[0]);

void setup () {
  Serial.begin(57600);
  
  pinMode(SW_BTN_PIN,  INPUT_PULLUP);
  pinMode(IR_RECV_PIN, INPUT);
  pinMode(IR_LED_PIN,  OUTPUT);
}

void pulseOn (unsigned long length) {
  unsigned long startTime = micros();
  unsigned int flag = LOW;
  
  while ((micros() - startTime) < length) {
    digitalWrite(IR_LED_PIN, flag = !flag);
    delayMicroseconds(PULSE_DELAY);
  }
}

void pulseOff (unsigned long length) {
  digitalWrite(IR_LED_PIN, LOW);
  delayMicroseconds(length);
}

void irSend () {
  Serial.println("Send");
  
  unsigned int irDataSize = sizeof(irData) / sizeof(irData[0]);
  for (unsigned int i = 0; i < irDataSize; i++) {
    unsigned long length = irData[i] * 10;
    if (i % 2 == 0) {
      pulseOn(length);
    } else {
      pulseOff(length);
    }
  }

  delay(1000);
}

void loop () {
  if (digitalRead(SW_BTN_PIN) == LOW) {
    irSend();
  } else {
    delay(1000);
  }
}


