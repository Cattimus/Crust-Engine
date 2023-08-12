#pragma once

#include <iostream>
#include <unordered_map>
using namespace std;

#include <SDL2/SDL.h>

#include "Controllers/EventHandler.hpp"
#include "Logic/Position.hpp"
#include "Logic/Hitbox.hpp"
#include "Objects/Texture.hpp"

//TODO - implement event where object can garbage collect itself
//TODO - change hitbox and textures to vectors (for animations and multiple hitboxes)
//TODO - property for "active"
//TODO - ability to link multiple objects together so they can be independantly controlled

class Object
{
private:
	//Unique ID for the object (at least in the scene)
	uint id;	

	//Pointer to the texture object that will be used for rendering
	Texture* tex;

	void Init(uint id, Texture* tex);	

public:
	//Collection of all events sorted by name
	EventHandler events;

	//Should this object be rendered in front of(+) or behind(-) other objects
	int renderPriority;

	//Should this object be rendered
	bool visible;

	Position pos;
	Hitbox hitbox;

	Object(uint id, Texture* tex, int x, int y, int w, int h);
	Object(uint id, Texture* tex, int w, int h);
	Object(uint id, Texture* tex);
	Object(uint id);

	//Return the object ID
	uint GetID();

//////////////////////COLLISIONS///////////////////////////

	bool IsCollidingWith(Object& b);

	//Decrease refcount on texture to make sure it is deleted
	~Object();

///////////////////TEXTURE FUNCTIONS//////////////////////////

	//Return the SDL_Texture* for rendering
	SDL_Texture* GetTexture();

	//Return the Texture object
	Texture* GetTextureObject();

	//Render object
	void Render(SDL_Renderer* r);
};
