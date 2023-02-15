#pragma once

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

#include "Object.hpp"

class Scene
{
private:
	string name;

	//list of objects
	uint ID = 0; //ID of next object, will increment with every object
	vector<unique_ptr<Object>> objects;

public:
	Scene();

	//object management functions
	Object* CreateObject(string texPath, uint x, uint y, uint w, uint h);
	Object* GetObject(uint id);
	void    DeleteObject(uint id);
	string  GetActiveObjects(); //return a list of active object IDs separated by ','

	//Trigger logic step in every object held in scene
	void LogicStep();
	void LogicStep(double delta);
};