#pragma once

#include<iostream>
using namespace std;

#include "Texture.hpp"

class Object
{
private:
	int pos[2];
	int vel[2];
	int size[2];

	int renderPriority;
	Texture* tex;

public:
	Object();
};