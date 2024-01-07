#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <SPI.h>

#define RESOLUTION 4
#define MAXLEN 100
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define DISP_HEIGHT 84
#define DISP_WIDTH 48

#define BUTTON 8


// game values
char direction = RIGHT;
bool game_over = false;

char snakesize = 6;
char snakex[MAXLEN];
char snakey[MAXLEN];

char foodx = -1;
char foody = -1;

// Nokia 5110 LCD
// pin 13 - Serial clock out (CLK)
// pin 11 - Serial data out (DIN)
// pin 9 - Data/Command select (DC)
// pin 10 - LCD chip select (CE)
// pin 8 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 9, 10, 8);


// joystick pins
char sensorPinX = A0;
char sensorPinY = A1;
char sensorValueX = 0;
char sensorValueY = 0;


void setup() {
  Serial.begin(9600);
  pinMode(BUTTON, INPUT_PULLUP);

  // initialize lcd display
  display.begin();
  display.setContrast(45);
  display.setTextColor(BLACK, WHITE);
  display.setTextSize(1);
  display.clearDisplay();
  delay(200);
  display.drawRect(0, 0, 84, 46, BLACK);
  display.setCursor(12, 18);
  display.println("SNAKE GAME");

  display.display();
  delay(200);
  display.clearDisplay();

  init_snake();
}

void loop() {

  if (game_over) {
    display.clearDisplay();
    display.display();
    show_score();
    while (digitalRead(BUTTON)) {
      // while not pressed button, do nothing
    }

    // start again
    display.clearDisplay();
    display.display();
    game_over = false;
    snakesize = 6;
    init_snake();
  }

  display.clearDisplay();

  //----------------game cycle------------------>

  // 1- move parts based on dir
  movesnake();

  // 2- check food
  food();

  // 3- draw snake
  snake();

  //<--------------------------------------------


  display.display();
  delay(100);
}

static void init_snake() {

  // initialize all index in snake
  for (char i = 0; i < MAXLEN; i++) {
    snakex[i] = -2;
    snakey[i] = -2;
  }

  // assign snake position based on its size
  for (char i = 0; i < snakesize; i++) {
    snakex[i] = 11 - i;
    snakey[i] = 5;
  }

  // default direction
  direction = RIGHT;

  // show snake
  for (char i = 0; i <= 2; i++) {
    snake();
    display.display();
    delay(350);
    display.clearDisplay();
    display.display();
    delay(350);
  }
}

// show after lost
static void show_score() {
  display.setCursor(25, 10);
  display.setTextSize(1);
  int score = snakesize;
  display.print("SCORE: ");
  display.println(score);
  display.println(" ");
  display.print("press button");
  display.display();
}

static void food() {
  if (foodx < 0) {
    foodx = random(0, DISP_HEIGHT / RESOLUTION);
    foody = random(0, DISP_WIDTH / RESOLUTION);
  }
  display.drawCircle(foodx * RESOLUTION, foody * RESOLUTION, RESOLUTION / 2, BLACK);
}

static void snake() {

  // all index is drew -> break
  for (char i = 0; i < MAXLEN; i++) {
    if (snakex[i] == -2) {
      break;
    }

    // draw head
    if (i == 0) {
      display.drawCircle(snakex[i] * RESOLUTION, snakey[i] * RESOLUTION, RESOLUTION / 2, BLACK);
    } else {

      // if head hit body
      if (snakex[0] == snakex[i] && snakey[0] == snakey[i]) {
        game_over = true;
      }

      // filled body while not pressed. Low - btn not pressed. High - pressed.
      if (digitalRead(BUTTON) == LOW) {
        display.drawCircle(snakex[i] * RESOLUTION, snakey[i] * RESOLUTION, RESOLUTION / 2, BLACK);
        //display.fillRect(snakex[i] * RESOLUTION, snakey[i] * RESOLUTION, RESOLUTION, RESOLUTION, BLACK);
      } else {
        display.fillCircle(snakex[i] * RESOLUTION, snakey[i] * RESOLUTION, RESOLUTION / 2, BLACK);
      }
    }
  }
}

static void movesnake() {
  char tmpx = snakex[0];
  char tmpy = snakey[0];
  input();
  int xdirection, ydirection;
  switch (direction) {
    case UP:
      xdirection = 0;
      ydirection = -1;
      break;
    case DOWN:
      xdirection = 0;
      ydirection = 1;
      break;
    case LEFT:
      xdirection = -1;
      ydirection = 0;
      break;
    case RIGHT:
      xdirection = 1;
      ydirection = 0;
      break;
  }

  // move snake x and y points based on x an y directions
  char prevx = tmpx + xdirection;
  char prevy = tmpy + ydirection;

  // when snake is going out of screen
  if (prevx >= DISP_HEIGHT / RESOLUTION) {
    prevx = 0;
  } else if (prevx == -1) {
    prevx = DISP_HEIGHT / RESOLUTION;
  }
  if (prevy >= DISP_WIDTH / RESOLUTION) {
    prevy = 0;
  } else if (prevy == -1) {
    prevy = DISP_WIDTH / RESOLUTION;
  }

  for (char i = 0; i < MAXLEN; i++) {
    if (i == 0) {
      if (foodx == snakex[i] && foody == snakey[i]) {
        if (snakesize < MAXLEN) {
          snakex[snakesize] = 0;
          snakey[snakesize] = 0;
          snakesize++;
        }

        foodx = -1;
      }
    }
    if (snakex[i] == -2 || (prevx == snakex[i] && prevy == snakey[i])) {
      break;
    }
    tmpx = snakex[i];
    tmpy = snakey[i];

    snakex[i] = prevx;
    snakey[i] = prevy;

    prevx = tmpx;
    prevy = tmpy;
  }
}
//--------------------
void input() {

  int xValue = analogRead(sensorPinX);
  int yValue = analogRead(sensorPinY);
  int mappedX = map(xValue, 0, 1023, -100, 100);
  int mappedY = map(yValue, 0, 1023, -100, 100);

  if (mappedY > 10) {
    if (direction != DOWN)
      direction = UP;
  } else if (mappedY < -10) {
    if (direction != UP)
      direction = DOWN;
  } else if (mappedX > 10) {
    if (direction != LEFT)
      direction = RIGHT;
  } else if (mappedX < -10) {
    if (direction != RIGHT)
      direction = LEFT;
  }
}