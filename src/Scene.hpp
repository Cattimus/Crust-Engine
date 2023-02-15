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
	vector<unique_ptr<Object>> objects;

public:
	Scene();
	~Scene();

	//object management functions
	Object* CreateObject(string, uint, uint, uint, uint);
	void    DeleteObject(Object*);
	Object* ListObjects();

};