#include "Objects/Object.hpp"

void Object::Init(uint id, Texture* tex)
{
	this->id = id;

	//Move should automatically activate every loop
	events.RegisterEvent(Event<Object>(this, "Move"));
	events.GetEvent("Move")->autoExec = true;

	events.RegisterEvent(Event<Object>(this, "Collision"));
	events.RegisterEvent(Event<Object>(this, "Deleted"));

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

Object::Object(uint id, Texture* tex, int x, int y, int w, int h)
{
	Init(id, tex);
	pos = Position(x,y,w,h);
	
}
Object::Object(uint id, Texture* tex, int w, int h)
{
	Init(id, tex);
	pos = Position(0,0,w,h);

}

Object::Object(uint id, Texture* tex)
{
	Init(id, tex);
}

Object::Object(uint id)
{
	Init(id, NULL);
}

uint Object::GetID()
{
	return id;
}

EventHandler<Object>* Object::GetEventHandler()
{
	return &events;
}

bool Object::IsCollidingWith(Object& b)
{
	return false;
}

Hitbox* Object::GetHitbox()
{
	return &hitbox;	
}

void Object::Render(SDL_Renderer* r)
{
	if(!r || !tex)
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
