#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

const int width = 83;
const int height = 47;

bool gameover;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail = 10;
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
}
void loop() {
}

void draw() {

  // Draw the snake
  for (int i = 0; i < nTail; i++)
    board[tailY[i]][tailX[i]] = '.';

  // Draw the head
  board[y][x] = '.';

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      display.print(board[i][j]);
    }
    cout << endl;
  }
}