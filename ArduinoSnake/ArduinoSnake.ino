#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 9, 10, 8);
void setup()   {
  display.begin();
  // init done
  display.clearDisplay();
  display.display();
  display.setContrast(50);
  
  // Draw a rectangle
  display.drawRect(0, 0, 83, 47, BLACK);
  display.display();
}
void loop() {
}