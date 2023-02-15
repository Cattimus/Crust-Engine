#pragma once

#include <iostream>
using namespace std;

class Object;

class Scene
{
private:
	//list of objects

public:
	Scene();
	~Scene();

	//object management functions
	Object* CreateObject(string, uint, uint, uint, uint);
	void    DeleteObject(Object*);
	Object* ListObjects();

};