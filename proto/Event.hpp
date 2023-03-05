#pragma once

#include <string>
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


public:
	Event(T* parent, string name, bool (*condition)(T*), void (*action)(T*))
	{
		this->parent = parent;
		this->name = name;
		this->condition = condition;
		this->action = action;
	}

	Event(T* parent, string name)
	{
		this->parent = parent;
		this->name = name;
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

	void Check()
	{
		//check for null condition or action
		if(!(condition && action))
		{
			return;
		}

		//perform action if condition is met
		if(condition(parent))
		{
			cout << "Event: " << name << " is activating.\n";
			action(parent);
		}
	}
};