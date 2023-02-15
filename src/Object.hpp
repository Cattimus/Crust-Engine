#pragma once

#include<iostream>
using namespace std;

#include "Texture.hpp"

class Object
{
private:
	uint id = 0;
	Texture* tex = NULL;

	int    pos[2];
	double vel[2];
	int    size[2];

	//logic step callback
	void (*LogicCallback)() = NULL;

	//default logic step
	void DefaultLogic();
	
public:
	int renderPriority;
	bool visible;

	//constructors(visible)
	Object(uint id, string, int, int, int, int);
	Object(uint id, string, int, int);
	Object(uint id, string);

	//constructors(position only)
	Object(uint id, int, int, int, int);
	Object(uint id, int, int);
	Object(uint id){renderPriority = 0; visible = false; this->id = id;}; 

	uint GetID();

	//position functions
	void SetPosition(int, int);
	int  GetXPosition();
	int  GetYPosition();

	//velocity functions
	void   SetVelocity(double, double);
	double GetXVelocity();
	double GetYVelocity();

	//size functions
	void SetSize(int, int);
	int  GetWidth();
	int  GetHeight();

	//texture functions
	SDL_Texture* GetTexture();
	Texture* GetTextureObject();

	//logic
	void RegisterLogicCallback(void (*)());
	void LogicStep();
};