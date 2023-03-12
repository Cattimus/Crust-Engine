#include "Object.hpp"

Object::Object(uint id, int x, int y, int w, int h) : Position(x,y,w,h)
{
	this->id = id;
}
Object::Object(uint id, int w, int h) : Position(x,y)
{
	this->id = id;
}

Object::Object(uint id) : Position()
{
	this->id = id;
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
	
}