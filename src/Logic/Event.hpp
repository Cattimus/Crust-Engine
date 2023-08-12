#pragma once

#include <string>
#include <iostream>
using namespace std;

class Event
{
private:
	string name;

	//Condition check arguments
	void* condArgs;

	//action arguments
	void* actArgs;

	//Function pointer to condition
	bool (*condition)(void* args);

	//Function pointer to action
	void (*action)(void* args);

	//Helper function to null-initialize all values
	void Init()
	{
		this->condArgs = nullptr;
		this->actArgs = nullptr;
		this->name = "";
		this->condition = nullptr;
		this->action = nullptr;
		this->debug = false;
		this->autoExec = false;
	}

public:
	bool debug;
	bool autoExec;

	Event(string name, bool (*condition)(void*), void* condArgs, void (*action)(void*), void* actArgs)
	{
		Init();
		this->condArgs = condArgs;
		this->actArgs = actArgs;
		this->name = name;
		this->condition = condition;
		this->action = action;
		autoExec = true;
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

	//Register condition
	void RegisterCondition(bool (*func)(void*))
	{
		condition = func;
	}

	void RegisterCondition(bool (*func)(void*), void* args)
	{
		condition = func;
		condArgs = args;
	}

	void ConditionArgs(void* args)
	{
		condArgs = args;
	}

	//Register action
	void RegisterAction(void (*func)(void*))
	{
		action = func;
	}

	void RegisterAction(void (*func)(void*), void* args)
	{
		action = func;
		actArgs = args;
	}

	void ActionArgs(void* args)
	{
		actArgs = args;
	}

	//Check to see if condition is true, if it is, activate action
	void Check()
	{
		if(!autoExec)
		{
			return;
		}

		//check for null parent or action
		if(!(action))
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

			action(actArgs);
		}

		//perform action if condition is met
		else if(condition(condArgs))
		{
			if(debug)
			{
				cout << "Event [" << name << "] is activating.\n";
			}

			action(actArgs);
		}
	}

	//Activate event without a condition check
	void Activate()
	{
		//check for null action
		if(!(action))
		{
			return;
		}

		if(debug)
		{
			cout << "Event [" << name << "] is activating.\n";
		}

		action(actArgs);
	}

	string GetName()
	{
		return name;
	}
};
