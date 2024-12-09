const float Target = 2.5;
const float Kp = 20;
const float Ki = 10;
const float Kd = 4;

float x; //測定結果
float dt; //微小時間
float pretime; //1つ前の時間
float P, I, D, preP;
uint8_t duty; //コントロール値0～255
int up = 5; //横軸作成用
int down = 0; //横軸作成用

void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
}

void loop() {
  analogWrite(10,duty);

  for(int i = 0;i < 1000;i++){
    x += analogRead(A0);
  }

  x = 5*x/1000/1023;

  dt = (micros() - pretime)/1000000;
  pretime = micros();
  P = Target - x;
  I += P*dt;
  D = (P - preP)/dt;
  preP = P;

  duty += Kp*P + Ki*I + Kd*D;

  Serial.print(x);
  Serial.print(",");
  Serial.print(up);
  Serial.print(",");
  Serial.print(down);
  Serial.print(",");
  Serial.print(Target);
  Serial.print("\n");
}



