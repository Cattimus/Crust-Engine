#include "Entity.hpp"

Entity::~Entity()
{
	if(tex)
	{
		tex->RefDec();
	}
}

void Entity::Init(Texture* tex)
{
	this->tex = tex;
	tex->RefInc();
	renderPriority = 0;
	visible = true;
}

Entity::Entity(uint id, Texture* tex, int x, int y, int w, int h) : Object(id,x,y,w,h)
{
	Init(tex);
}

Entity::Entity(uint id, Texture* tex, int w, int h) : Object(id,0,0,w,h)
{
	Init(tex);
}

//WARNING - this can cause problems if a null value is passed to this
Entity::Entity(uint id, Texture* tex) : Object(id, 0, 0,tex->GetWidth(), tex->GetHeight())
{
	Init(tex);
}