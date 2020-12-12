#include "bitGL.h"
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib> //_sleep()  --- just a function that waits a certain amount of milliseconds
#include <stdlib.h>
#include <vector>
#include <tuple>

using namespace bitGL;
using namespace std;

class GameObject
{
public:
    int x = 0;
    int y = 0;
    string displayChar = " ";
};

/*Screen*/
vector<vector<string>> displayCharsVec;

int displayWidth = 0;
int displayHeight = 0;

bool displayInited = false;

/*Frames*/
float timeTaken = 0;

float targetFPS = 10;
bool newFrame = true;

/*Game Objects*/
vector<GameObject> gameObjects;

/*Init Functions*/
void Update();
void DisplayFrame();

int main()
{
    Init(7, 2, 10);

    displayCharsVec[6][1] = "0";

    int newGameObjectIndex = CreateGameObject(1, 1, "1");
    int newGameObjectIndex2 = CreateGameObject(1, 1, "2");

    int otherObjectIndex = Collision(newGameObjectIndex);
    if (otherObjectIndex != -1)
    {
        RemoveGameObject(otherObjectIndex);
    }

    Update();
}

void bitGL::Init(int _displayWidth, int _displayHeight, int _targetFPS)
{
    displayWidth = _displayWidth;
    displayHeight = _displayHeight;

    targetFPS = _targetFPS;

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
            displayCharsVec[gameObjects[i].x][gameObjects[i].y] = gameObjects[i].displayChar;
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

int bitGL::CreateGameObject(int x, int y, string displayChar)
{
    GameObject newGameObject = GameObject();
    newGameObject.x = x;
    newGameObject.y = y;
    newGameObject.displayChar = displayChar;
    gameObjects.push_back(newGameObject);
    return gameObjects.size() - 1;
}

void bitGL::RemoveGameObject(int gameObjectIndex)
{
    gameObjects[gameObjectIndex];

    std::vector<GameObject>::iterator it = gameObjects.begin() + gameObjectIndex;
    gameObjects.erase(it);
}

int bitGL::Collision(int gameObjectIndex)
{
    for (int i = 0; i < gameObjects.size(); i++)
    {
        if (i != gameObjectIndex)
        {
            if (gameObjects[gameObjectIndex].x == gameObjects[i].x && gameObjects[gameObjectIndex].y == gameObjects[i].y)
            {
                return i;
            }
        }
    }
    return -1;
}
