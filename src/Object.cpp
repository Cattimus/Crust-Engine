#include "Object.hpp"

void Object::Init()
{
	id = 0;
	tex = NULL;
	OnLogicStep = NULL;
	OnLogicStepDelta = NULL;
	SetPosition(0,0);
	SetSize(0,0);
	SetVelocity(0,0);
}

Object::~Object()
{
	//Decrease reference count if texture exists
	if(tex)
	{
		tex->RefDec();
	}
}

Object::Object(uint id, Texture* tex, int x, int y, int w, int h)
{
	Init();
	this->id = id;

	this->tex = tex;
	tex->RefInc();

	SetPosition(x,y);
	SetSize(w,h);
}
Object::Object(uint id, Texture* tex, int w, int h)
{
	Init();
	this->id = id;

	this->tex = tex;
	tex->RefInc();

	SetSize(w,h);
}
Object::Object(uint id, Texture* tex)
{
	Init();
	this->id = id;

	this->tex = tex;
	tex->RefInc();

	SetSize(tex->GetWidth(), tex->GetHeight());
}

Object::Object(uint id, int x, int y, int w, int h)
{
	Init();

	this->id = id;
	SetPosition(x,y);
	SetSize(w,h);
}
Object::Object(uint id, int w, int h)
{
	Init();

	this->id = id;
	SetSize(w,h);
}
Object::Object(uint id)
{
	Init();
	this->id = id;
}

uint Object::GetID()
{
	return id;
}

void Object::SetPosition(double x, double y)
{
	pos[0] = x;
	pos[1] = y;
}
double Object::GetXPosition()
{
	return pos[0];
}
double Object::GetYPosition()
{
	return pos[1];
}

void Object::SetVelocity(double x, double y)
{
	vel[0] = x;
	vel[1] = y;
}
double Object::GetXVelocity()
{
	return vel[0];
}
double Object::GetYVelocity()
{
	return vel[1];
}

void Object::SetSize(int w, int h)
{
	size[0] = w;
	size[1] = h;
}
int Object::GetWidth()
{
	return size[0];
}
int Object::GetHeight()
{
	return size[1];
}

SDL_Texture* Object::GetTexture()
{
	return tex->Get();
}
Texture* Object::GetTextureObject()
{
	return tex;
}

void Object::RegisterLogicCallback(LogicFunc func)
{
	OnLogicStep = func;
}
void Object::RegisterLogicCallbackDelta(LogicFuncDelta func)
{
	OnLogicStepDelta = func;
}

CrustObjData Object::GetData()
{
	//Construct object data struct
	CrustObjData temp = 
	{
		.x = pos,
		.y = pos+1,

		.velX = vel,
		.velY = vel+1,

		.w = size,
		.h = size+1
	};

	return temp;
}

void Object::LogicStep()
{
	if(OnLogicStep)
	{
		OnLogicStep(GetData());
	}
	//else call default logic
}
void Object::LogicStep(double delta)
{
	if(OnLogicStepDelta)
	{
		OnLogicStepDelta(delta, GetData());
	}
	//else call default logic
}