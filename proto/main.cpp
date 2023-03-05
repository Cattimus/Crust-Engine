#include <iostream>
using namespace std;

#include "Testclass.hpp"
#include "Event.hpp"

bool IsOffscreen(Testclass* t)
{
	if((t->x > 500 || t->x < 0) ||
	(t->y > 500 || t->y < 0))
	{
		return true;
	}

	return false;
}

void ResetPosition(Testclass* t)
{
	t->x = 0;
	t->y = 0;
}

int main()
{
	Testclass temp;
	temp.RegisterEvent(IsOffscreen, ResetPosition, "OffscreenEvent");

	for(int i = 0; i < 50000; i++)
	{
		temp.x += 1;
		temp.y += 1;
		temp.CheckEvents();
	}

	return 0;
}