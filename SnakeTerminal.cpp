#include <iostream>
#include <windows.h>
#include <stdlib.h>


// game params
const int tableLenX = 20;
const int tableLenY = 40;
std::string table[tableLenX][tableLenY];

// game initial for test
int xHead = 1;
int yHead = 3;
int snakeLen = 3;

// just test turning snake
bool turned = false;
bool ascaris = true;

// to set or clear the table
void setTable()
{
    for (int i = 0; i < tableLenX; i++)
    {
        for (int j = 0; j < tableLenY; j++)
        {
            if (i == 0 || i == tableLenX - 1)
            {
                table[i][j] = "-";
            }
            else if (j == 0 || j == tableLenY - 1)
            {
                table[i][j] = "|";
            }
            else
            {
                table[i][j] = " ";
            }
        }
    }
}

// showing the table to ther user
void showTable()
{

    for (int i = 0; i < tableLenX; i++)
    {
        for (int j = 0; j < tableLenY; j++)
        {
            std::cout << table[i][j];
        }

        std::cout << "\n";
    }
}

void setSnakeHorizentall(int y)
{

    for (int i = 0; i < snakeLen; i++)
    {

        if (y == 0)
        {
            y = tableLenY - 2;
        }

        if (y == tableLenY - 1)
        {
            y = 1;
        }

        table[xHead][y] = "o";
        y = y - 1;
    }
}

void setSnakeVerticall(int x)
{
    for (int i = 0; i < snakeLen; i++)
    {

        if (x == 0)
        {
            x = tableLenX - 2;
        }

        if (x == tableLenX - 1)
        {
            x = 1;
        }

        table[x][yHead] = "o";
        x = x - 1;
    }
}

void turnSnake()
{
    for (int i = 1; i < snakeLen; i++)
    {
        for (int j = 0; j < i; j++)
        {
            table[xHead + j + 1][yHead] = "o";
        }

        for (int k = 0; k < snakeLen - i; k++)
        {
            table[xHead][yHead - k] = "o";
        }

        showTable();
        Sleep(200);
        system("cls");
        setTable();
    }

    xHead = xHead + snakeLen;
}

void goHorizentally()
{

    if (yHead == tableLenY - 1)
    {
        yHead = 1;
    }
    setSnakeHorizentall(yHead);
    yHead = yHead + 1;
}

void goVertically()
{

    if (xHead == tableLenX - 1)
    {
        xHead = 1;
    }
    setSnakeVerticall(xHead);
    xHead = xHead + 1;
}

void gameLoop()
{
    int test;

    if (turned)
    {
        goVertically();
        showTable();
        setTable();
    }
    else
    {
        setTable();
        goHorizentally();
        showTable();
    }

    Sleep(200);
    system("cls");

    if (yHead == 20 && ascaris)
    {
        std::cin >> test;
        if (test == 1)
        {
            setTable();
            turnSnake();
            turned = true;
            ascaris = false;
        }
    }
}

int main()
{

    while (1)
    {
        gameLoop();
    }

    return 0;
}