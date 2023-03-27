#pragma once

class Position
{
private:
	//Rotation value
	double rotation;

	void Init();

public:

	//Coordinate positions

	double x;
	double y;

	//Object size

	int w;
	int h;

	//Offset from center

	double centerOffsetX;
	double centerOffsetY;

	//Velocity (x horizontal, y vertical, r rotational)

	double velX;
	double velY;
	double velR;

////////////////////////////CONSTRUCTORS///////////////////////

	Position();
	Position(double x, double y);
	Position(double x, double y, int w, int h);

///////////////////ROTATION FUNCTIONS//////////////////////////

	void Rotate(double r);
	void RotateStep(double delta);
	double GetRotation();

/////////////////MOVEMENT FUNCTIONS////////////////////////////

	void Move(double x, double y);
	void MoveStep(double delta);
};