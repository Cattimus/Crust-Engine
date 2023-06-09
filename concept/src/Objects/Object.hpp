#pragma once

#include <iostream>
#include <unordered_map>
using namespace std;

#include <SDL2/SDL.h>

#include "Controllers/EventHandler.hpp"
#include "Logic/Position.hpp"
#include "Logic/Hitbox.hpp"

class Object : public Position
{
private:

	//Unique ID for the object (at least in the scene)
	uint id;

	//Collection of all events sorted by name
	EventHandler<Object> events;

	void Init(uint id);

public:
	Object(uint id, int x, int y, int w, int h);
	Object(uint id, int w, int h);
	Object(uint id);

	virtual ~Object(){};

	//Return the object ID
	uint GetID();

	EventHandler<Object>* GetEventHandler();

	virtual void Render(SDL_Renderer* r);
	virtual Hitbox* GetHitbox(){return NULL;};

//////////////////////COLLISIONS///////////////////////////

	bool IsCollidingWith(Object& b);

};