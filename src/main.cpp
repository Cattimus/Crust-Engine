#include <iostream>
using namespace std;

#include "Engine.hpp"

Object* controlled;
double maxVeloc = 500;

void logicDelta(double delta, CrustObjData self) 
{
	*self.x += (*self.velX * (delta / (double)1000));
	*self.y += (*self.velY * (delta / (double)1000));
}

void keyboard(bool pressed, char key)
{
	switch(key)
	{
		case 'w':
		{
			double x = controlled->GetXVelocity();
			double y = maxVeloc * -1;

			controlled->SetVelocity(x, (pressed) ? 0 : y);
			break;
		}

		case 's':
		{
			double x = controlled->GetXVelocity();
			double y = maxVeloc;

			controlled->SetVelocity(x, (pressed) ? 0 : y);
			break;
		}

		case 'a':
		{
			double x = maxVeloc * -1;
			double y = controlled->GetYVelocity();
			
			controlled->SetVelocity((pressed) ? 0 : x, y);
			break;
		}
		
		case 'd':
		{
			double x = maxVeloc;
			double y = controlled->GetYVelocity();
			
			controlled->SetVelocity((pressed) ? 0 : x, y);
			break;
		}
	}
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
	controlled = obj;

	//set up callbacks for user input
	engine.RegisterKeyboardCallback(keyboard);

	//set up logic for our object
	obj->RegisterLogicCallbackDelta(logicDelta);

	//start rendering
	engine.StartMainLoop();
	return 0;
}