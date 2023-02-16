#pragma once

#include<iostream>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>

class Texture
{
private:
	SDL_Texture* tex;
	uint ref;
	string path;

public:
	Texture(string, SDL_Renderer*);
	~Texture();

	//reference counting functions
	void RefInc();
	void RefDec();
	uint GetRef();

	//get raw SDL texture
	SDL_Texture* Get();
};