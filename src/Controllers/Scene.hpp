#pragma once

#include <iostream>
#include <unordered_map>
#include <memory>
using namespace std;

class Engine;
#include "Objects/Object.hpp"
#include "Controllers/Engine.hpp"
#include "Controllers/EventHandler.hpp"

class Scene
{
private:

	//Name given to the scene
	string name;

	//ID of next object to be created. Increments with every object. IDs are not reused.
	uint ID; 

	//Data storage for all of the objects that are currently active
	unordered_map<uint, unique_ptr<Object>> objects;	

	//Reference to the engine so we can access textures
	Engine* engine;

public:
	Scene(string name, Engine* engine);
	~Scene();

	EventHandler events;

////////////////OBJECT MANAGEMENT FUNCTIONS/////////////////////////////

	//Create a new object from parameters
	//Returns: a reference to the created object
	Object* CreateEntity(string texPath, int x, int y, int w, int h);
	Object* CreateObject(int x, int y, int w, int h);

	//Get an object by ID
	//Returns: a reference to the object if it exists. NULL if it does not.
	Object* GetObject(uint id);

	//Delete an object by ID
	void DeleteObject(uint id);

	//Returns a list of all currently active objects separated by ','
	string GetActiveObjects();

	//Return a direct pointer to the object list
	unordered_map<uint, unique_ptr<Object>>* GetObjectList();

	//Return the name of the Scene
	string GetName();

/////////////////////EVENT FUNCTIONS/////////////////////////
	void CheckEvents();

////////////////////COLLISION FUNCTIONS////////////////////
	void CheckCollisions();
};
