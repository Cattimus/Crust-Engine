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


	scene->RegisterEvent(Event<Scene>(scene, "Object Create",

	//condition
	[](Scene* p)
	{
		static int prev_size;
		int current_size = p->GetObjectList()->size();
		bool to_return = (current_size > prev_size);
		prev_size = current_size;
		return to_return;
	},

	//action
	[](auto p)
	{
		return;
	}

	));

	//enable printing for event
	scene->GetEvent("Object Create")->EnableDebug();

	Object* obj = scene->CreateObject("../media/test.png", 200, 100, 250, 250);
	controlled = obj;

	//Register a new event using lambda expressions
	obj->RegisterEvent(Event<Object>(obj, "Move", 

	//condition(always run)
	[](Object* parent) -> bool
	{
		return true;
	},

	//action (move object)
	[](Object* parent)
	{
		auto xvel = parent->GetXVelocity();
		auto yvel = parent->GetYVelocity();

		auto xpos = parent->GetXPosition();
		auto ypos = parent->GetYPosition();

		parent->SetPosition(xpos + xvel, ypos + yvel);
	}
	
	));

	//start rendering
	engine.StartMainLoop();
	return 0;
}