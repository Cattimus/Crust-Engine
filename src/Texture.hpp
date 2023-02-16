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

	int size[2];

public:
	Texture(string, SDL_Renderer*);
	~Texture();

	//reference counting functions
	void RefInc();
	void RefDec();
	uint GetRef();
	string GetPath();

	int GetWidth();
	int GetHeight();

	//get raw SDL texture
	SDL_Texture* Get();
};