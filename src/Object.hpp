#pragma once

#include<iostream>
using namespace std;

#include "Texture.hpp"

class Object
{
private:

	//Unique ID for the object (at least in the scene)
	uint id;

	//Pointer to the texture object that will be used for rendering
	Texture* tex;

	//Position data (x,y)
	int    pos[2];

	//Velocity data (x,y)
	double vel[2];

	//Size data (w,h)
	int    size[2];

	//logic step callback
	//Parameters: position data(x,y), velocity data(x,y), size data(w,h)
	void (*LogicCallback)(int*, double*, int*);

	//Logic step callback
	//Parameters: delta value, position data(x,y), velocity data(x,y), size data(w,h)
	void (*LogicCallbackDelta)(double, int*, double*, int*);

	//Default logic step
	void DefaultLogic();
	//Default logic step (with delta time)
	void DefaultLogic(double delta);

	//Helper functions to initialize values
	void Init();

public:
	//Should this object be rendered in front of(+) or behind(-) other objects
	int renderPriority;
	//Should this object be rendered
	bool visible;

//////////////CONSTRUCTORS - VISIBLE OBJECT////////////////////////////

	Object(uint id, Texture* tex, int x, int y, int w, int h);
	Object(uint id, Texture* tex, int w, int h);
	Object(uint id, Texture* tex);

/////////////CONSTRUCTORS - POSITION ONLY/////////////////////////

	Object(uint id, int x, int y, int w, int h);
	Object(uint id, int w, int h);
	Object(uint id);

	//Decrease refcount on texture to make sure it is deleted
	~Object();

	//Return the object ID
	uint GetID();

////////////////POSITION FUNCTIONS//////////////////////////////

	void SetPosition(int x, int y);
	int  GetXPosition();
	int  GetYPosition();

//////////////////////VELOCITY FUNCTIONS//////////////////////////

	void   SetVelocity(double x, double y);
	double GetXVelocity();
	double GetYVelocity();

/////////////////////SIZE FUNCTIONS////////////////////////////

	void SetSize(int w, int h);
	int  GetWidth();
	int  GetHeight();

///////////////////TEXTURE FUNCTIONS//////////////////////////

	//Return the SDL_Texture* for rendering
	SDL_Texture* GetTexture();

	//Return the Texture object
	Texture* GetTextureObject();

//////////////////////LOGIC CALLBACKS////////////////////////////

	//Register the callback that will be activated on a logic step
	void RegisterLogicCallback(void (*)(int*, double*, int*));
	//Deactivate the callback that will be activated on every logic step
	void ClearLogicCallback();

	//Register the callback that will be activated on a logic step (with delta time)
	void RegisterLogicCallbackDelta(void (*)(double, int*, double*, int*));
	//Deactivate teh callback that will be activated on every logic step (with delta time)
	void ClearLogicCallbackDelta();

	//Function that will be executed on logic step
	void LogicStep();
	//Function that will be executed on logic step (with delta time)
	void LogicStep(double delta);
};