int i = 2;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(i, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(i, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(i, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}





