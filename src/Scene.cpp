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
	objects = unordered_map<uint, unique_ptr<Object>>();
}

Object* Scene::CreateObject(string texPath, int x, int y, int w, int h)
{
	Texture* tex = engine->GetTexture(texPath);
	objects[ID] = make_unique<Object>(ID, tex, x, y, w, h);
	ID++;

	return objects[ID].get();
}

Object* Scene::GetObject(uint id)
{
	//Object with the ID does not exist
	if(objects.find(ID) == objects.end())
	{
		return NULL;
	}

	return objects[ID].get();
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

void Scene::RegisterEvent(Event<Scene> event)
{
	string name = event.GetName();
	events[name] = event;
}

void Scene::DeleteEvent(string name)
{
	//Event does not exist
	if(events.find(name) == events.end())
	{
		return;
	}

	events.erase(events.find(name));
}

void Scene::DoEvents()
{
	//Perform event actions for scene
	for(auto &i : events) 
	{
		i.second.Check();
	}

	//Perform event actions for objects
	for(auto &i : objects)
	{
		i.second.get()->DoEvents();
	}
}