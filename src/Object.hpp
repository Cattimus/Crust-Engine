#pragma once

#include <iostream>
#include <unordered_map>
using namespace std;

#include "EventHandler.hpp"
#include "Position.hpp"

class Object : public Position
{
private:

	//Unique ID for the object (at least in the scene)
	uint id;

	//Collection of all events sorted by name
	EventHandler<Object> events;

public:
	Object(uint id, int x, int y, int w, int h);
	Object(uint id, int w, int h);
	Object(uint id);

	//Return the object ID
	uint GetID();

	EventHandler<Object>* GetEventHandler();

//////////////////////COLLISIONS///////////////////////////

	bool IsCollidingWith(Object& b);

};