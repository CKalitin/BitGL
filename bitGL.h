#include <string>

using namespace std;

// Here are all the function that can be called from another script (All the functions the user can use).
namespace bitGL
{
    void Init(int, int, int);
    int CreateGameObject(int, int, string);
    void RemoveGameObject(int);
    int Collision(int);
} // namespace bitGL