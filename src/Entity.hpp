#pragma once

#include <iostream>
#include <unordered_map>
using namespace std;

#include "Texture.hpp"
#include "Object.hpp"
#include "EventHandler.hpp"
#include "Position.hpp"

class Entity : public Object
{

	//Unique ID for the object (at least in the scene)
	uint id;

	//Pointer to the texture object that will be used for rendering
	Texture* tex;

	//Collection of all events sorted by name
	EventHandler<Entity> events;

	void Init(Texture* tex);

public:
	//Should this object be rendered in front of(+) or behind(-) other objects
	int renderPriority;

	//Should this object be rendered
	bool visible;

	Entity(uint id, Texture* tex, int x, int y, int w, int h);
	Entity(uint id, Texture* tex, int w, int h);
	Entity(uint id, Texture* tex);

	//Decrease refcount on texture to make sure it is deleted
	~Entity();

///////////////////TEXTURE FUNCTIONS//////////////////////////

	//Return the SDL_Texture* for rendering
	SDL_Texture* GetTexture();

	//Return the Texture object
	Texture* GetTextureObject();

//////////////////EVENT FUNCTIONS///////////////////////////

	EventHandler<Entity>* GetEventHandler();

//////////////////////COLLISIONS///////////////////////////

	bool IsCollidingWith(Entity& b);
};