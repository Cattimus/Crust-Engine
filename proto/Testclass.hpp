#pragma once

#include <vector>
#include <string>
using namespace std;

#include "Event.hpp"

class Testclass 
{
public:
	int x;
	int y;
	int w;
	int h;

	vector<Event<Testclass>> events;

	Testclass()
	{
		x = 0;
		y = 0;
		w = 0;
		h = 0;
	}

	Testclass(int x, int y, int w, int h)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}

	//register a new event
	void RegisterEvent(bool (*condition)(Testclass*), void (*action)(Testclass*), string name)
	{
		events.push_back(Event<Testclass>(this, name, condition, action));
	}
};