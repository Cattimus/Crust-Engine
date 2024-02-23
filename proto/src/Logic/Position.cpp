#include "Logic/Position.hpp"

void Position::Init()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	velX = 0;
	velY = 0;
	velR = 0;
	rotation = 0;
	centerOffsetX = 0;
	centerOffsetY = 0;
}

Position::Position()
{
	Init();
}
	
Position::Position(double x, double y)
{
	Init();
	this->x = x;
	this->y = y;
}

Position::Position(double x, double y, int w, int h)
{
	Init();
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

void Position::Rotate(double r)
{
	rotation += r;

	//Control the maximum value of rotation
	if(rotation >= 360)
	{
		rotation -= 360;
	}
	else if (rotation <= 0)
	{
		rotation += 360;
	}
}

void Position::RotateStep(double delta)
{
	Rotate(velR * delta);
}

double Position::GetRotation()
{
	return rotation;
}

void Position::Move(double x, double y)
{
	this->x += x;
	this->y += y;
}

void Position::MoveStep(double delta)
{
	this->x += (velX * delta);
	this->y += (velY * delta);
}