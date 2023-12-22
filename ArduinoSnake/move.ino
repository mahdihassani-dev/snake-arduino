#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>


Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 9, 10, 8);
void setup()   {
  //Serial.begin(9600);
  display.begin();
  display.clearDisplay();
  display.setContrast(50);
  //display.drawRect(0, 0, 83, 47, BLACK);
  //display.display();
}
void loop() {
  //char board[12]={'.','.','.','.','.','.','.','.','.','.','.','.'};
  while(true){
    display.drawRect(0, 0, 83, 47, BLACK);
    display.display();
    for(int j=0;j<12;j++){
      for(int k=0;k<12;k++){
        if(j==k){
          display.setCursor(j, k);
          display.print(".");
          display.display();
          delay(250);
        } 
      }
    }
    display.clearDisplay();
    display.drawRect(0, 0, 83, 47, BLACK);
    display.display();
    for(int j=12;j<24;j++){
      for(int k=12;k<24;k++){
        if(j==k){
          display.setCursor(j, k);
          display.print(".");
          display.display();
          delay(250);
        } 
      }
    }
    display.clearDisplay();
    display.display();
    

    display.clearDisplay();
    display.drawRect(0, 0, 83, 47, BLACK);
    display.display();
    for(int j=24;j<36;j++){
      for(int k=24;k<36;k++){
        if(j==k){
          display.setCursor(j, k);
          display.print(".");
          display.display();
          delay(250);
        } 
      }
    }
    display.clearDisplay();
    display.display();
    }
}