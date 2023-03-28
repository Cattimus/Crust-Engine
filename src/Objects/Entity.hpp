#pragma once

#include <iostream>
#include <unordered_map>
using namespace std;

#include <SDL.h>

#include "Objects/Texture.hpp"
#include "Objects/Object.hpp"
#include "Controllers/EventHandler.hpp"
#include "Logic/Position.hpp"
#include "Logic/Hitbox.hpp"

class Entity final : public Object
{
	//Unique ID for the object (at least in the scene)
	uint id;

	//Pointer to the texture object that will be used for rendering
	Texture* tex;

	void Init(Texture* tex);

	Hitbox hitbox;

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

	//Render object
	void Render(SDL_Renderer* r);
	Hitbox* GetHitbox();
};