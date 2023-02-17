#pragma once

#include<iostream>
using namespace std;

#include "Texture.hpp"

class Object
{
private:
	uint id;
	Texture* tex;

	int    pos[2];
	double vel[2];
	int    size[2];

	//logic step callback
	void (*LogicCallback)(int*, double*, int*) = NULL;
	void (*LogicCallbackDelta)(double, int*, double*, int*) = NULL;

	/*
	//default logic step
	void DefaultLogic();
	void DefaultLogic(double delta);
	*/

	void Init();

public:
	int renderPriority;
	bool visible;

	//constructors(visible)
	Object(uint id, Texture* tex, int x, int y, int w, int h);
	Object(uint id, Texture* tex, int w, int h);
	Object(uint id, Texture* tex);

	//constructors(position only)
	Object(uint id, int x, int y, int w, int h);
	Object(uint id, int w, int h);
	Object(uint id);
	~Object(); //decrease refcount on texture

	uint GetID();

	//position functions
	void SetPosition(int x, int y);
	int  GetXPosition();
	int  GetYPosition();

	//velocity functions
	void   SetVelocity(double x, double y);
	double GetXVelocity();
	double GetYVelocity();

	//size functions
	void SetSize(int w, int h);
	int  GetWidth();
	int  GetHeight();

	//texture functions
	SDL_Texture* GetTexture();
	Texture* GetTextureObject();

	//logic
	void RegisterLogicCallback(void (*)(int*, double*, int*));
	void RegisterLogicCallbackDelta(void (*)(double, int*, double*, int*));

	void LogicStep();
	void LogicStep(double delta);
};