#include <iostream>
using namespace std;

#include "Engine.hpp"

int main()
{
	Engine engine;
	engine.SetBackgroundColor(0x32, 0x60, 0xA8);
	engine.EnableVsync();
	engine.UseBilinearScaling();
	engine.CreateWindow("Crust engine demo", true);
	Scene* scene = engine.CreateScene("main");
	scene->CreateObject("../media/test.png", 200, 100, 250, 250);
	engine.StartMainLoop();
	return 0;
}