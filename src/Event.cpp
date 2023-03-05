#include "Event.hpp"

template <typename T>
Event<T>::Event(T* parent, string name, bool (*condition)(T*), void (*action)(T*))
{
	this->parent = parent;
	this->name = name;
	this->condition = condition;
	this->action = action;
}

template <typename T>
Event<T>::Event(T* parent, string name)
{
	this->parent = parent;
	this->name = name;
}

template <typename T>
void Event<T>::RegisterCondition(bool (*func)(T*))
{
	condition = func;
}

template <typename T>
void Event<T>::RegisterAction(void (*func)(T*))
{
	action = func;
}

template <typename T>
void Event<T>::Check()
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