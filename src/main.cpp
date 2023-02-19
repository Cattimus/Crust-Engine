#include <iostream>
using namespace std;

#include "Engine.hpp"



void logicDelta(double delta, double* pos, double* vel, int* size) {
	pos[0] += (vel[0] * delta);
	pos[1] += (vel[1] * delta);
}

int main()
{
	Engine engine;
	engine.SetBackgroundColor(0x32, 0x60, 0xA8);

	//config options
	engine.EnableVsync();
	engine.UseBilinearFiltering();
	engine.EnableDelta();

	//set up scene
	engine.CreateWindow("Crust engine demo", true);
	Scene* scene = engine.CreateScene("main");
	Object* obj = scene->CreateObject("../media/test.png", 200, 100, 250, 250);

	//set up logic for our object
	obj->RegisterLogicCallbackDelta(logicDelta);
	obj->SetVelocity(1, 0);

	//start rendering
	engine.StartMainLoop();
	return 0;
}