#pragma once

#include "Position.hpp"
#include "SDL.h"

class Hitbox : Position
{
private:
	bool debug;
	int debugColor[3];

public:
	Hitbox();
	Hitbox(double x, double y);
	Hitbox(double x, double y, int w, int h);

	bool IsColliding(Hitbox& b);

///////////////DEBUG RENDERING//////////////////
	void EnableDebug();
	void DisableDebug();
	void SetDebugColor(int r, int g, int b);
	int* GetDebugColor();

	virtual void Render(SDL_Renderer* r);
};