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

Hitbox::Hitbox()
{
	Init();
}

Hitbox::Hitbox(double x, double y)
{
	Init();

	position.x = x;
	position.y = y;
}

Hitbox::Hitbox(double x, double y, int w, int h)
{
	Init();

	position.x = x;
	position.y = y;
	position.w = w;
	position.h = h;
}

bool Hitbox::IsColliding(Hitbox& b)
{
	//AABB collision detection
	bool xOverlap = position.x + position.w >= b.position.x && b.position.x + b.position.w >= position.x;
	bool yOverlap = position.y + position.h >= b.position.y && b.position.y + b.position.h >= position.y;

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
	if(!r || !debug)
	{
		return;
	}

	//Construct an SDL_Rect for the object based on position and size
	SDL_Rect objPos
	{
		.x = (int)position.x,
		.y = (int)position.y,
		.w = position.w,
		.h = position.h
	};

	//set draw color of rect
	SDL_SetRenderDrawColor(r, this->r, g, b, 255 * opacity);

	//Render to the screen
	SDL_RenderFillRect(r, &objPos);
}
