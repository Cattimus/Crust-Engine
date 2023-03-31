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

Object::Object(uint id, int x, int y, int w, int h) : Position(x,y,w,h)
{
	Init(id);
}
Object::Object(uint id, int w, int h) : Position(0,0,w,h)
{
	Init(id);
}

Object::Object(uint id) : Position()
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