#pragma once

#include "Logic/Position.hpp"
#include <SDL2/SDL.h>

class Hitbox
{
private:
	void Init();

public:
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
	float opacity = 0;
	bool debug;
	
	Position position;

	Hitbox();
	Hitbox(double x, double y);
	Hitbox(double x, double y, int w, int h);

	virtual ~Hitbox(){};

	bool IsColliding(Hitbox& b);
	void SetDebugColor(uint r, uint g, uint b);

///////////////DEBUG RENDERING//////////////////

	virtual void Render(SDL_Renderer* r);
};
