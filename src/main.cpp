#include <iostream>
using namespace std;

#include "Engine.hpp"

int main()
{
	Engine engine;
	engine.SetBackgroundColor(0xCC, 0x11, 0x22);
	engine.CreateWindow("Test window", true);
	engine.RenderCurrent();
	SDL_Delay(5000);
	return 0;
}