#include <iostream>
using namespace std;

#include "Engine.hpp"

double maxVeloc = 500;
Object* controlled;
Scene* scene;
Engine engine;

int main()
{
	engine.SetBackgroundColor(0x32, 0x60, 0xA8);

	//config options
	engine.EnableVsync();
	engine.UseBilinearFiltering();
	engine.EnableDelta();

	//set up scene
	engine.CreateWindow("Crust engine demo", false);
	scene = engine.CreateScene("main");
	Object* obj = scene->CreateObject("../media/test.png", 200, 100, 250, 250);
	controlled = obj;

	//start rendering
	engine.StartMainLoop();
	return 0;
}