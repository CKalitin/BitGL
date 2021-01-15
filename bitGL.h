#include <string>

using namespace std;

// Here are all the function that can be called from another script (All the functions the user can use).
namespace bitGL
{
    void Init(int, int);
    void Loop();
    int CreateGameObject(float, float, string);
    void RemoveGameObject(int);
    void MoveGameObject(int, float, float);
    int Collision(int gameObjectIndex, int otherGameObjectIndex = -1);
    float GetDeltaTime();
    float GetFPS();
    void Quit();
} // namespace bitGL
