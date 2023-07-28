#include "Controllers/Scene.hpp"

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

Object* Scene::CreateEntity(string texPath, int x, int y, int w, int h)
{
	Texture* tex = engine->GetTexture(texPath);
	Object* to_return = (objects[ID] = make_unique<Object>(ID, tex, x, y, w, h)).get();
	ID++;

	return to_return;
}

Object* Scene::CreateObject(int x, int y, int w, int h)
{
	Object* to_return = (objects[ID] = make_unique<Object>(ID, nullptr, x, y, w, h)).get();
	ID++;

	return to_return;
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
	if(objects.find(id) != objects.end())
	{
		objects.erase(objects.find(id));
	}
}

string Scene::GetActiveObjects()
{
	string toReturn = "";

	for(auto &i : objects)
	{
		Object* cur = i.second.get();

		//append object name to string
		toReturn += to_string(cur->GetID());
		toReturn += ",";
	}

	toReturn.pop_back();
	return toReturn;
}

string Scene::GetName()
{
	return name;
}

unordered_map<uint, unique_ptr<Object>>* Scene::GetObjectList()
{
	return &objects;
}

EventHandler<Scene>* Scene::GetEventHandler()
{
	return &events;
}

void Scene::CheckEvents()
{
	events.CheckEvents();

	for(auto &i : objects)
	{
		i.second.get()->GetEventHandler()->CheckEvents();
	}
}

void Scene::CheckCollisions()
{
	//Iterate through main list
	for(ulong i = 0; i < objects.size(); i++)
	{
		auto cur = objects.at(i).get();

		//Iterate through every object after the current one
		for(ulong x = i+1; x < objects.size(); x++)
		{
			auto next = objects.at(x).get();

			//Activate collision event for both objects
			if(cur->GetHitbox()->IsColliding(*next->GetHitbox()))
			{
				cur->GetEventHandler()->DoEvent("Collision");
				next->GetEventHandler()->DoEvent("Collision");
			}
		}
		
	}
}
