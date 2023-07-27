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

Entity::Entity(uint id, Texture* tex, int x, int y, int w, int h) : object(id, x, y, w, h)
{
	Init(tex);

	hitbox = Hitbox(x,y,w,h);
}

Entity::Entity(uint id, Texture* tex, int w, int h) : object(id, w, h)
{
	Init(tex);

	hitbox = Hitbox(0,0,w,h);
}

//WARNING - this can cause problems if a null value is passed to this
Entity::Entity(uint id, Texture* tex) : object(id, 0, 0,tex->GetWidth(), tex->GetHeight())
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
		.x = (int)object.position.x,
		.y = (int)object.position.y,
		.w = object.position.w,
		.h = object.position.h
	};

	//calculate center of object
	SDL_Point center;
	center.x = (object.position.w / (float)2) + object.position.centerOffsetX;
	center.y = (object.position.h / (float)2) + object.position.centerOffsetY;

	//Render to the screen
	SDL_RenderCopyEx(r, tex->Get(), NULL, &objPos, object.position.GetRotation(), &center, SDL_FLIP_NONE);

	//Render hitbox
	hitbox.Render(r);
}
