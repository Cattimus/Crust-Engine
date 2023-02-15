#pragma once

#include<iostream>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>

class Texture
{
private:
	SDL_Texture* tex = NULL;
	uint ref = 0;
	string path;

public:
	Texture(string);
	~Texture();

	//reference counting functions
	void RefInc();
	void RefDec();
	uint GetRef();

	//get raw SDL texture
	SDL_Texture* Get();
};