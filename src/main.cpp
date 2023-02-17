#include <iostream>
using namespace std;

#include "Engine.hpp"

int main()
{
	Engine engine;
	engine.SetBackgroundColor(0x32, 0x60, 0xA8);
	engine.CreateWindow("Test window", true);
	engine.RenderCurrent();
	Scene* scene = engine.CreateScene("main");
	scene->CreateObject("../media/test.png", 100, 100, 150, 150);
	engine.StartMainLoop();
	return 0;
}