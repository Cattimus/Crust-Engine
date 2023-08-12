#pragma once

#include <string>
#include <iostream>
using namespace std;

class Event
{
private:
	string name;

	//Pointer to the arguments to condition and action (usually the parent object)
	void* args;

	//Function pointer to condition
	bool (*condition)(void* args);

	//Function pointer to action
	void (*action)(void* args);

	//Helper function to null-initialize all values
	void Init()
	{
		this->args = nullptr;
		this->name = "";
		this->condition = nullptr;
		this->action = nullptr;
		this->debug = false;
		this->autoExec = false;
	}

public:
	bool debug;
	bool autoExec;

	Event(void* args, string name, bool (*condition)(void*), void (*action)(void*))
	{
		Init();
		this->args = args;
		this->name = name;
		this->condition = condition;
		this->action = action;
		autoExec = true;
	}

	Event(void* parent, string name)
	{
		Init();
		this->args = parent;
		this->name = name;
	}

	Event()
	{
		Init();
	}

	//Register condition
	void RegisterCondition(bool (*func)(void*))
	{
		condition = func;
	}

	//Register action
	void RegisterAction(void (*func)(void*))
	{
		action = func;
	}

	//Check to see if condition is true, if it is, activate action
	void Check()
	{
		if(!autoExec)
		{
			return;
		}

		//check for null parent or action
		if(!(action && args))
		{
			return;
		}

		//perform action by default if condition is unset
		if(!condition)
		{
			if(debug)
			{
				cout << "Event: [" << name << "] is activating.\n";
			}

			action(args);
		}

		//perform action if condition is met
		else if(condition(args))
		{
			if(debug)
			{
				cout << "Event [" << name << "] is activating.\n";
			}

			action(args);
		}
	}

	//Activate event without a condition check
	void Activate()
	{
		//check for null parent or action
		if(!(action && args))
		{
			return;
		}

		if(debug)
		{
			cout << "Event [" << name << "] is activating.\n";
		}

		action(args);
	}

	string GetName()
	{
		return name;
	}
};
