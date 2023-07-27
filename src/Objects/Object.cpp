#include "Objects/Object.hpp"

void Object::Init(uint id)
{
	this->id = id;

	//Move should automatically activate every loop
	events.RegisterEvent(Event<Object>(this, "Move"));
	events.GetEvent("Move")->autoExec = true;

	events.RegisterEvent(Event<Object>(this, "Collision"));
	events.RegisterEvent(Event<Object>(this, "Deleted"));
}

Object::Object(uint id, int x, int y, int w, int h)
{
	Init(id);

	position.x = x;
	position.y = y;
	position.w = w;
	position.h = h;
}
Object::Object(uint id, int w, int h)
{
	Init(id);

	position.x = 0;
	position.y = 0;
	position.w = w;
	position.h = h;
}

Object::Object(uint id)
{
	Init(id);
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

void Object::Render(SDL_Renderer* r)
{

}
