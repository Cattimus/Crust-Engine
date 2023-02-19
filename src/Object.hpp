#pragma once

#include<iostream>
using namespace std;

#include "Texture.hpp"

typedef struct CrustObjData
{
	double* x;
	double* y;

	double* velX;
	double* velY;

	int* w;
	int* h;
}CrustObjData;

//Parameters: object data (position and velocity)
typedef void (*LogicFunc)(CrustObjData);

//Parameters: delta time, object data (position and velocity)
typedef void (*LogicFuncDelta)(double, CrustObjData);

//Parameters: object data self, object data collide
typedef void (*CollisionFunc)(CrustObjData, CrustObjData);

class Object
{
private:

	//Unique ID for the object (at least in the scene)
	uint id;

	//Pointer to the texture object that will be used for rendering
	Texture* tex;

	//Position data (x,y)
	double pos[2];

	//Velocity data (x,y)
	double vel[2];

	//Size data (w,h)
	int    size[2];

	//Logic step callback
	LogicFunc OnLogicStep; 

	//Logic step callback(with delta time)
	LogicFuncDelta OnLogicStepDelta;

	//Collision callback
	CollisionFunc OnCollision;


	//Default logic step
	void DefaultLogic();
	//Default logic step (with delta time)
	void DefaultLogic(double delta);

	//Helper functions to initialize values
	void Init();

	CrustObjData GetData();

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

	void SetPosition(double x, double y);
	double  GetXPosition();
	double  GetYPosition();

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
	void RegisterLogicCallback(LogicFunc func);
	//Deactivate the callback that will be activated on every logic step
	void ClearLogicCallback();

	//Register the callback that will be activated on a logic step (with delta time)
	void RegisterLogicCallbackDelta(LogicFuncDelta func);
	//Deactivate the callback that will be activated on every logic step (with delta time)
	void ClearLogicCallbackDelta();

	//Register the callback that will be activated when an object collides with another
	void RegisterCollisionCallback(CollisionFunc func);
	//Deactivate the callback that will be activated when an object collides with another
	void ClearCollisionCallback();

	//Function that will be executed on logic step
	void LogicStep();
	//Function that will be executed on logic step (with delta time)
	void LogicStep(double delta);

	//Function that will execute when objects have collided
	void Collision(Object& B);
};