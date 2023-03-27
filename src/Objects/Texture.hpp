#pragma once

#include<iostream>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>

class Texture
{
private:
	//Pointer to the SDL texture object
	SDL_Texture* tex;
	//How many things reference this texture
	uint ref;
	//Path to the source file (for possible reconstruction)
	string path;

	//Size data (w,h)
	int size[2];

	//Position offset(x,y)
	int offset[2];

public:
	Texture(string, SDL_Renderer*);
	~Texture();

//////////////REFERENCE COUNTING FUNCTIONS//////////////////////

	void RefInc();
	void RefDec();
	uint GetRef();
	string GetPath();

	int GetWidth();
	int GetHeight();

	int GetXOffset();
	int GetYOffset();

	//Get raw SDL texture
	SDL_Texture* Get();
};