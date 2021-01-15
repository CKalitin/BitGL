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

/*Game*/
bool runGame = true;

int playerGameObjectIndex;
float playerXSpeed = 7;
float playerYSpeed = 3.5;
int playerStartPos[2] = {9, 0};

vector<int> projectileIndexs;
float projectileSpeed = 4.5;

float shootTimer = 0;
float timeBtwShots = 1;

vector<int> enemyIndexs;
vector<float> enemyXMoves;
vector<float> enemyXFlipPos;
float enemyTimer = 4;

float timeBtwEnemies[] = {4, 3, 4, 3, 2, 4, 3, 2, 3};
float timeBtwEnemiesDelays[] = {8, 12, 8, 12, 6, 8, 12, 8, 99999};
//bool decreaseTimeBtwEnemies = true;
int enemySpawnTimerIndex = 0;
float fasterEnemySpawnerTimer = 0;

int score = 0;

void StartMenu();
void ToggleDisplayOfGameObjects();
void GameOver();
void GameOverLoop();
void RestartGame();
void Move();
void ShootInput();
void Shoot();
void Projectiles();
void SpawnEnemies();
void Enemies();
void FasterEnemySpawns();

void Start()
{
    Init(20, 10);

    StartMenu();

    playerGameObjectIndex = CreateGameObject(playerStartPos[0], playerStartPos[1], "^");
}

<<<<<<< HEAD
=======
void Update()
{
    if (GetKeyState(VK_ESCAPE) & 0x8000)
    {
        Quit();
    }

    if (runGame == true)
    {
        ShootInput();
        Projectiles();
        Move();
        FasterEnemySpawns();
        SpawnEnemies();
        Enemies();

        cout << "Score: " << score << endl;
    }
    else
    {
        GameOverLoop();
    }
}

void StartMenu()
{
    system("CLS");
    cout << "Welcome to Blastar 2.0! By Christopher Kalitin" << endl;
    cout << "Use WASD or arrow keys to move, space to shoot, Esc to quit." << endl;
    system("pause");
}

void ToggleDisplayOfGameObjects()
{
    gameObjects[playerGameObjectIndex].display = !gameObjects[playerGameObjectIndex].display;
    for (int i = 0; i < enemyIndexs.size(); i++)
    {
        gameObjects[enemyIndexs[i]].display = !gameObjects[enemyIndexs[i]].display;
    }
    for (int i = 0; i < projectileIndexs.size(); i++)
    {
        gameObjects[projectileIndexs[i]].display = !gameObjects[projectileIndexs[i]].display;
    }
}

void GameOver()
{
    runGame = false;
    ToggleDisplayOfGameObjects();
}

void GameOverLoop()
{
    cout << "Game Over" << endl;
    cout << "Score: " << score << endl;
    cout << "Press R to restart" << endl;
    if ((GetKeyState('R') & 0x8000))
    {
        RestartGame();
    }
}

void RestartGame()
{
    shootTimer = 0;
    projectileIndexs.clear();

    enemyTimer = 0;
    enemyIndexs.clear();
    enemyXMoves.clear();
    enemyXFlipPos.clear();

    enemySpawnTimerIndex = 0;
    fasterEnemySpawnerTimer = 0;

    gameObjects[playerGameObjectIndex].x = playerStartPos[0];
    gameObjects[playerGameObjectIndex].y = playerStartPos[1];

    runGame = true;
}

void Move()
{
    if ((GetKeyState('W') & 0x8000) || (GetKeyState(VK_UP) & 0x8000))
    {
        MoveGameObject(playerGameObjectIndex, 0, playerYSpeed);
    }
    if ((GetKeyState('S') & 0x8000) || (GetKeyState(VK_DOWN) & 0x8000))
    {
        MoveGameObject(playerGameObjectIndex, 0, -playerYSpeed);
    }
    if ((GetKeyState('D') & 0x8000) || (GetKeyState(VK_RIGHT) & 0x8000))
    {
        MoveGameObject(playerGameObjectIndex, playerXSpeed, 0);
    }
    if ((GetKeyState('A') & 0x8000) || (GetKeyState(VK_LEFT) & 0x8000))
    {
        MoveGameObject(playerGameObjectIndex, -playerXSpeed, 0);
    }
}

void ShootInput()
{
    if ((GetKeyState(VK_SPACE) & 0x8000) && shootTimer >= timeBtwShots)
    {
        shootTimer = 0;
        Shoot();
    }
    else
    {
        shootTimer += deltaTime;
    }
}

void Shoot()
{
    projectileIndexs.push_back(CreateGameObject(gameObjects[playerGameObjectIndex].x, gameObjects[playerGameObjectIndex].y + 1, "!"));
}

void Projectiles()
{
    for (int i = 0; i < projectileIndexs.size(); i++)
    {
        for (int x = 0; x < enemyIndexs.size(); x++)
        {
            if (Collision(projectileIndexs[i], enemyIndexs[x]) != -1)
            {
                RemoveGameObject(projectileIndexs[i]);
                projectileIndexs.erase(projectileIndexs.begin() + i);

                RemoveGameObject(enemyIndexs[x]);

                score += 1;
            }
        }
        if (gameObjects[projectileIndexs[i]].y - (displayHeight - 1) > -0.5)
        {
            RemoveGameObject(projectileIndexs[i]);
            projectileIndexs.erase(projectileIndexs.begin() + i);
        }
        else
        {
            MoveGameObject(projectileIndexs[i], 0, projectileSpeed);
        }
    }
}

void SpawnEnemies()
{
    if (enemyTimer >= timeBtwEnemies[enemySpawnTimerIndex])
    {
        enemyTimer = 0;
        enemyIndexs.push_back(CreateGameObject(rand() % displayWidth, displayHeight - 1, "v"));
        enemyXFlipPos.push_back(displayWidth / 2);
        float xMove = 2;
        if (rand() % 2 == 1)
        {
            xMove = -xMove;
        }
        enemyXMoves.push_back(xMove);
    }
    else
    {
        enemyTimer += deltaTime;
    }
}

void Enemies()
{
    for (int i = 0; i < enemyIndexs.size(); i++)
    {
        float difference = fabs(enemyXFlipPos[i] - gameObjects[enemyIndexs[i]].x);
        if (gameObjects[enemyIndexs[i]].display == false)
        {
            enemyIndexs.erase(enemyIndexs.begin() + i);
        }
        else if (gameObjects[enemyIndexs[i]].y < 0.1)
        {
            RemoveGameObject(enemyIndexs[i]);
            enemyIndexs.erase(enemyIndexs.begin() + i);
            enemyXMoves.erase(enemyXMoves.begin() + i);
            enemyXFlipPos.erase(enemyXFlipPos.begin() + i);
            GameOver();
        }
        else if ((gameObjects[enemyIndexs[i]].x >= displayWidth - 1.3 || gameObjects[enemyIndexs[i]].x <= 0.3) && difference > displayWidth / 4)
        {
            enemyXFlipPos[i] = gameObjects[enemyIndexs[i]].x;
            enemyXMoves[i] = -enemyXMoves[i];
        }
        else
        {
            MoveGameObject(enemyIndexs[i], enemyXMoves[i], -0.4);
        }
    }
}

void FasterEnemySpawns()
{
    if (fasterEnemySpawnerTimer >= timeBtwEnemiesDelays[enemySpawnTimerIndex])
    {
        if (enemySpawnTimerIndex < sizeof(timeBtwEnemiesDelays))
        {
            enemySpawnTimerIndex += 1;
        }
        fasterEnemySpawnerTimer = 0;
    }
    else
    {
        fasterEnemySpawnerTimer += deltaTime;
    }
}

>>>>>>> main
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
