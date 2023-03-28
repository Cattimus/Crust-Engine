#pragma once

#include <string>
#include <iostream>
using namespace std;

template <typename T>
class Event
{
private:
	string name;

	//Pointer to parent object that the event will act upon
	T* parent;

	//Function pointer to condition
	bool (*condition)(T* parent);

	//Function pointer to action
	void (*action)(T* parent);



	//Helper function to null-initialize all values
	void init()
	{
		this->parent = NULL;
		this->name = "";
		this->condition = NULL;
		this->action = NULL;
		this->debug = false;
		this->autoExec = false;
	}

public:
	bool debug;
	bool autoExec;

	Event(T* parent, string name, bool (*condition)(T*), void (*action)(T*))
	{
		init();
		this->parent = parent;
		this->name = name;
		this->condition = condition;
		this->action = action;
		autoExec = true;
	}

	Event(T* parent, string name)
	{
		init();
		this->parent = parent;
		this->name = name;
	}

	Event()
	{
		init();
	}

	//Register condition
	void RegisterCondition(bool (*func)(T*))
	{
		condition = func;
	}

	//Register action
	void RegisterAction(void (*func)(T*))
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
		if(!(action && parent))
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

			action(parent);
		}

		//perform action if condition is met
		else if(condition(parent))
		{
			if(debug)
			{
				cout << "Event [" << name << "] is activating.\n";
			}

			action(parent);
		}
	}

	//Activate event without a condition check
	void Activate()
	{
		//check for null parent or action
		if(!(action && parent))
		{
			return;
		}

		if(debug)
		{
			cout << "Event [" << name << "] is activating.\n";
		}

		action(parent);
	}

	string GetName()
	{
		return name;
	}
};