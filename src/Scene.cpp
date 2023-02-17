#include "Scene.hpp"

Scene::Scene(string name, Engine* engine)
{
	ID = 0;
	this->name = name;
	this->engine = engine;
}

Scene::~Scene()
{
	//This will ensure our destructors are called in the proper order. This must be called before SDL_Quit()
	objects = vector<unique_ptr<Object>>();
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
	//Search through objects
	for(auto i = 0; i < objects.size(); i++)
	{
		//If the IDs match, return
		Object* cur = objects[i].get();
		if(cur->GetID() == id)
		{
			return cur;
		}
	}

	//If no object is found, return NULL
	return NULL;
}

void Scene::DeleteObject(uint id)
{	
	//Search for object index
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

	//If the index was found, delete the object
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

		//append object name to string
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

void Scene::LogicStep()
{
	for(auto i = 0; i < objects.size(); i++)
	{
		objects[i].get()->LogicStep();
	}
}

vector<unique_ptr<Object>>* Scene::GetObjectList()
{
	return &objects;
}

void Scene::LogicStep(double delta)
{
	for(auto i = 0; i < objects.size(); i++)
	{
		objects[i].get()->LogicStep();
	}
}