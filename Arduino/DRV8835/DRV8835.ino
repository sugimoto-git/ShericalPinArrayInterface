// 回転速度(35-255)
// ※値が大きいほど高速,余りにも小さい値は回転しません。
const uint8_t speeds = 48;
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  // 正転(回転)
  Serial.println("正転");
  analogWrite(10,speeds);
  analogWrite(11,0);
  delay(1000);
 
  // 逆転(逆回転)
  Serial.println("逆転");
  analogWrite(10,0);
  analogWrite(11,speeds);
  delay(1000);
  
  // ブレーキ
  Serial.println("ブレーキ");
  analogWrite(10,speeds);
  analogWrite(11,speeds);
  delay(1000);
}
 