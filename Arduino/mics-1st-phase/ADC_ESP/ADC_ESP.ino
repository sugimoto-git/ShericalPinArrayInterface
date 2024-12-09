void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(34, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int a = analogRead(34);
  Serial.print(a);
  Serial.print(",");
  Serial.print(4096);
  Serial.print(",");
  Serial.println(0);
}
