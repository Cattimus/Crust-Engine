#include <iostream>
using namespace std;

#include "Controllers/Engine.hpp"

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
			controlled->pos.velY = p->KeyDown() ? maxVeloc * -1 : 0;
			break;
		}

		case SDLK_s:
		{
			controlled->pos.velY = p->KeyDown() ? maxVeloc : 0;
			break;
		}

		case SDLK_a:
		{
			controlled->pos.velX = p->KeyDown() ? maxVeloc * -1 : 0;
			break;
		}

		case SDLK_d:
		{
			controlled->pos.velX = p->KeyDown() ? maxVeloc : 0;
			break;
		}

		case SDLK_r:
		{
			controlled->pos.velR = p->KeyDown() ? 15 : 0;
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
	scene->GetEventHandler()->GetEvent("Object Create")->debug = true;

	Object* obj = scene->CreateEntity("../media/test2.png", 200, 100, 250, 250);
	controlled = obj;

	obj->GetHitbox()->debug = true;
	obj->GetHitbox()->SetDebugColor(255, 150, 0);

	//Register a move function
	obj->GetEventHandler()->GetEvent("Move")->autoExec = true;
	obj->GetEventHandler()->GetEvent("Move")->RegisterAction(
		[](Object* parent)
		{
			parent->pos.MoveStep(1);
			parent->pos.RotateStep(1);

			//move hitbox to follow object
			auto hitbox = parent->GetHitbox();
			if(hitbox)
			{
				hitbox->pos.x = parent->pos.x;
				hitbox->pos.y = parent->pos.y;
			}
		}
	);

	//Add an action to the collision event
	obj->GetEventHandler()->GetEvent("Collision")->RegisterAction(
		[](Object* parent)
		{
			cout << "Collision detected. at xpos: " << parent->pos.x << endl;
		}
	);

	engine.GetEventHandler()->GetEvent("KeyboardInput")->RegisterAction(HandleKeyboardInput);
	engine.GetEventHandler()->GetEvent("Quit")->RegisterAction([](auto p){return;});
	engine.GetEventHandler()->GetEvent("Quit")->debug = true;

	Object* obj2 = scene->CreateEntity("../media/test.png", 500, 400, 250, 250);
	obj2->GetHitbox()->debug = true;
	obj2->GetHitbox()->SetDebugColor(35, 255, 150);

	//start rendering
	engine.StartMainLoop();
	return 0;
}
