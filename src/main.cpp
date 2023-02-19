#include <iostream>
using namespace std;

#include "Engine.hpp"

double maxVeloc = 500;
Object* controlled;
Scene* active;
Engine engine;

void logicDelta(double delta, CrustObjData self) 
{
	*self.x += (*self.velX * (delta / (double)1000));
	*self.y += (*self.velY * (delta / (double)1000));
	*self.rotation += (*self.rotVeloc * (delta / (double)1000));
}

//spawn a new cat on click
void mouseClick(bool pressed, int button, int clicks, int x, int y)
{
	if(pressed && button)
	{
		//spawn new cat
		Object* newcat = active->CreateObject(controlled->GetTextureObject()->GetPath(), x, y, controlled->GetWidth(), controlled->GetHeight());

		//match rotation velocity of the current one
		newcat->SetRotation(controlled->GetRotation());
		newcat->SetRotationVelocity(controlled->GetRotationVelocity());
		controlled = newcat;
	}
} 

void keyboard(bool pressed, char key)
{
	switch(key)
	{
		case 'w':
		{
			double x = controlled->GetXVelocity();
			double y = maxVeloc * -1;

			controlled->SetVelocity(x, (pressed) ? y : 0);
			break;
		}

		case 's':
		{
			double x = controlled->GetXVelocity();
			double y = maxVeloc;

			controlled->SetVelocity(x, (pressed) ? y : 0);
			break;
		}

		case 'a':
		{
			double x = maxVeloc * -1;
			double y = controlled->GetYVelocity();
			
			controlled->SetVelocity((pressed) ? x : 0, y);
			break;
		}
		
		case 'd':
		{
			double x = maxVeloc;
			double y = controlled->GetYVelocity();
			
			controlled->SetVelocity((pressed) ? x : 0, y);
			break;
		}

		case 'r':
		{
			controlled->SetRotationVelocity(controlled->GetRotationVelocity() + 5);
			break;
		}

		case 'z':
		{
			controlled->SetRotationVelocity(controlled->GetRotationVelocity() - 5);
			break;
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
	engine.CreateWindow("Crust engine demo", true);
	Scene* scene = engine.CreateScene("main");
	Object* obj = scene->CreateObject("../media/test.png", 200, 100, 250, 250);
	controlled = obj;

	//set up callbacks for user input
	engine.RegisterKeyboardCallback(keyboard);
	engine.RegisterMouseClickCallback(mouseClick);

	//set up logic for our object
	obj->RegisterLogicCallbackDelta(logicDelta);

	//start rendering
	engine.StartMainLoop();
	return 0;
}