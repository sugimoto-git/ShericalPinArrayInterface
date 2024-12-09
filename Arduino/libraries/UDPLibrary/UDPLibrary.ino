#include "UDPLibrary.h"

void UDPLib::begin(String ip, int send_p, int rec_p) {
  host = ip;
  send_port = send_p;
  receive_port = rec_p;
  wifiUdp.begin(receive_port);
}

void UDPLib::send(String text) {
  byte Data[256];
  char hostC[256];
  host.toCharArray(hostC, text.length());
  Serial.println(hostC);
  text.getBytes(Data, text.length() + 1);
  wifiUdp.beginPacket(hostC, send_port);
  wifiUdp.write(Data, text.length() + 1);
  wifiUdp.endPacket();
}

String UDPLib::read() {
  char x[512] = "";
  if (wifiUdp.parsePacket()) {
    for (int i = 0; i < 512; i++) {
      int v = wifiUdp.read();
      if (v == -1) {
        x[i] = '\0';
        break;
      }
      x[i] = v;
    }
  }
  String r = x;
  return r;
}
