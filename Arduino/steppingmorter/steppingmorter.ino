const int ENABLE = 8;
const int STEP = 2;
const int DIR = 5;
char c;

void setup() {
  Serial.begin(115200);
  pinMode(ENABLE, OUTPUT);
  pinMode(STEP, OUTPUT);
  digitalWrite(ENABLE, LOW);
  digitalWrite(STEP, LOW);
  digitalWrite(ENABLE, LOW);
}


void loop() {
  // delay(1000);
  if ( Serial.available() > 0 ) {
    c = Serial.read();
    if(c == '1'){
      Serial.println("YES");
      for (int i=0; i<400; i++) {
        digitalWrite(STEP, HIGH);
        delayMicroseconds(2000);
        digitalWrite(STEP, LOW);
        delayMicroseconds(2000);
      }
    }
    if(c = 'a'){
      Serial.println("reverse");
      digitalWrite(DIR, LOW);
    }
    if(c = 'd'){
      Serial.println("reverse");
      digitalWrite(DIR, HIGH);
    }
  }
  delay(1000);
}




