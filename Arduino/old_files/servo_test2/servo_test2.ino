#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(2,2,NEO_RGB + NEO_KHZ800);
int i;

void setup(){
  pixels.begin();
  i=0;
}

void  loop(){
  i++;
  if(i>=255){i=0;}
  pixels.setPixelColor(0, pixels.Color(255-i,abs(128-i),i));
  pixels.setPixelColor(1, pixels.Color(0,0,0));
  pixels.show();
  delay(50);
}