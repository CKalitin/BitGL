#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib> //_sleep()  --- just a function that waits a certain amount of milliseconds
#include <stdlib.h>
#include <vector>
#include <list>
using namespace std;

/*Screen*/
vector<vector<string>> displayCharsVec;

int displayWidth = 0;
int displayHeight = 0;

bool displayInited = false;

/*Frames*/
float timeTaken = 0;

float targetFPS = 2;
bool newFrame = true;

/*Game Objects*/
list<GameObject> gameObjects = {};

/*Init Functions*/
void InitDisplay(int, int);
void Update();
void DisplayFrame();

int main()
{
    InitDisplay(7, 2);

    displayCharsVec[6][1] = "0";

    /*GameObject *newGameObject = new GameObject();
    newGameObject->x = 1;
    newGameObject->y = 1;
    newGameObject->objectChar = "0";

    gameObjects.push_back(newGameObject);*/

    Update();
}

void InitDisplay(int _displayWidth, int _displayHeight)
{
    displayWidth = _displayWidth;
    displayHeight = _displayHeight;

    vector<vector<string>> newVec(displayWidth, vector<string>(displayHeight, " "));
    displayCharsVec = newVec;

    displayInited = true;
}

void Update()
{
    while (true)
    {
        if (displayInited)
        {
            DisplayFrame();
        }
    }
}

void DisplayFrame()
{
    clock_t startTime;
    if (newFrame == true)
    {
        startTime = clock();
        newFrame = false;
    }

    if ((clock() - startTime) / (double)CLOCKS_PER_SEC >= 1 / targetFPS)
    {
        system("CLS");

        for (int i = 0; i < gameObjects.size(); i++)
        {

            displayCharsVec[gameObject.x][gameObject.y] = gameObject.objectChar;
        }

        for (int y = 0; y < displayHeight; y++)
        {
            for (int x = 0; x < displayWidth; x++)
            {
                cout << displayCharsVec[x][y];
            }
            cout << endl;
        }

        clock_t endTime = clock();
        clock_t clockTicksTaken = endTime - startTime;
        timeTaken = clockTicksTaken / (double)CLOCKS_PER_SEC;

        cout << "Ms per Frame: " << timeTaken << endl;
        cout << "FPS: " << 1 / timeTaken << endl;

        newFrame = true;
    }
}

class GameObject
{
public:
    int x;
    int y;
    string objectChar = " ";
};