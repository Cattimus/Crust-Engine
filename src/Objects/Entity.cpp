#include "Objects/Entity.hpp"

Entity::~Entity()
{
	if(tex)
	{
		tex->RefDec();
	}
}

void Entity::Init(Texture* tex)
{
	this->tex = tex;
	tex->RefInc();
	renderPriority = 0;
	visible = true;
}

Hitbox* Entity::GetHitbox()
{
	return &hitbox;
}

Entity::Entity(uint id, Texture* tex, int x, int y, int w, int h) : Object(id,x,y,w,h)
{
	Init(tex);
	hitbox.w = w;
	hitbox.h = h;
	hitbox.x = x;
	hitbox.y = y;
}

Entity::Entity(uint id, Texture* tex, int w, int h) : Object(id,0,0,w,h)
{
	Init(tex);
	hitbox.w = w;
	hitbox.h = h;
	hitbox.x = x;
	hitbox.y = y;
}

//WARNING - this can cause problems if a null value is passed to this
Entity::Entity(uint id, Texture* tex) : Object(id, 0, 0,tex->GetWidth(), tex->GetHeight())
{
	Init(tex);
}

void Entity::Render(SDL_Renderer* r)
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

	//calculate center of object
	SDL_Point center;
	center.x = (w / 2) + centerOffsetX;
	center.y = (h / 2) + centerOffsetY;

	//Render to the screen
	SDL_RenderCopyEx(r, tex->Get(), NULL, &objPos, GetRotation(), &center, SDL_FLIP_NONE);

	//Render hitbox
	hitbox.Render(r);
}