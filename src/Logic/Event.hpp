#pragma once

#include <string>
#include <iostream>
using namespace std;

#include "Logic/Action.hpp"
#include "Logic/Condition.hpp"

class Event
{
private:
	string name;


	//Helper function to null-initialize all values
	void Init()
	{
		this->name = "";
		this->debug = false;
		this->autoExec = false;
	}

public:
	bool debug;
	bool autoExec;
	Action action;
	Condition condition;

	Event(string name, bool (*condition)(void*), void* condArgs, void (*action)(void*), void* actArgs)
	{
		Init();
		this->name = name;
		autoExec = true;

		//Initialize action and condition
		this->action = Action(action, actArgs);
		this->condition = Condition(condition, condArgs);
	}

	Event(string name)
	{
		Init();
		this->name = name;
	}

	Event()
	{
		Init();
	}

	//Check to see if condition is true, if it is, activate action
	void Check()
	{
		if(!autoExec)
		{
			return;
		}

		//perform action by default if condition is unset
		if(!condition.IsSet())
		{
			if(debug)
			{
				cout << "Event: [" << name << "] is activating.\n";
			}

			action.ExecuteWithArgs();
		}

		//perform action if condition is met
		else if(condition.ExecuteWithArgs())
		{
			if(debug)
			{
				cout << "Event [" << name << "] is activating.\n";
			}

			action.ExecuteWithArgs();
		}
	}

	string GetName()
	{
		return name;
	}
};
