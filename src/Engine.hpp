#pragma once

#include<iostream>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>

class Scene;
class Texture;

class Engine
{
private:
	int screen_width = 640;
	int screen_height = 480;

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	//list of textures

	bool Init();

public:
	Engine();
	~Engine();

	//create the initial window
	void CreateWindow(uint, uint, uint, uint, bool);

	//scene management functions
	Scene* CreateScene(string);
	Scene* SwitchScene(string);
	void   DeleteScene(string);
	Scene* ListScenes();

	//Texture management functions
	Texture* CreateTexture(string);
	Texture* GetTexture(string);
	//There is no texture delete because textures will be refcounted

	//user input callback
	void OnInput(void(*)());
};