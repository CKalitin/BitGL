#include "bitGL.h"

using namespace bitGL;

void loop();

int main()
{
    bitGL::Init(10, 10);
    loop();
}

void loop()
{
    while (true)
    {
        bitGL::Loop();
    }
}

//Command to compile: g++ example.cpp bitGL.cpp -o BitGL