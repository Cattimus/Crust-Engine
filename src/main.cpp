#include <iostream>
using namespace std;

#include "Engine.hpp"

double maxVeloc = 5;
Object* controlled;
Scene* scene;
Engine engine;

void HandleKeyboardInput(Engine* p)
{
	switch(p->GetKeycode())
	{
		case SDLK_w:
		{
			controlled->velY = p->KeyDown() ? maxVeloc * -1 : 0;
			break;
		}

		case SDLK_s:
		{
			controlled->velY = p->KeyDown() ? maxVeloc : 0;
			break;
		}

		case SDLK_a:
		{
			controlled->velX = p->KeyDown() ? maxVeloc * -1 : 0;
			break;
		}

		case SDLK_d:
		{
			controlled->velX = p->KeyDown() ? maxVeloc : 0;
			break;
		}

		case SDLK_r:
		{
			controlled->velR = p->KeyDown() ? 15 : 0;
		}
	}
}

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

	scene->GetEventHandler()->RegisterEvent(
		Event<Scene>(scene, "Object Create",

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
			[](Scene* p)
			{
				return;
			}

		)
	);

	//enable printing for event
	scene->GetEventHandler()->GetEvent("Object Create")->EnableDebug();

	Object* obj = scene->CreateEntity("../media/test.png", 200, 100, 250, 250);
	controlled = obj;

	//Register a new event using lambda expressions
	obj->GetEventHandler()->RegisterEvent(
		Event<Object>(obj, "Move", 
			//condition(always run)
			NULL,

			//action (move object)
			[](Object* parent)
			{
				parent->MoveStep(1);
				parent->RotateStep(1);
			}
	
		)
	);

	engine.GetEventHandler()->GetEvent("KeyboardInput")->RegisterAction(HandleKeyboardInput);
	engine.GetEventHandler()->GetEvent("Quit")->RegisterAction([](auto p){return;});
	engine.GetEventHandler()->GetEvent("Quit")->EnableDebug();

	//start rendering
	engine.StartMainLoop();
	return 0;
}