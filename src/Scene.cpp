#include "Scene.hpp"

Scene::Scene(string name, Engine* engine)
{
	ID = 0;
	this->name = name;
	this->engine = engine;
}

Object* Scene::CreateObject(string texPath, int x, int y, int w, int h)
{
	Texture* tex = engine->GetTexture(texPath);
	objects.push_back(make_unique<Object>(ID, tex, x, y, w, h));
	ID++;

	return objects.back().get();
}

Object* Scene::GetObject(uint id)
{
	for(auto i = 0; i < objects.size(); i++)
	{
		Object* cur = objects[i].get();
		if(cur->GetID() == id)
		{
			return cur;
		}
	}

	return NULL;
}

void Scene::DeleteObject(uint id)
{	
	int index = -1;
	for(auto i = 0; i < objects.size(); i++)
	{
		Object* cur = objects[i].get();
		if(cur->GetID() == id)
		{
			index = i;
			break;
		}
	}

	if(index != -1)
	{
		objects.erase(next(objects.begin(), index));
	}
}

string Scene::GetActiveObjects()
{
	string toReturn = "";

	for(auto i = 0; i < objects.size(); i++)
	{
		Object* cur = objects[i].get();

		toReturn += to_string(cur->GetID());
		if(i < objects.size() - 1)
		{
			toReturn += ",";
		}
	}

	return toReturn;
}

string Scene::GetName()
{
	return name;
}