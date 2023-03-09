#pragma once

#include <iostream>
#include <unordered_map>
using namespace std;

#include "Texture.hpp"
#include "Event.hpp"

class Object
{
private:

	//Unique ID for the object (at least in the scene)
	uint id;

	//Pointer to the texture object that will be used for rendering
	Texture* tex;

	//Position data (x,y)
	double pos[2];

	//Center of rotation
	double centerOffset[2];

	//Velocity data (x,y)
	double vel[2];

	//Size data (w,h)
	int    size[2];

	double rotation;
	double rotVeloc;

	//Collection of all events sorted by name
	unordered_map<string, Event<Object>> events;

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

//////////////////////ROTATION////////////////////////////////

	void SetRotation(double rotation);
	double GetRotation();

	void SetRotationVelocity(double rotVeloc);
	double GetRotationVelocity();

	void SetRotationOffset(double x, double y);
	double GetRotationOffsetX();
	double GetRotationOffsetY();

///////////////////TEXTURE FUNCTIONS//////////////////////////

	//Return the SDL_Texture* for rendering
	SDL_Texture* GetTexture();

	//Return the Texture object
	Texture* GetTextureObject();

//////////////////EVENT FUNCTIONS///////////////////////////

	void RegisterEvent(Event<Object> event);
	Event<Object>* GetEvent(string name);
	void DeleteEvent(string name);
	void CheckEvents();
};