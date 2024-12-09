// モータ制御
const int STBY = 2;
const int PWMA = 3;
const int AIN1 = 8;
const int AIN2 = 7;
const int LEDC_CHANNEL = 0;
const int LEDC_BASE_FREQ = 1000;
 
void setup() {
  // PWMの初期化
  
  
  
  ledcSetup(LEDC_CHANNEL, LEDC_BASE_FREQ, 8);
  ledcAttachPin(PWMA, LEDC_CHANNEL);
 
  // GPIOピンの初期化
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(STBY, OUTPUT);
   
  digitalWrite(STBY, HIGH);
}
 
void loop() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW); 
 
  // 加速
  for(int i = 0; i <= 255; i++){
    ledcWrite(LEDC_CHANNEL, i);
    delay(10); 
  }
  // 減速
  for(int i = 255; i >= 0; i--){
    ledcWrite(LEDC_CHANNEL, i);
    delay(10); 
  }
  // 停止
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, HIGH); 
  delay(500);
 
  // 逆回転
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH); 
  // 加速
  for(int i = 0; i <= 255; i++){
    ledcWrite(LEDC_CHANNEL, i);
    delay(10); 
  }
  // 減速
  for(int i = 255; i >= 0; i--){
    ledcWrite(LEDC_CHANNEL, i);
    delay(10); 
  }
  // 停止
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, HIGH); 
  delay(500);
}