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

	pos.x = x;
	pos.y = y;
}

Hitbox::Hitbox(double x, double y, int w, int h)
{
	Init();

	pos.x = x;
	pos.y = y;
	pos.w = w;
	pos.h = h;
}

bool Hitbox::IsColliding(Hitbox& b)
{
	//AABB collision detection
	bool xOverlap = pos.x + pos.w >= b.pos.x && b.pos.x + b.pos.w >= pos.x;
	bool yOverlap = pos.y + pos.h >= b.pos.y && b.pos.y + b.pos.h >= pos.y;

	return xOverlap && yOverlap;
}


bool Hitbox::PointOverlaps(double x, double y)
{
	bool xOverlap = (pos.x + pos.w >= x) && (x >= pos.x);
	bool yOverlap = (pos.y + pos.h >= y) && (y >= pos.y);

	return xOverlap && yOverlap;
}

void Hitbox::SetDebugColor(uint32_t r, uint32_t g, uint32_t b)
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
		.x = (int)pos.x,
		.y = (int)pos.y,
		.w = pos.w,
		.h = pos.h
	};

	//set draw color of rect
	SDL_SetRenderDrawColor(r, this->r, g, b, 255 * opacity);

	//Render to the screen
	SDL_RenderFillRect(r, &objPos);
}
