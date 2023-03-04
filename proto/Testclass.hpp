#pragma once

class Testclass 
{
public:
	int x;
	int y;
	int w;
	int h;

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

};