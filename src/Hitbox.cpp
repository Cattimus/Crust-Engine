#include "Hitbox.hpp"

Hitbox::Hitbox() : Position()
{
	debug = false;
}

Hitbox::Hitbox(double x, double y) : Position(x,y)
{
	debug = false;
}

Hitbox::Hitbox(double x, double y, int w, int h) : Position(x,y,w,h)
{
	
}

bool Hitbox::IsColliding(Hitbox& b)
{
	return false;
}


void Hitbox::EnableDebug()
{
	debug = true;
}

void Hitbox::DisableDebug()
{
	debug = false;
}

void Hitbox::SetDebugColor(int r, int g, int b)
{
	debugColor[0] = r;
	debugColor[1] = g;
	debugColor[2] = b;
}

int* Hitbox::GetDebugColor()
{
	return debugColor;
}