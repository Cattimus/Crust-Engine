#pragma once

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Engine;
#include "Object.hpp"
#include "Engine.hpp"

class Scene
{
private:
	string name;

	//list of objects
	uint ID; //ID of next object, will increment with every object
	vector<unique_ptr<Object>> objects;

	Engine* engine;

public:
	Scene(string name, Engine* engine);

	//object management functions
	Object* CreateObject(string texPath, int x, int y, int w, int h);
	Object* GetObject(uint id);
	void    DeleteObject(uint id);
	string  GetActiveObjects(); //return a list of active object IDs separated by ','

	string GetName();

	/*
	//Trigger logic step in every object held in scene
	void LogicStep();
	void LogicStep(double delta);
	*/
};