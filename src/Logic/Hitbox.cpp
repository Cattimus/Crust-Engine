#include "Logic/Hitbox.hpp"

#include "iostream"
using namespace std;

void Hitbox::Init()
{
	debug = false;
	r = 0;
	g = 0;
	b = 0;
	opacity = 0.5;
}

Hitbox::Hitbox() : Position()
{
	Init();
}

Hitbox::Hitbox(double x, double y) : Position(x,y)
{
	Init();
}

Hitbox::Hitbox(double x, double y, int w, int h) : Position(x,y,w,h)
{
	Init();
}

bool Hitbox::IsColliding(Hitbox& b)
{
	//AABB collision detection
	bool xOverlap = x + w >= b.x && b.x + b.w >= x;
	bool yOverlap = y + h >= b.y && b.y + b.h >= y;

	return xOverlap && yOverlap;
}

void Hitbox::SetDebugColor(uint r, uint g, uint b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

void Hitbox::Render(SDL_Renderer* r)
{
	if(!r)
	{
		return;
	}

	//Construct an SDL_Rect for the object based on position and size
	SDL_Rect objPos
	{
		.x = (int)x,
		.y = (int)y,
		.w = w,
		.h = h
	};

	//set draw color of rect
	SDL_SetRenderDrawColor(r, this->r, g, b, 255 * opacity);

	//Render to the screen
	SDL_RenderFillRect(r, &objPos);
}