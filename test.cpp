#include "bitGL.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    Init(5, 5, 10);
    int gameObjectIndex = CreateGameObject(2, 2, "0");
}

void Update()
{
    while (true)
    {
        cout << GetDeltaTime << endl;
    }
}