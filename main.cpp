//Simple Snake Console Game
//Not object-oriented (i.e. no classes)
//ADAPTED FROM NVITANOVIC (YOUTUBE)

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
//coordinate system [20x20]
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100]; //array for tail.
int nTail; //length of tail
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;


//Initially sets up the game.
void Setup(){
    srand(time(NULL));
    nTail = 0;
    gameOver = false;
    dir = STOP;
    x = width/2; //middle of the board
    y = height/2; //snake's head will be in the middle of map.
    fruitX = rand() % width; // anywhere from 0 - (width - 1)
    fruitY = rand() % height;
    score = 0;
}

void Draw()
{
    system("cls");
    //display the top border of the map.
    for (int i = 0; i < width+2; i++){
        cout << "#";
    }
    cout << endl;

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++)
        {
            if (j == 0) //check if it's the first field in the row
                cout << "#";
            if (i == y && j == x)
                cout << "O"; //snake head
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else{
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (j == (width-1)) //check if it's the last field in the row
                cout << "#";
        }
        cout << endl;
    }

    //bottom border
    for (int i = 0; i < width+2; i++){
        cout << "#";
    }
    cout << endl;
    cout << "Score: " << score << endl;
}

void Input()
{
    //controls.
    if (_kbhit()) //returns positive if key is pressed
    {
        switch(_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'f':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic()
{
    Sleep(100);
    //first item in tail is the item directly previous to head.
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
    switch(dir)
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

    //if snake bumps into wall
    //if (x > width || x < 0 || y > height || y < 0)
        //fgameOver = true;
    //come out on the other side:
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;
    //if snake head bumps into tail
    for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
			cout << "****** GAME OVER ********" << endl;

    //if snake eats fruit
    if (x == fruitX && y == fruitY)
    {
        nTail++; //tail length increases
        score += 10; //score increases
        fruitX = rand() % width; // anywhere from 0 - (width - 1)
        fruitY = rand() % height;
    }
}

int main()
{
    Setup();
    while (!gameOver){
        Draw();
        Input();
        Logic();
        //Sleep(10);
    }
    return 0;
}
