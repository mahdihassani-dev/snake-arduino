#include <SPI.h>

const int xPin = A0;
const int yPin = A1;

void setup()   {
  Serial.begin(9600);
}
void loop() {
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);
  int mappedX = map(xValue, 0, 1023, -100, 100);
  int mappedY = map(yValue, 0, 1023, -100, 100);

  if (mappedY > 10) {
    //"Up"
  } else if (mappedY < -10) {
    //"Down"
  } else if (mappedX > 10) {
    //"Right"
  } else if (mappedX < -10) {
    //"Left"
  }


}