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
	Event(T* parent, string name, bool (*condition)(T*), void (*action)(T*));
	Event(T* parent, string name);

	//Register condition
	void RegisterCondition(bool (*func)(T*));

	//Register action
	void RegisterAction(void (*func)(T*));

	//Check to see if condition is true, if it is, activate action
	void Check();
};