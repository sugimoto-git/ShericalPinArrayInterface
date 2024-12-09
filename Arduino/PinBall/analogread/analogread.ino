void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i = analogRead(A0);
  Serial.print(i);
  Serial.print(" ");
  Serial.print(0);
  Serial.print(" ");
  Serial.println(1024);
}
