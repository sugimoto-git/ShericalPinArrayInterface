const int arraySize = 5;
int dataArray[arraySize];

void setup() {
  Serial.begin(9600);  // シリアル通信を開始
  Serial.println("Arduino is ready");  // 開始メッセージを送信
}

void loop() {
  if (Serial.available() > 0) {
    String receivedString = Serial.readStringUntil('\n');  // 改行文字までのデータを読み込み
    parseData(receivedString);  // 受信データをパースして配列に格納
    printData();  // 受信した配列データを表示
  }
}

void parseData(String data) {
  int index = 0;
  int lastIndex = 0;
  while (index < arraySize) {
    int commaIndex = data.indexOf(',', lastIndex);
    if (commaIndex == -1) {
      dataArray[index] = data.substring(lastIndex).toInt();  // 最後のデータ
      break;
    } else {
      dataArray[index] = data.substring(lastIndex, commaIndex).toInt();  // カンマ区切りのデータ
    }
    lastIndex = commaIndex + 1;
    index++;
  }
}

void printData() {
  Serial.print("Received data: ");
  for (int i = 0; i < arraySize; i++) {
    Serial.print(dataArray[i]);
    if (i < arraySize - 1) {
      Serial.print(", ");
    }
  }
  Serial.println();
}
