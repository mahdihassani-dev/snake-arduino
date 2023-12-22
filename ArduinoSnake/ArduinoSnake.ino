#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

const int width = 30;
const int height = 20;

bool gameover;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail = 4;
enum eDirection {
  STOP = 0,
  LEFT,
  RIGHT,
  UP,
  DOWN
};
eDirection dir;

char board[width][height];

Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 9, 10, 8);



void draw() {

  // Draw the snake
  for (int i = 0; i < nTail; i++)
    board[tailY[i]][tailX[i]] = '.';

  // Draw the head
  board[y][x] = '.';

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      display.setCursor(i, j);
      display.print(board[i][j]);
      display.display()
    }
  }
}


void setup() {
  display.begin();
  // init done
  display.clearDisplay();
  display.display();
  display.setContrast(50);

  // Draw a rectangle
  display.drawRect(0, 0, 83, 47, BLACK);
  display.display();

  gameover = false;
  dir = STOP;
  x = width / 2;
  y = height / 2;
  fruitX = rand() % width;
  fruitY = rand() % height;
  score = 0;

  //test data
  tailX[0] = x - 1;
  tailX[1] = x - 2;
  tailX[2] = x - 3;
  tailX[3] = x - 4;

  tailY[0] = y - 1;
  tailY[1] = y - 2;
  tailY[2] = y - 3;
  tailY[3] = y - 4;
  
}
void loop() {

  draw();

}
