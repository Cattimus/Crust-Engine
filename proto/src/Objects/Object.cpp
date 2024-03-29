#include "Objects/Object.hpp"

void Object::Init(uint32_t id, Texture* tex)
{
	this->id = id;

	//Move should automatically activate every loop
	events.RegisterEvent(Event("Move"));
	events.GetEvent("Move")->autoExec = true;

	events.RegisterEvent(Event("Collision"));
	events.RegisterEvent(Event("Deleted"));

	if(tex)
	{
		this->tex = tex;
		tex->RefInc();
		renderPriority = 0;
		visible = true;
	}
	else
	{
		this->tex = nullptr;
		renderPriority = 0;
		visible = false;
	}
}

Object::Object(uint32_t id, Texture* tex, int x, int y, int w, int h)
{
	Init(id, tex);
	pos = Position(x,y,w,h);
	hitbox = Hitbox(x,y,w,h);
	
}
Object::Object(uint32_t id, Texture* tex, int w, int h)
{
	Init(id, tex);
	pos = Position(0,0,w,h);
	hitbox = Hitbox(0,0,w,h);
}

Object::Object(uint32_t id, Texture* tex)
{
	Init(id, tex);
}

Object::Object(uint32_t id)
{
	Init(id, nullptr);
}

uint32_t Object::GetID()
{
	return id;
}

bool Object::IsCollidingWith(Object& b)
{
	return false;
}

void Object::Render(SDL_Renderer* r)
{
	if(!r || !tex || !visible)
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

	//calculate center of object
	SDL_Point center;
	center.x = (pos.w / (float)2) + pos.centerOffsetX;
	center.y = (pos.h / (float)2) + pos.centerOffsetY;

	//Render to the screen
	SDL_RenderCopyEx(r, tex->Get(), NULL, &objPos, pos.GetRotation(), &center, SDL_FLIP_NONE);

	//Render hitbox
	hitbox.Render(r);
}

SDL_Texture* Object::GetTexture()
{
	return tex->Get();
}

Texture* Object::GetTextureObject()
{
	return tex;
}

Object::~Object()
{
	if(tex)
	{
		tex->RefDec();
	}
}
