#pragma once

#include <unordered_map>
using namespace std;

#include "Logic/Event.hpp"

class EventHandler
{
private:
	unordered_map<string, Event> events;

public:
	//Register a new event
	void RegisterEvent(Event event)
	{
		events[event.GetName()] = event;
	}

	//Get a reference to an existing event
	Event* GetEvent(string name)
	{
		if(events.find(name) == events.end())
		{
			return NULL;
		}

		return &events[name];
	}

	//Remove an event
	void DeleteEvent(string name)
	{
		//Event does not exist
		if(events.find(name) == events.end())
		{
			return;
		}

		events.erase(events.find(name));
	}

	//Check all events
	void CheckEvents()
	{
		//Perform event actions for scene
		for(auto &i : events) 
		{
			i.second.Check();
		}
	}

	//Activate an event without checking condition
	void DoEvent(string name)
	{
		if(events.find(name) == events.end())
		{
			return;
		}

		events[name].action.ExecuteWithArgs();
	}

};