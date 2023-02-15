#pragma once

#include<iostream>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>

class Scene;

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

	//user input callback
	void OnInput(void(*)());
};