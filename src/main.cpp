#include <iostream>
using namespace std;

#include "Controllers/Engine.hpp"

double maxVeloc = 5;
Object* controlled;
Object* dragged = nullptr;
Scene* scene;
Engine engine;

//TODO - audio playing class
//TODO - audio recording class
//TODO - UI class

void HandleKeyboardInput(void* args)
{
	InputHandler* p = (InputHandler*)args;
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

void HandleMouseButton(void* args)
{
	InputHandler* p = (InputHandler*)args;
	//release dragged object
	if(!p->MouseButtonDown())
	{
		dragged = nullptr;
		return;
	}

	if(p->LeftMouseClicked())
	{
		//iterate over objects to find the one clicked on
		auto list = scene->GetObjectList();
		for(auto &obj : *list)
		{
			auto cur = obj.second.get();
			if(cur->hitbox.PointOverlaps(p->GetMouseX(), p->GetMouseY()))
			{
				dragged = cur;
				break;
			}
		}
	}
}

void HandleMouseWheel(void* args)
{
	InputHandler* p = (InputHandler*)args;
	int scrolledY = p->GetWheelScrolledY();
	int scrolledX = p->GetWheelScrolledX();

	if(scrolledY > 0)
	{
		cout << "Mouse wheel scrolled up\n";
	}
	else if(scrolledY < 0)
	{
		cout << "Mouse wheel scrolled down\n";
	}

	if(scrolledX > 0)
	{
		cout << "Mouse wheel scrolled right\n";
	}
	else if(scrolledX < 0)
	{
		cout << "Mouse wheel scrolled left\n";
	}
}

void HandleMouseDrag(void* args)
{
	InputHandler* p = (InputHandler*)args;
	if(dragged)
	{
		Position* pos = &dragged->pos;
		pos->Move(p->GetMouseMovedX(), p->GetMouseMovedY());
	}
}

#undef main

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

	scene->events.RegisterEvent(
		Event("Object Create",

			//condition
			[](void* args)
			{
				Scene* p = (Scene*)args;
				static int prev_size;
				int current_size = p->GetObjectList()->size();
				bool to_return = (current_size > prev_size);
				prev_size = current_size;
				return to_return;
			},
			scene,

			//action
			[](void* p)
			{
				return;
			},
			nullptr

		)
	);

	//enable printing for event
	scene->events.GetEvent("Object Create")->debug = true;

	Object* obj = scene->CreateEntity("media/test2.png", 200, 100, 250, 250);
	controlled = obj;

	obj->hitbox.debug = true;
	obj->hitbox.SetDebugColor(255, 150, 0);

	//Register a move function
	obj->events.GetEvent("Move")->autoExec = true;
	obj->events.GetEvent("Move")->action.Set(
		[](void* args)
		{
			if(!args)
			{
				return;
			}

			Object* parent = (Object*)args;
			parent->pos.MoveStep(1);
			parent->pos.RotateStep(1);

			//move hitbox to follow object
			auto hitbox = &(parent->hitbox);
			hitbox->pos.x = parent->pos.x;
			hitbox->pos.y = parent->pos.y;
		},

		obj
	);

	//Add an action to the collision event
	obj->events.GetEvent("Collision")->action.Set(
		[](void* args)
		{
			Object* parent = (Object*)args;
			cout << "Collision detected. at xpos: " << parent->pos.x << endl;
		},

		obj
	);
	
	//input events
	InputHandler* in = &(engine.input);
	engine.input.events.GetEvent("KeyboardInput")->action.Set(HandleKeyboardInput, in);
	engine.input.events.GetEvent("MouseButton")->action.Set(HandleMouseButton, in);
	engine.input.events.GetEvent("MouseWheel")->action.Set(HandleMouseWheel, in);
	engine.input.events.GetEvent("MouseDrag")->action.Set(HandleMouseDrag, in);
	
	//engine events
	engine.events.GetEvent("Quit")->action.Set([](auto p){return;});
	engine.events.GetEvent("Quit")->debug = true;

	Object* obj2 = scene->CreateEntity("media/test.png", 500, 400, 250, 250);
	obj2->hitbox.debug = true;
	obj2->hitbox.SetDebugColor(35, 255, 150);
	
	obj2->events.GetEvent("Move")->autoExec = true;
	obj2->events.GetEvent("Move")->action.Set(
		[](void* args)
		{
			if(!args)
			{
				return;
			}

			Object* parent = (Object*)args;
			auto hitbox = &(parent->hitbox);
			hitbox->pos.x = parent->pos.x;
			hitbox->pos.y = parent->pos.y;
		},

		obj2
	);

	//start rendering
	engine.StartMainLoop();
	return 0;
}
