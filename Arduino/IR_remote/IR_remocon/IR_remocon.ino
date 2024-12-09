#define SW_BTN_PIN  35
#define IR_RECV_PIN 34
#define IR_LED_PIN  4
#define PULSE_DELAY 8
#define MAX_SAMPLES 300    // 最大サンプル数

unsigned int irData[MAX_SAMPLES];
unsigned int irDataSize = sizeof(irData) / sizeof(irData[0]);
int dataSize = 0;

void setup () {
  Serial.begin(57600);
  
  pinMode(SW_BTN_PIN,  INPUT_PULLUP);
  pinMode(IR_RECV_PIN, INPUT);
  pinMode(IR_LED_PIN,  OUTPUT);
}

// void irRecv () {
//   Serial.print(".");
  
//   unsigned int prevIR = HIGH;
//   unsigned long prevTime = micros();
  
//   unsigned int curIR;
//   unsigned long curTime;
  
//   while ((curTime = micros()) - prevTime < 1000000) {
//     if ((curIR = digitalRead(IR_RECV_PIN)) == prevIR) {
//       continue;
//     }
    
//     Serial.print((curTime - prevTime) / 10);
//     Serial.print(',');
    
//     prevIR = curIR;
//     prevTime = curTime;
//   }
  
//   Serial.println();
// }

void irRecv(unsigned int* irData, int& dataSize) {
  unsigned int prevIR = HIGH;
  unsigned long prevTime = micros();
  
  unsigned int curIR;
  unsigned long curTime;
  
  int index = 0;

  while ((curTime = micros()) - prevTime < 1000000) {
    if ((curIR = digitalRead(IR_RECV_PIN)) == prevIR) {
      continue;
    }
    
    // 時間差を記録
    if (index < MAX_SAMPLES) {
      irData[index++] = (curTime - prevTime) / 10; // 10us単位で記録
    }
    
    prevIR = curIR;
    prevTime = curTime;
  }
  dataSize = index; // 実際に収集したデータ数を返す
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

void printdata(unsigned int *arr, int size) {
  Serial.print("[");
  for (int i = 0; i < size; i++) {
    Serial.print(arr[i]);
    if (i < size - 1) {
      Serial.print(", "); // 要素間にカンマを追加
    }
  }
  Serial.println("]");
}

void loop () {
  irDataSize = 0;
  if (digitalRead(SW_BTN_PIN) == LOW) {
    irRecv(irData,dataSize);
  } else {
    // irSend();
    printdata(irData, irDataSize);
    delay(2000);
  }
}