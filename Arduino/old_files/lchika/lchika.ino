const int ledPin = LED_BUILTIN;

void setup() {
  pinMode(ledPin,OUTPUT);
}

void loop() {
  if(millis()%2000 < 1000){
    digitalWrite(ledPin, HIGH);
  }else{
    digitalWrite(ledPin,LOW);
  }
}

// 最大2093056バイトのフラッシュメモリのうち、スケッチが311764バイト（14%）を使っています。
// 最大262144バイトのRAMのうち、グローバル変数が70808バイト（27%）を使っていて、ローカル変数で191336バイト使うことができます。
// Resetting /dev/ttyACM0
// Converting to uf2, output size: 659968, start address: 0x2000
// Scanning for RP2040 devices
// No drive to deploy.
// Failed uploading: uploading error: exit status 1