const int analogOutPin = 21;
unsigned long t;
int outputValue = 128;

void setup() {
  // analogWriteResolution(12); //Analog range set to 0-4095
  analogWriteFreq(6000);  
}

void loop() {
  t = micros();
  outputValue = (int)(128.0 * sin(2.0 * PI * 264 * (float)t/1000000.0) +127.0);
  
  analogWrite(analogOutPin, outputValue);
}

