#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameover;
const int width = 20;
const int height = 10;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir;

char board[height][width];

void Setup()
{
    gameover = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;

    // Initialize the board
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            board[i][j] = ' ';
}

void Draw()
{
    // Draw the snake
    for (int i = 0; i < nTail; i++)
        board[tailY[i]][tailX[i]] = 'o';

    // Draw the head
    board[y][x] = 'O';

    // Draw the fruit
    board[fruitY][fruitX] = '@';

    // Draw the board
    system("cls"); // Clear the console

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#"; // left wall
            cout << board[i][j];
            if (j == width - 1)
                cout << "#"; // right wall
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;

    // Clear the board for the next iteration
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            board[i][j] = ' ';
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 224: // arrow key
            switch (_getch())
            {
            case 75: // left arrow
                if (dir != RIGHT)
                    dir = LEFT;
                break;
            case 77: // right arrow
                if (dir != LEFT)
                    dir = RIGHT;
                break;
            case 72: // up arrow
                if (dir != DOWN)
                    dir = UP;
                break;
            case 80: // down arrow
                if (dir != UP)
                    dir = DOWN;
                break;
            }
            break;
        case 'x':
            gameover = true;
            break;
        }
    }
}

void Algorithm()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;

    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameover = true;

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main()
{
    Setup();
    while (!gameover)
    {
        Draw();
        Input();
        Algorithm();
        Sleep(50); // Delay adjusted to slow down the game
    }
    return 0;
}