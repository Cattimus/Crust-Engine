#pragma once

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>

#include "Scene.hpp"
#include "Texture.hpp"

class Engine
{
private:
	int screenWidth = 640;
	int screenHeight = 480;

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	Scene* selectedScene = NULL;
	//background color

	//list of textures
	vector<unique_ptr<Texture>> textures;

	//list of scenes
	vector<unique_ptr<Scene>> scenes;

	bool Init();
	void RenderScene();
	void RenderBlank();

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