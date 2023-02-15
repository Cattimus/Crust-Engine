#pragma once

#include <iostream>
using namespace std;

#include "Object.hpp"

class Scene
{
private:
	//list of objects
	string name;

public:
	Scene();
	~Scene();

	//object management functions
	Object* CreateObject(string, uint, uint, uint, uint);
	void    DeleteObject(Object*);
	Object* ListObjects();

};