#include "bitGL.h"
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib> //_sleep()  --- just a function that waits a certain amount of milliseconds
#include <stdlib.h>
#include <vector>
#include <tuple>
#include <math.h>

using namespace std;
using namespace bitGL;

#pragma region bitGLVars

class GameObject
{
public:
    float x = 0;
    float y = 0;
    string displayChar = " ";
    bool display = true;
};

/*Screen*/
vector<vector<string>> displayCharsVec;

int displayWidth = 0;
int displayHeight = 0;

bool displayInited = false;

/*Frames*/
float deltaTime = 0;

bool newFrame = true;

/*Game Objects*/
vector<GameObject> gameObjects;

/*Functions(That are only used by bitGL, not user)*/
void DisplayFrame();

#pragma endregion bitGLVars

#pragma region game

void Start()
{
    Init(10, 10);
}

#pragma endregion game

#pragma region bitGL

void bitGL::Init(int _displayWidth, int _displayHeight)
{
    displayWidth = _displayWidth;
    displayHeight = _displayHeight;

    vector<vector<string>> newVec(displayWidth, vector<string>(displayHeight, " "));
    displayCharsVec = newVec;

    displayInited = true;
}

void bitGL::Loop()
{
    clock_t startTime;
    if (newFrame == true)
    {
        startTime = clock();
        newFrame = false;
    }

    if (displayInited)
    {
        DisplayFrame();
    }

    clock_t endTime = clock();
    clock_t clockTicksTaken = endTime - startTime;
    deltaTime = clockTicksTaken / (double)CLOCKS_PER_SEC;
}

void DisplayFrame()
{
    system("CLS");

    for (int i = 0; i < gameObjects.size(); i++)
    {
        if (gameObjects[i].display == true)
        {
            displayCharsVec[round(gameObjects[i].x)][round(gameObjects[i].y)] = gameObjects[i].displayChar;
        }
    }

    for (int y = 0; y < displayHeight; y++)
    {
        for (int x = 0; x < displayWidth; x++)
        {
            cout << displayCharsVec[x][displayHeight - y - 1];
        }
        cout << endl;
    }

    for (int y = 0; y < displayHeight; y++)
    {
        for (int x = 0; x < displayWidth; x++)
        {
            displayCharsVec[x][y] = " ";
        }
    }

    newFrame = true;
}

int bitGL::CreateGameObject(float x, float y, string displayChar)
{
    if (x > displayWidth - 1)
    {
        cout << "X of " << displayChar << " not within display width." << endl;
        return -1;
    }
    else if (y > displayHeight - 1)
    {
        cout << "Y of " << displayChar << " not within display height." << endl;
        return -1;
    }
    else
    {
        GameObject newGameObject = GameObject();

        newGameObject.x = x;
        newGameObject.y = y;
        newGameObject.display = true;
        newGameObject.displayChar = displayChar;

        gameObjects.push_back(newGameObject);

        return gameObjects.size() - 1;
    }
}

void bitGL::RemoveGameObject(int gameObjectIndex)
{
    gameObjects[gameObjectIndex].display = false;
}

void bitGL::MoveGameObject(int gameObjectIndex, float xMovement, float yMovement)
{
    float newX = gameObjects[gameObjectIndex].x + xMovement * deltaTime;
    float newY = gameObjects[gameObjectIndex].y + yMovement * deltaTime;

    if (newX > 0 && newX < displayWidth - 1)
    {
        gameObjects[gameObjectIndex].x = newX;
    }
    if (newY > 0 && newY < displayHeight - 1)
    {
        gameObjects[gameObjectIndex].y = newY;
    }
}

int bitGL::Collision(int gameObjectIndex, int otherGameObjectIndex)
{
    if (otherGameObjectIndex == -1)
    {
        for (int i = 0; i < gameObjects.size(); i++)
        {
            if (round(gameObjects[gameObjectIndex].x) == round(gameObjects[i].x) && round(gameObjects[gameObjectIndex].y) == round(gameObjects[i].y) && i != gameObjectIndex)
            {
                return i;
            }
        }
        return -1;
    }
    else
    {
        if (round(gameObjects[gameObjectIndex].x) == round(gameObjects[otherGameObjectIndex].x) && round(gameObjects[gameObjectIndex].y) == round(gameObjects[otherGameObjectIndex].y))
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    return -1;
}

float bitGL::GetDeltaTime()
{
    return deltaTime;
}

float bitGL::GetFPS()
{
    return round(1 / deltaTime);
}

void bitGL::Quit()
{
    system("CLS");
    exit(EXIT_FAILURE);
}

#pragma endregion bitGL
